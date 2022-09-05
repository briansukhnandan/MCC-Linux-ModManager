#!/bin/sh

# Globals
BACKUP_DIR=/home/prophet/Documents/MCC-Backups

#####################
# Process arguments #
#####################
while getopts p:f:g:o: flag
do
  case "${flag}" in
    # Remove trailing / from dir path.
    p) path=$(echo ${OPTARG} | sed 's:/*$::');;
    f) files=${OPTARG};;
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
  echo "adding"

elif [[ $operation == "rm" ]]
then
  echo "rm"

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