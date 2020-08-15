#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

bool hasSubDir(std::string path);
bool verifyAmtOfMaps(std::string game_selected, int maps_counter);

/*
 *
 * .restore_maps() - Purges all .map files from MCC maps directory and
 *                   recopies over all files from backup_maps_folder into maps
 *                   directory.
 *
 *                   Written by: Brian Sukhnandan 08/12/20 @briansukhnandan
 *                    
 */

int restore_maps(std::string def_maps_path, std::string backup_maps_folder, std::string game_selected) {

    std::vector halo1_maps = get_halo1_maps();
    std::vector halo2_maps = get_halo2_maps();
    std::vector halo3_maps = get_halo3_maps();
    std::vector haloreach_maps = get_haloreach_maps();
    
    // First check if backup_maps_dir is empty.
    if (!hasSubDir(backup_maps_folder)) {
        std::cout << "Error. Backup directory is empty." << std::endl;
        return 1;
    }

    // Now verify that the backup created consists of only .map files
    // This is to prevent injection of unwanted files.
    // We also check if the map name is appropriate for the correct halo game.
    DIR *dir;
    struct dirent *ent;
    int maps_counter = 0;
    if ((dir = opendir(backup_maps_folder.c_str())) != NULL) {

        while ((ent = readdir (dir)) != NULL) {

            std::string map_name(ent->d_name);
            
            // Anytime we encounter a .map file increment maps_counter.
            // At the end of this while loop maps_counter should = amt of .map files in halo dir.
            if ((ent->d_name[0] != '.') && (map_name.substr(map_name.size()-4) == ".map")) {
                
                maps_counter++;

                if (!check_validity(map_name, game_selected, halo1_maps, halo2_maps, halo3_maps, haloreach_maps)) {
                    std::cout << "One or more .map files in the backups directory are not valid for "+game_selected+"." << std::endl;
                    std::cout << "Maybe a file is misspelled?" << std::endl;
                    return 1;
                }

            }

            // If we encounter a non-hidden file with an extension other than .map.
            if ((ent->d_name[0] != '.') && (map_name.substr(map_name.size()-4) != ".map")) {
                std::cout << std::endl << "Non .map files encountered in backups folder, please check contents of backup and try again." << std::endl << std::endl;
                return 1;
            }

        }
        closedir(dir);
    }

    // Now verify that the amount of maps in there matches the amt that should
    // be in the corresponding halo game.
    if (!verifyAmtOfMaps(game_selected, maps_counter)) {
        std::cout << "Amount of .map files in backup folder does not match with files needed for "+game_selected+"." << std::endl;
        return 1;
    }

    // Prompt user to press ENTER before deleting files.
    std::cout << std::endl << "Map files are about to be deleted from Halo MCC." << std::endl;
    std::cout << "Please do not terminate this program." << std::endl;
    std::cout << std::endl << "Press ENTER to continue." << std::endl;
    std::cin.ignore();

    // Then delete all .map files and .bak files from def_maps_path.
    if ((dir = opendir(def_maps_path.c_str())) != NULL) {

        while ((ent = readdir (dir)) != NULL) {

            std::string map_name(ent->d_name);

            if ((ent->d_name[0] != '.') && ( (map_name.substr(map_name.size()-4) == ".bak") || (map_name.substr(map_name.size()-4) == ".map") ) ) {
                
                std::cout << "Deleting: "+map_name << std::endl;
                std::string deletecmd = "rm \""+def_maps_path+map_name+"\"";
                // std::cout << deletecmd << std::endl;
                
                const int delete_err = system(deletecmd.c_str());

                if (delete_err == -1) {
                    std::cout << "Error deleting contents of maps directory." << std::endl;
                    return 1;
                }

            }

        }
        closedir(dir);
    }

    std::cout << std::endl << "Map files are about to be copied over from the backup directory." << std::endl;
    std::cout << "Please do not terminate this program." << std::endl;
    std::cout << std::endl << "Press ENTER to continue." << std::endl;
    std::cin.ignore();

    // Now copy all files from backup dir to maps dir.
    maps_counter = 0;
    if ((dir = opendir(backup_maps_folder.c_str())) != NULL) {

        while ((ent = readdir (dir)) != NULL) {

            std::string map_name(ent->d_name);

            if ((ent->d_name[0] != '.') && (map_name.substr(map_name.size()-4) == ".map") ) {
                
                std::cout << "Copying: "+map_name << std::endl;

                std::string cpycmd = "cp \""+backup_maps_folder+map_name+"\""+" \""+def_maps_path+"\"";
                // std::cout << cpycmd << std::endl;
        
                const int cpycmd_err = system(cpycmd.c_str());

                if (cpycmd_err == -1) {
                    std::cout << "Error deleting contents of maps directory." << std::endl;
                    return 1;
                }
                
                maps_counter++;

            }

        }
        closedir(dir);
    }

    // Last check, make sure # of maps copied over is correct.
    // This block would only be hit if the backups folder was somehow
    // modified after passing the initial file amount checks.

    // If this is the case, the user tampered with the maps on purpose.
    // Punish the user and just copy them anyways. Let them manually sort out the differences.
    if (!verifyAmtOfMaps(game_selected, maps_counter)) {
        std::cout << std::endl << "Not all necessary maps copied over. Please verify game files with Steam!" << std::endl;
        return 1;
    }

    return 0;
}

// Checks if a directory is empty by checking two dir iterators are =.
bool hasSubDir(std::string path) {

    if(!fs::is_directory(path)) return false;

    fs::directory_iterator end_iter;
    fs::directory_iterator iter(path);

    if (iter == end_iter) return false;

    else return true;

}

bool verifyAmtOfMaps(std::string game_selected, int maps_counter) {

    if ( (game_selected == "halo1") && (maps_counter != 11) ) return false;

    else if ((game_selected == "halo2") && (maps_counter != 18)) return false;

    else if ((game_selected == "halo3") && (maps_counter != 38)) return false;
    
    else if ((game_selected == "haloreach") && (maps_counter != 44)) return false;

    return true;
}

