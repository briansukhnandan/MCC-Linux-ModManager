#!/bin/sh

# Globals
BACKUP_DIR=/home/prophet/Documents/MCC-Backups

halo1maps=("a10.map" "a30.map" "a50.map" "b30.map" "b40.map" "c10.map" "c20.map" "c40.map" "d20.map" "d40.map" "ui.map")
halo2maps=("00a_introduction.map" "01a_tutorial.map" "01b_spacestation.map" "03a_oldmombasa.map" "03b_newmombasa.map" "04a_gasgiant.map" "04b_floodlab.map", "05a_deltaapproach.map" "05b_deltatowers.map" "06a_sentinelwalls.map" "06b_floodzone.map" "07a_highcharity.map" "07b_forerunnership.map" "08a_deltacliffs.map" "08b_deltacontrol.map" "mainmenu.map" "shared.map" "single_player_shared.map")
halo3maps=("005_intro.map" "010_jungle.map" "020_base.map" "030_outskirts.map" "040_voi.map" "050_floodvoi.map" "070_waste.map" "100_citadel.map" "110_hc.map" "120_halo.map" "130_epilogue.map" "armory.map" "bunkerworld.map" "campaign.map" "chill.map" "chillout.map" "construct.map" "cyberdyne.map" "deadlock.map" "descent.map" "docks.map" "fortress.map" "ghosttown.map" "guardian.map" "isolation.map" "lockout.map" "mainmenu.map" "midship.map" "riverworld.map" "salvation.map" "sandbox.map" "shared.map" "shrine.map" "sidewinder.map" "snowbound.map" "spacecamp.map" "warehouse.map" "zanzibar.map")
haloreachmaps=("20_sword_slayer.map" "30_settlement.map" "35_island.map" "45_aftship.map" "45_launch_station.map" "50_panopticon.map" "52_ivory_tower.map" "70_boneyard.map" "campaign.map" "cex_beaver_creek.map" "cex_damnation.map" "cex_ff_halo.map" "cex_hangemhigh.map" "cex_headlong.map" "cex_prisoner.map" "cex_timberland.map" "condemned.map" "dlc_invasion.map" "dlc_medium.map" "dlc_slayer.map" "ff_unearthed.map" "ff10_prototype.map" "ff20_courtyard.map" "ff30_waterfront.map" "ff45_corvette.map" "ff50_park.map" "ff60_airview.map" "ff60_icecave.map" "ff70_holdout.map" "forge_halo.map" "m05.map" "m10.map" "m20.map" "m30.map" "m35.map" "m45.map" "m50.map" "m52.map" "m60.map" "m70_a.map" "m70_bonus.map" "m70.map" "shared.map" "trainingpreserve.map")

#####################
# Process arguments #
#####################
while getopts p:f:g:o: flag
do
  case "${flag}" in
    # Remove trailing / from dir path and mod files path.
    p) path=$(echo ${OPTARG} | sed 's:/*$::');;
    f) files=$(echo ${OPTARG} | sed 's:/*$::');;
    g) game=${OPTARG};;
    o) operation=${OPTARG};;
  esac
done

# Why 343i doesn't use a consistent naming scheme is beyond me.
function get_maps_path {
  case $game in
    halo1)
      echo "$path/$game/original/build/maps/";;
    halo2)
      echo "$path/$game/h2_maps_win64_dx11/";;
    halo3|haloreach)
      echo "$path/$game/maps/";;
    *) ;;
  esac
}

function get_maps_array {
  case $game in
    halo1)
      echo ${halo1maps[@]};;
    halo2)
      echo ${halo2maps[@]};;
    halo3)
      echo ${halo3maps[@]};;
    haloreach)
      echo ${haloreachmaps[@]};;
    *) ;;
  esac
}

# Similarities to the Chinese port of Halo: MCC.
function toggle_pegasus_mode {
  echo "Toggling Pegasus mode"
  if [ -f $path/pegasus ]
  then
    rm "$path/pegasus"
  else
    touch "$path/pegasus"
  fi
}

# Adds map_variants/ files from mod -> MCC path.
# Also backs up mod files to $BACKUP_DIR
function apply_mod_files {
  ASSOCIATED_MAPS=($(get_maps_array))
  MOD_BACKUP_FOLDER="$BACKUP_DIR/mods/$(date +%s)/"
  for file in $files/map_variants/*;
  do
    # Makes sure files in mod are valid for the specified game.
    # And makes sure there isn't a currently modded file (.map will have an associated .bak) that should be replaced.
    if [[ ("${ASSOCIATED_MAPS[@]}" =~ "$(basename $file)") && ! -f $(get_maps_path)$(basename $file).bak ]]
    then
      echo "Adding $(basename $file) to $game"
      mv $(get_maps_path)$(basename $file) $(get_maps_path)$(basename $file).bak
      cp -f $file $(get_maps_path)
      
      # Copy over valid mod files into MCC-Backups.
      mkdir -p $MOD_BACKUP_FOLDER
      cp -f $file $MOD_BACKUP_FOLDER

    else
      echo "$game maps doesn't contain the specified map or a .bak file already exists for: $(basename $file). Skipping..."
    fi
  done
}

# Checks if any .bak files exist in MCC maps and removes the corresponding file
# without .bak and renames the .bak to the original file name.
function remove_mod_files {
  echo "Removing .bak files"
  for file in $(get_maps_path)*.bak;
  do
    FILE_NAME_WITHOUT_BAK=$(echo "$file" | sed 's/.\{4\}$//')
    mv -f $file $FILE_NAME_WITHOUT_BAK
  done
}

# Copies all contents from associated maps directory to the backup directory.
function backup_maps {
  if [ -d "$(get_maps_path)" ]
  then
    echo "Creating backup directory if not exists..."
    mkdir -p $BACKUP_DIR/$game
    printf "Copying files from $(get_maps_path) to $BACKUP_DIR/$game...\n\n"
    cp $(get_maps_path)* $BACKUP_DIR/$game
    echo "Backup complete!"

  else
    echo "The directory $(get_maps_path) doesn't exist! Please verify your game files through Steam."

  fi
}

# Should only be called if a backup for the specified game exists.
function restore_maps_from_backup {
  if [ -d $BACKUP_DIR/$game ]
  then
    # Warn the user about this if they want to take manual intervention.
    echo "Restoring .map files from $BACKUP_DIR/$game/ to $(get_maps_path)"
    echo "WARNING: This will nuke the current contents of the $game maps folder and replace it with the backup."
    read -p "Continue? (y/n)" -r
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
      # Probably want to force overwrite if there exists a file with the same file name already.
      # The "add" operation will back up all mods each time so no harm in doing this.
      cp -rf $BACKUP_DIR/$game/* $(get_maps_path)
      printf "\nRestore complete!\n"
    fi

  else
    echo "A backup for $game doesn't exist!"

  fi
}

##############
# Operations #
##############
if [[ $operation == "add" ]]
then 
  apply_mod_files

elif [[ $operation == "rm" ]]
then
  remove_mod_files

elif [[ $operation == "backup" ]]
then
  backup_maps

elif [[ $operation == "restore" ]]
then
  restore_maps_from_backup

elif [[ $operation == "pegasus" ]]
then
  toggle_pegasus_mode

else
  echo "Operation not valid!"

fi