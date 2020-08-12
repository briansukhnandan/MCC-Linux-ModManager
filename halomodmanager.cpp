#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

#include "fs_ops/manage_mods.h"
#include "fs_ops/backup_maps.h"
#include "fs_ops/restore_maps.h"

std::string getMapsPath(std::string mcc_file_path, std::string game_selected); 

/*
 *
 * REQUIRES C++17
 * 
 * My MCC Path: /home/prophet/.local/share/Steam/steamapps/common/Halo\ The\ Master\ Chief\ Collection/
 *
 */

int main(int argc, char* argv[]) {

    int opt;
    std::string user_choice;
    std::string mcc_file_path;
    std::string mod_path;
    std::string game_selected;

    // Process arguments for paths and selected game.
    while((opt = getopt(argc, argv, ":p:f:g:o:")) != -1) {

        switch(opt) {
            
            // Specifying MCC path.
            case 'p':
                mcc_file_path = optarg;
                if (mcc_file_path.back() != '/') {
                    mcc_file_path = mcc_file_path+"/";
                }
                break;

            // Specifying mod files.
            case 'f':
                mod_path = optarg;
                if (mod_path.back() != '/') {
                    mod_path = mod_path+"/";
                }
                break;

            // Specifying game chosen, can be "halo1", "halo2", "halo3", "haloreach".
            case 'g':
                game_selected = optarg;
                break;

            // Specifying desired operation, can be add, rm, or backup.
            case 'o':
                user_choice = optarg;
                break;
                
        }

    }

    // Now set definitive maps path.
    std::string def_maps_path = getMapsPath(mcc_file_path, game_selected);    

    // Do initial check to make sure maps path can be found.
    if (!(PathExists(def_maps_path))) {
        std::cout << std::endl <<  "Maps path not found with the given parameters." << std::endl;
        return 1;
    }

    // Applying .map files and making backups.
    // Requires -p, -f, -g, and -o flags to be set with args.
    if (user_choice == "add") {

        // Check if path or files DNE, end program if any of these conditions are met.
        if (!(PathExists(mod_path))) {
            std::cout << "Mod files not found, please check the path and try again!" << std::endl;
            return 1;
        }
            
        // applyModFiles() will return 1 if an error occurred, 0 otherwise.
        if (applyModFiles(def_maps_path, mod_path)) {
            std::cout << std::endl << "Something went wrong, one or more mod files conflict with MCC's current modded files." << std::endl;
        }

        else std::cout << "Mods successfully loaded!" << std::endl;

    }

    // Removes .map files from Halo MCC directory and backs them up.
    // Requires -p, -g, and -o flags to be set (-b flag optional).
    if (user_choice == "rm") { 

        // If specified backups directory and backups/ dir does not exist, create default one.
        if (!(PathExists("backups/modded_files/"))) {
            
            std::cout << std::endl << "Creating default backup directory at 'backups/'" << std::endl;
            const int dir_err = system("mkdir -p backups/modded_files/");

            std::cout << "Please rerun halomodmanager." << std::endl << std::endl;
            
            if (dir_err == -1) {
                std::cout << "Error creating backups directory." << std::endl;
                return 1;
            }

        }

        removeModFiles(def_maps_path);

    }

    // Creates a clean backup of all .map files.
    if (user_choice == "backup") {

        // backup_maps_folder will be in the form of:
        // backups/halo3/
        // backups/halo2/ 
        std::string backup_maps_folder = "backups/"+game_selected+"_backup/";
        
        // Check to see if backup folder exists already.
        if (!(PathExists(backup_maps_folder))) {
            std::string cpycmd = "mkdir -p "+backup_maps_folder;
            const int dir_err = system(cpycmd.c_str());

            if (dir_err == -1) {
                std::cout << "Error creating backup maps directory." << std::endl;
                return 1;
            }
        
        }

        // backup_maps() will return 1 if an error has occured.
        // Check return status.
        if (backup_maps(def_maps_path, backup_maps_folder)) std::cout << "An error has occurred while backing maps up from "+game_selected << std::endl;

        else std::cout << "All .map files successfully copied over to "+backup_maps_folder << std::endl;

    }

    // Restores .map files with a backup.
    if (user_choice == "restore") {
        
        std::string backup_maps_folder = "backups/"+game_selected+"_backup/";

        if (!(PathExists(backup_maps_folder))) {
            std::cout << "No backup exists at: '" << backup_maps_folder << std::string("'. Please ensure one exists first with '")+std::string("-g ")+game_selected+" -o backup'." << std::endl;
        }

        else {

            if (restore_maps(def_maps_path, backup_maps_folder)) {
                std::cout << "Error restoring files." << std::endl;
            }
            
            else {
                std::cout << std::endl << "Maps successfully restored." << std::endl;
            }

        }

    }

    return 0;
}

std::string getMapsPath(std::string mcc_file_path, std::string game_selected) {

    std::string def_maps_path;

    if (game_selected == "halo1") {
        //TODO
    }

    else if (game_selected == "halo2") {
        def_maps_path = mcc_file_path+game_selected+"/h2_maps_win64_dx11/";            
    }                    

    else if (game_selected == "halo3") {
        def_maps_path = mcc_file_path+game_selected+"/maps/";
    }

    else if (game_selected == "haloreach") {
        def_maps_path = mcc_file_path+game_selected+"/maps/";
    }

    if (game_selected == "halo4") {
        //TODO when Halo4 comes out.
    }

    return def_maps_path;

}