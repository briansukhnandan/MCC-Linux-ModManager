#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

bool hasSubDir(std::string path);

int restore_maps(std::string def_maps_path, std::string backup_maps_folder) {

    // First check if backup_maps_dir is empty.
    if (!hasSubDir(backup_maps_folder)) {
        std::cout << "Backup directory is empty." << std::endl;
        return 1;
    }

    // Prompt user to press ENTER before deleting files.
    std::cout << std::endl << "Map files are about to be deleted from Halo MCC." << std::endl;
    std::cout << "Please do not terminate this program." << std::endl;
    std::cout << std::endl << "Press ENTER to continue." << std::endl;
    std::cin.ignore();

    DIR *dir;
    struct dirent *ent;
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

bool hasSubDir(std::string path) {

    if(!fs::is_directory(path)) return false;

    fs::directory_iterator end_it;
    fs::directory_iterator it(path);

    if (it == end_it) return false;

    else return true;

}
