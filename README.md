# MCC-Linux-ModManager
A Mod Manager CLI for Halo: The Master Chief Collection on Linux. v0.1

## Games supported
- Halo: CE (In Progress)
- Halo 2 (Done)
- Halo 3 (Done)
- Halo: Reach (Done)

## What can I do with it?
The following operations are supported:
- Adding/Removing .map files (for MP maps/Rebalanced Campaigns).

## How do I use it?
```
g++ -o halomodmanager halomodmanager.cpp -std=c++17

./halomodmanager -p <PATH_TO_MCC> -f <PATH_TO_MOD_.MAP_FILES> -g <GAME_SELECTED> -o <OPERATION>
```

For all flags, please use absolute paths to your directories!
* -p is the path where Halo: MCC resides. For example, mine would be: `/home/prophet/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/`
* -f is the path to your mod's .map files. These can be located anywhere on the fs.
* -g compiler flag args can either be `halo1`, `halo2`, `halo3`, or `haloreach`.
* -o compiler flag args can be `add`, or `rm`.

## Notes
- PLEASE MAKE SURE THE MOD FOLDER CONTAINS ONLY .MAP FILES!!!
- Adding .map files requires the -p, -f, -g, and -o flags to be set.
- Restoring .map files/removing modded files requires the -p, -g, and -o flags to be set.
- When adding .map files, make sure the name(s) of those files matches the ones in MCC's maps directory before replacement. You can find the names of these files on Halo Assembly (if you have access to a Windows machine) or in the Halo Modding discord.

## Examples
- Adding maps to Halo 3, given a folder named 'sample_halo3_mod' containing 3 *.map files (the same command would work for other Halo games, just change -g to halo2/haloreach and supply the appropriate mod path):

`./halomodmanager -p /home/prophet/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -f /home/prophet/Documents/sample_halo3_mod/ -g halo3 -o add`

- Removing modded .map files from Halo 3 and restoring the originals (Again, the same would work for any other Halo game by changing -g):

`./halomodmanager -p /home/prophet/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -g halo3 -o rm`

- Installing Ultimate Forge World for Halo: Reach:

`./halomodmanager -p /home/prophet/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -f /home/prophet/Documents/sample_reach_mod/ -g haloreach -o add`
