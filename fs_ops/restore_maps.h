#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

bool hasSubDir(std::string path);
bool verifyAmtOfMaps(std::string game_selected, int maps_counter);

int restore_maps(std::string def_maps_path, std::string backup_maps_folder, std::string game_selected) {

    // First check if backup_maps_dir is empty.
    if (!hasSubDir(backup_maps_folder)) {
        std::cout << "Error. Backup directory is empty." << std::endl;
        return 1;
    }

    // Now verify that the backup created consists of only .map files
    // This is to prevent injection of unwanted files.
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
                

            }

        }
        closedir(dir);
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

    if ( (game_selected == "halo1") ) {
        //TODO
    }

    else if ((game_selected == "halo2") && (maps_counter != 18)) return false;

    else if ((game_selected == "halo3") && (maps_counter != 38)) return false;
    
    else if ((game_selected == "haloreach") && (maps_counter != 44)) return false;

    return true;
}

