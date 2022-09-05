#!/bin/sh

# Globals
BACKUP_DIR=~/Documents/MCC\ Backups

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

# Why 343i doesn't use a consistent naming scheme
# is beyond me.
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

# Copies file from associated maps directory to the backup directory.
function backup_maps {
  if [ -d "$(get_maps_path)" ]
  then
    echo "Maps directory found. Creating backup directory in $BACKUP_DIR if it doesn't exist and backing up .map files"
    mkdir -p $BACKUP_DIR/$game
    cp -r $(get_maps_path) $BACKUP_DIR/$game

  else
    echo "The directory $(get_maps_path) doesn't exist! Please verify your game files through Steam."

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
  # echo "backup $(get_maps_path)"
  backup_maps

elif [[ $operation == "restore" ]]
then
  echo "restore"

elif [[ $operation == "pegasus" ]]
then
  echo "Toggling Pegasus mode"
  if [ -f $path/pegasus ]
  then
    rm "$path/pegasus"
  else
    touch "$path/pegasus"
  fi

else
  echo "Operation not valid!"
  exit

fi