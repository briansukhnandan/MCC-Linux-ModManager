# MCC-Linux-ModManager
A Mod Manager CLI for Halo: The Master Chief Collection on Linux. v0.6

## Games supported
- Halo: CE (Done)
- Halo 2 (Done)
- Halo 3 (Done)
- Halo: Reach (Done)
- Halo 4 (N/A)

## What can I do with it?
The following operations are supported:
- Adding/Removing .map files (for MP maps/Campaign).
- Creating a backup of MCC .map files.
- Restoring .map files from a backup.
- Enabling/Disabling Pegasus Mode (A similar version to the Chinese port of MCC).
- Adding game/map variants to Halo 3, and Reach.

## How do I use it?
```
chmod +x halomodmanager.sh
./halomodmanager -p <PATH_TO_MCC> -f <PATH_TO_MOD_.MAP_FILES> -g <GAME_SELECTED> -o <OPERATION>
```

For all parameters, please use absolute paths to your directories!
* `-p` is the path where Halo: MCC resides. For example, mine would be: `/home/$USER/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/`
* `-f` is the path to a folder containing your mod's .map files. These can be located anywhere on the fs. An example would be something like: `/home/$USER/Documents/sample_halo_mod/`.
* `-g` args can either be `halo1`, `halo2`, `halo3`, or `haloreach`.
* `-o` args can be: 
  * `add` for adding .map files.
  * `rm` for removing .map files.
  * `backup` for creating a backup of any Halo game supplied by `-g`.
  * `restore` for restoring .map files of any Halo game supplied by `-g` to its original state, **after creating a backup**.
  * `pegasus` for enabling/disabling Pegasus mode. The only parameter required is your MCC path.

## Notes
- If you're using this program for the first time, you're going to want to make a backup of all your files.

  `./halomodmanager -p <PATH_TO_MCC> -g halo1 -o backup`

  `./halomodmanager -p <PATH_TO_MCC> -g halo2 -o backup`
  
  `./halomodmanager -p <PATH_TO_MCC> -g halo3 -o backup`
  
  `./halomodmanager -p <PATH_TO_MCC> -g haloreach -o backup`
  
- The mod folder (supplied by -f) should only contain `*.map` files, a `game_variants/` directory, and a `map_variants/` directory!!!
- Adding .map files requires the `-p`, `-f`, `-g`, and `-o` parameters to be set.
- Restoring .map files/removing modded files requires the `-p`, `-g`, and `-o` parameters to be set.
- All backups will be stored in a `./backups/` directory which is created upon removing .map files and backup creations.
- When adding .map files, make sure the name(s) of those files matches the ones in MCC's maps directory before replacement. You can find the names of these files on Halo Assembly (if you have access to a Windows machine) or in the Halo Modding discord.
- Modded files that are removed will be moved to `./backups/modded_files/` with a UNIX timestamp equating to when those files were removed from MCC.
- Custom tag support is not available because of Halo Assembly not having a native Linux release or workaround. Hopefully soon we can see this being implemented.

## Examples
- Adding maps to Halo 3, given a folder named 'sample_halo3_mod' containing 3 *.map files (the same command would work for other Halo games, just change -g to halo2/haloreach and supply the appropriate mod path):

`./halomodmanager -p /home/$USER/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -f /home/$USER/Documents/sample_halo3_mod/ -g halo3 -o add`

- Removing modded .map files from Halo 3 and restoring the originals, while also backing up modded files to the backups/ directory (the same would work for any other Halo game by changing -g):

`./halomodmanager -p /home/$USER/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -g halo3 -o rm`

- Installing Ultimate Forge World for Halo: Reach:

`./halomodmanager -p /home/$USER/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -f /home/$USER/Documents/ultimateforgeworld_reach_mod/ -g haloreach -o add`

- Creating a backup of Halo 2 .map files:

`./halomodmanager -p /home/$USER/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -g halo2 -o backup`

- Restoring Halo: Reach .map files from a backup:

`./halomodmanager -p /home/$USER/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -g haloreach -o restore`

- Enabling Pegasus Mode:

`./halomodmanager -p /home/$USER/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/ -o pegasus`

## Disclaimer
This Mod Manager, like others is **not** EAC-compliant. Before using modded files of any kind, you must disable EAC. Playing with mods without doing this will probably cause your game to not boot, or worse you'll be banned from Halo: MCC and XBL. I am not responsible for anyone being banned because of this.

## TODO
- Custom Menu screen support.
