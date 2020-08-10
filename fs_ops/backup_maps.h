#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int backup_maps(std::string def_maps_path, std::string backup_maps_folder) {
    
    DIR *dir;
    struct dirent *ent;
    
    // First off, check to make sure no backups already by looping through
    // dir and checking file extensions. If all is good, proceed below:

    if ((dir = opendir(def_maps_path.c_str())) != NULL) {

        while ((ent = readdir (dir)) != NULL) {

            std::string map_name(ent->d_name);

            if ((ent->d_name[0] != '.') && (map_name.substr(map_name.size()-4) == ".bak")) {
                std::cout << std::endl << "Please clear maps folder of all modded .map files with '-o rm' before backing up."  << std::endl << std::endl;
                return 1;
            }

        }
        closedir(dir);
    } 

    // Go into Halo MCC maps folder (def_maps_path).
    // Loop through directory and push all .map files
    // to a vector.
    std::vector<std::string> dot_map_files;

    std::cout << std::endl;
    std::cout << "The following maps were found and are going to be backed up: " << std::endl << std::endl;
    if ((dir = opendir(def_maps_path.c_str())) != NULL) {

        while ((ent = readdir (dir)) != NULL) {

            std::string map_name(ent->d_name);

            if ((ent->d_name[0] != '.') && (map_name.substr(map_name.size()-4) == ".map")) {

                std::cout << ent->d_name << std::endl;
                std::cout << def_maps_path+ent->d_name << std::endl << std::endl;
                
                // dot_map_files now contains the absolute path of our .map
                // files to replace.
                dot_map_files.push_back(def_maps_path+ent->d_name);

            }

        }
        closedir(dir);
    }

    std::cout << std::endl;
    std::cout << "Press ENTER to continue..." << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cin.ignore();

    // Finally do the actual system call to copy the files over.
    for (size_t i = 0; i < dot_map_files.size(); i++) {

        std::string cpycmd = "cp \""+dot_map_files[i]+"\" "+backup_maps_folder;
        // std::cout << cpycmd << std::endl;

        // Copy over files with system() cp command.
        std::cout << "Copying over "+dot_map_files[i] << std::endl << std::endl;
        const int cpy_err = system(cpycmd.c_str());

        if (cpy_err == -1) {
            std::cout << "Error backing up .map files." << std::endl;
            return 1;
        }

    }

    return 0;
}