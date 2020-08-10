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

* -p is the path where Halo: MCC resides. For example, mine would be: `/home/prophet/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/`
* -g compiler flag args can either be `halo1`, `halo2`, `halo3`, or `haloreach`.
* -o compiler flag args can be `add`, or `rm`.

## Notes
- Adding .map files requires the -p, -f, -g, and -o flags to be set.
- Restoring .map files/removing modded files requires the -p, -g, and -o flags to be set.

## Examples
- Adding maps to Halo 3, given a folder containing 3 *.map files:

`./halomodmanager -p /home/prophet/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -f /home/prophet/Documents/sample_halo3_mod/ -g halo3 -o add`
