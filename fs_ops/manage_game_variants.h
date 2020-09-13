#include <iostream>
#include <string>

int add_Game_and_Map_Variants(std::string mcc_file_path, std::string def_maps_path, std::string mod_path, std::string game_selected) {

    // Look inside of mod folder and check to see
    // if a folder 'game_variants' exists.

    std::string selected_halo_game_variant_dir = mcc_file_path+game_selected+"/game_variants/";
    std::string selected_halo_map_variant_dir = mcc_file_path+game_selected+"/map_variants/";
    std::string mods_game_variants = mod_path+"game_variants/";
    std::string mods_map_variants = mod_path+"map_variants/";

    // std::cout << selected_halo_game_variant_dir << std::endl;
    // std::cout << mods_game_variants << std::endl;

    // std::cout << selected_halo_map_variant_dir << std::endl;
    // std::cout << mods_map_variants << std::endl;

    DIR *dir;
    struct dirent *ent;

    // If there are gamemodes in the mod, 
    if (PathExists(mod_path+"game_variants")) {

        std::cout << std::endl << "A 'game_variants/' folder was found within the mod." << std::endl;
        std::cout << "Copying game variants over to "+game_selected+"/game_variants/" << std::endl << std::endl;

        if ((dir = opendir(mods_game_variants.c_str())) != NULL) {

            while ((ent = readdir (dir)) != NULL) {

                std::string map_name(ent->d_name);

                if ((ent->d_name[0] != '.') && (map_name.substr(map_name.size()-4) != ".bin")) {
                    std::cout << "Invalid game variant found in "+game_selected << std::endl;
                    return 1;
                }

                if ((ent->d_name[0] != '.') && (map_name.substr(map_name.size()-4) == ".bin")) {
                    std::string cpycmd = "cp \""+mods_game_variants+map_name+"\" \""+selected_halo_game_variant_dir+"\"";
                    system(cpycmd.c_str());
                }

            }
            closedir(dir);
        }

    }

    // Halo 1 and Halo 2 don't accept standard map variants.
    if ( (game_selected != "halo1") && (game_selected != "halo2") ) {

        // If there are map variants in the mod, 
        if (PathExists(mod_path+"map_variants")) {

            std::cout << std::endl << "A 'map_variants/' folder was found within the mod." << std::endl;
            std::cout << "Copying map variants over to "+game_selected+"/map_variants/" << std::endl << std::endl;

            if ((dir = opendir(mods_map_variants.c_str())) != NULL) {

                while ((ent = readdir (dir)) != NULL) {
                    
                    std::string map_name(ent->d_name);

                    if ((ent->d_name[0] != '.') && (map_name.substr(map_name.size()-5) != ".mvar")) {
                        std::cout << "Invalid map variant found in "+game_selected << std::endl;
                        std::cout << map_name << std::endl;
                        return 1;
                    }

                    if ((ent->d_name[0] != '.') && (map_name.substr(map_name.size()-5) == ".mvar")) {
                        std::string cpycmd = "cp \""+mods_map_variants+map_name+"\" \""+selected_halo_map_variant_dir+"\"";
                        system(cpycmd.c_str());
                    }   

                }
                closedir(dir);
            }

        }

    }

    return 0;

}