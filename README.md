# MCC-Linux-ModManager
A Mod Manager CLI for Halo: The Master Chief Collection on Linux. v0.1

## What can I do with it?
The following operations are supported:
- Adding/Removing .map files (for MP maps/Rebalanced Campaigns).

## How do I use it?
```
g++ -o halomodmanager halomodmanager.cpp -std=c++17

./halomodmanager -p <PATH_TO_MCC> -f <PATH_TO_MOD_.MAP_FILES> -g <GAME_SELECTED> -o <OPERATION>
```

## Notes
- -g compiler flag args can either be halo1, halo2, halo3, or haloreach.
- -o compiler flag args can be add, or rm.
- Adding .map files requires the -p, -f, -g, and -o flags to be set.
