# MCC-Linux-ModManager
A Mod Manager CLI for Halo: The Master Chief Collection on Linux. v0.1

## Games supported
- Halo: CE (In Progress)
- Halo 2 (Done)
- Halo 3 (Done)
- Halo: Reach (Done)
- Halo 4 (N/A)

## What can I do with it?
The following operations are supported:
- Adding/Removing .map files (for MP maps/Campaign).
- Creating a backup of MCC .map files.
- Restoring .map files from a backup.

## How do I use it?
```
g++ -o halomodmanager halomodmanager.cpp -std=c++17

./halomodmanager -p <PATH_TO_MCC> -f <PATH_TO_MOD_.MAP_FILES> -g <GAME_SELECTED> -o <OPERATION>
```

For all args, please use absolute paths to your directories!
* -p is the path where Halo: MCC resides. For example, mine would be: `/home/$USER/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/`
* -f is the path to a folder containing your mod's .map files. These can be located anywhere on the fs. An example would be something like: `/home/$USER/Documents/sample_halo_mod/`.
* -g args can either be `halo1`, `halo2`, `halo3`, or `haloreach`.
* -o args can be: 
  * `add` for adding .map files.
  * `rm` for removing .map files.
  * `backup` for creating a backup of any Halo game supplied by `-g`.
  * `restore` for restoring .map files of any Halo game supplied by `-g` to its original state, **after creating a backup**.

## Notes
- PLEASE MAKE SURE THE MOD FOLDER (supplied by -f) ONLY CONTAINS `*.map` FILES!!!
- Adding .map files requires the `-p`, `-f`, `-g`, and `-o` args to be set.
- Restoring .map files/removing modded files requires the `-p`, `-g`, and `-o` args to be set.
- All backups will be stored in a `./backups/` directory which is created upon removing .map files and backup creations.
- When adding .map files, make sure the name(s) of those files matches the ones in MCC's maps directory before replacement. You can find the names of these files on Halo Assembly (if you have access to a Windows machine) or in the Halo Modding discord.

## Examples
- Adding maps to Halo 3, given a folder named 'sample_halo3_mod' containing 3 *.map files (the same command would work for other Halo games, just change -g to halo2/haloreach and supply the appropriate mod path):

`./halomodmanager -p /home/$USER/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -f /home/$USER/Documents/sample_halo3_mod/ -g halo3 -o add`

- Removing modded .map files from Halo 3 and restoring the originals, while also backing up modded files to the backups/ directory (the same would work for any other Halo game by changing -g):

`./halomodmanager -p /home/$USER/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -g halo3 -o rm`

- Installing Ultimate Forge World for Halo: Reach:

`./halomodmanager -p /home/$USER/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -f /home/$USER/Documents/ultimateforgeworld_reach_mod/ -g haloreach -o add`

- Creating a backup of Halo 2 .map files:

`./halomodmanager -p /home/prophet/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -g halo2 -o backup`
