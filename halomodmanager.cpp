#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

#include "fs_ops/manage_mods.h"

/*
 * REQUIRES C++17
 * Example command usage:
 * ./halo_linux -p ~/Documents/dummy_maps_folder/ -f ./map_names.txt -g halo3
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

            // Specifying game chosen.
            case 'g':
                game_selected = optarg;
                break;

            // Specifying desired operation.
            case 'o':
                user_choice = optarg;
                break;
                
        }

    }

    // Now set definitive maps path.
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
        
        // renameFiles() will return 1 if an error occurred, 0 otherwise.
        if (applyModFiles(def_maps_path, mod_path)) {
            std::cout << std::endl << "Something went wrong, one or more mod files conflict with MCC's current modded files." << std::endl;
        }

        else std::cout << "Mods successfully loaded!" << std::endl;

    }

    // Removes .map files from Halo MCC directory and backs them up.
    // Requires -p, -g, and -o flags to be set (-b flag optional).
    if (user_choice == "rm") { 

        // If specified backups directory and backups/ dir does not exist, create default one.
        if (!(PathExists("backups/"))) {
            
            std::cout << std::endl << "Creating default backup directory at 'backups/'" << std::endl;
            std::cout << "Please rerun halomodmanager." << std::endl << std::endl;
            const int dir_err = system("mkdir -p backups");
            
            if (dir_err == -1) {
                std::cout << "Error creating backups directory." << std::endl;
                return 1;
            }

        }

        else removeModFiles(def_maps_path);

    }

    return 0;

}