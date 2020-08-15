#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

#include <dirent.h>
#include <sys/stat.h> 

#include "valid_paths.h"
#include "get_maps_strings.h"

// bool check_validity(std::string map_name, std::string game_selected, std::vector<std::string> halo1_maps, std::vector<std::string> halo2_maps, std::vector<std::string> halo3_maps, std::vector<std::string> haloreach_maps);

/*
 *
 * .applyModFiles() - Moves .map files from mod_path to def_maps_path. In the process of
 *                    doing so, this will also create backups of all necessary maps in mod
 *                    directory.
 *
 *                    Written by: Brian Sukhnandan 08/09/20 @briansukhnandan
 *                    
 */

int applyModFiles(std::string def_maps_path, std::string mod_path, std::string game_selected) {

    // Print paths about to be modified.
    std::cout << std::endl << "All paths successfully found, here is what's going to be modified -" << std::endl << std:: endl;
    std::cout << "Maps File Path: " << def_maps_path << std::endl;
    std::cout << "Path to Mod's .map files: "  << mod_path << std::endl << std::endl;

    // Go through directory of mod containing map files.
    // For each file, look in mcc halo maps dir and
    // change map name to map_name.map.bak

    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> map_vector;
    std::vector<std::string> individual_maps;

    std::vector halo1_maps = get_halo1_maps();
    std::vector halo2_maps = get_halo2_maps();
    std::vector halo3_maps = get_halo3_maps();
    std::vector haloreach_maps = get_haloreach_maps();

    // First check, loop through mod_path and make sure each .map
    // file is valid for the halo game going to be selected.
    // This is to ensure for example that Forge World doesn't get
    // accidentally added to Halo3 when it should go to Reach.
    if ((dir = opendir(mod_path.c_str())) != NULL) {

        while ((ent = readdir (dir)) != NULL) {

            std::string map_name(ent->d_name);

            if ((ent->d_name[0] != '.') && (map_name.substr(map_name.size()-4) == ".map")) {

                if (!check_validity(map_name, game_selected, halo1_maps, halo2_maps, halo3_maps, haloreach_maps)) {
                    std::cout << "One or more .map files in the mod directory are not valid for "+game_selected+"." << std::endl;
                    std::cout << "Perhaps a file in the mods directory is misspelled?" << std::endl;
                    return 1;
                }

            }
        
        }

    }

    // Open up mod path for copying paths. Also checks if appropriate files exist.
    if ((dir = opendir(mod_path.c_str())) != NULL) {

        // Print all files in mod directory.
        std::cout << "The following files will be turned into backup files:" << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
        while ((ent = readdir (dir)) != NULL) {

            // If directories start with ., they are hidden folders which will be ignored.
            // This block below means we have encountered a normal *.map file.
            if (ent->d_name[0] != '.') {

                // Firstly, check if any .bak files exist for maps that are also contained
                // within mod folder.
                if (FileExists(def_maps_path+(ent->d_name)+".bak")) {
                    std::cout << "Error: '" << ent->d_name << "' is already modded." << std::endl;
                    std::cout << "Please restore the .map file backup currently loaded with '-o rm' as a compiler flag." << std::endl;
                    return 1;
                }

                std::cout << def_maps_path+(ent->d_name) << std::endl;
                map_vector.push_back(def_maps_path+(ent->d_name));
                individual_maps.push_back(ent->d_name); 
            }

        }
        closedir(dir);
    }

    else {
        // We will only reach this else statement when the directory could not be opened (insufficient perms maybe).
        perror ("");
        return 1;
    }


    // Prompt user to press ENTER, then actually rename the current map files to backups.
    std::cout << std::endl << "Press ENTER to continue..." << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cin.ignore();
    for (size_t i = 0; i < map_vector.size(); i++) {
        std::rename(map_vector[i].c_str(), (map_vector[i]+".bak").c_str());
    }

    // Displays info for the user, and then after pressing enter, will copy files over.
    std::cout << "The following mod files will now be moved into the Halo MCC maps folder." << std::endl;
    for (size_t i = 0; i < map_vector.size(); i++) {
        std::cout << mod_path+individual_maps[i] << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl << "Press ENTER to continue..." << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cin.ignore();

    // Now copy files from mod path to halo mcc maps folder. All files
    // will be backed up at this point.
    for (size_t i = 0; i < individual_maps.size(); i++) {

        std::ifstream src(mod_path+individual_maps[i], std::ios::binary);
        std::ofstream dst(def_maps_path+individual_maps[i], std::ios::binary);

        dst << src.rdbuf();

    }

    return 0;
}

/*
 *
 * .removeModFiles() - Removes modded .map files from Halo MCC maps dir. Everything
 *                     removed from Halo MCC maps folder will be placed into backups/ directory
 *                     which will be created upon '-o rm' flag. 
 *
 *                     Written by: Brian Sukhnandan 08/09/20 @briansukhnandan
 *                    
 */

int removeModFiles(std::string def_maps_path) {

    DIR *dir;
    struct dirent *ent;
    std::string user_choice = "99";
    size_t map_counter = 1;
    std::map<int, std::string> map_order;

    // Open Halo MCC maps directory, and run a search for all files
    // ending with .map.bak, which contain the original maps for restoration.
    // Then add them to an int/string map to delete them from maps directory.
    while (user_choice != "0") {

        map_counter = 1;
        
        std::cout << std::endl << "The following backup files were found: " << std::endl << std::endl;
        std::cout << "0. EXIT" << std::endl;

        if ((dir = opendir(def_maps_path.c_str())) != NULL) {
            
            while ((ent = readdir(dir)) != NULL) {

                std::string map_name(ent->d_name);
                
                // Print out all files ending with .bak.
                if ( (ent->d_name[0] != '.') && (map_name.substr(map_name.size()-4) == ".bak") ) {
                    
                    std::cout << map_counter << ". " << ent->d_name << std::endl;
                    map_order.insert(std::pair<int, std::string>(map_counter, def_maps_path+(ent->d_name)));
                    map_counter++;

                }

            }

            closedir(dir);
        }
        std::cout << std::endl << "Please enter any backup files listed above to restore them (or 0 if finished)." << std::endl;
        std::cout << std::endl << "For example if I wanted to restore Guardian, I would type 'guardian.map.bak' if it's listed." << std::endl;
        std::cout << ">";
        std::cin >> user_choice;

        // Check if user wants to exit.
        if (user_choice == "0") return 0;

        if ((user_choice.size() <= 4) || user_choice.substr(user_choice.size()-4) != ".bak") {
            std::cout << "Please enter a .bak file listed above! You can accidentally delete a map otherwise." << std::endl;
            return 1;
        }

        // Create an object to store the map result obtained from user_choice.
        // auto map_iter = map_order.find(user_choice);
        std::string staged_map = def_maps_path+(user_choice).substr(0, user_choice.size()-4);
        // map_order.erase(user_choice);

        std::cout << std::endl << "The following file was staged for removal:" << std::endl;     
        std::cout << std::endl << staged_map << std::endl;

        std::cout << std::endl << "Press ENTER to continue..." << std::endl;
        std::cin.ignore();

        // Prepare mv command for staged map.
        std::string mv_cmd = "mv \""+staged_map+"\" backups/modded_files/";

        // Move staged map to backups folder.
        system(mv_cmd.c_str());
        std::rename((staged_map+".bak").c_str(), staged_map.c_str());

    }

    return 0;
}