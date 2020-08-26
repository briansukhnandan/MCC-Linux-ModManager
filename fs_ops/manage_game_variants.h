#include <iostream>
#include <string>

int add_Game_Variants(std::string def_maps_path, std::string mod_path, std::string game_selected) {

    // Look inside of mod folder and check to see
    // if a folder 'game_variants' exists.

    //TODO TEST

    std::string selected_halo_game_variant_dir = def_maps_path+game_selected+"/"+"game_variants/"
    std::string mods_game_variants = mod_path+"game_variants/";

    std::string cpycmd = "cp "+mods_game_variants+"* "+selected_halo_game_variant_dir;

    // If there are gamemodes in the mod, 
    if (PathExists(mod_path+"game_variants")) {
        std::cout << std::endl << "A 'game_variants/' folder was found within the mod." << std::endl;

        if ((dir = opendir(def_maps_path.c_str())) != NULL) {

            while ((ent = readdir (dir)) != NULL) {

                std::string map_name(ent->d_name);

                if ((ent->d_name[0] != '.') && (map_name.substr(map_name.size()-4) != ".bin")) {
                    std::cout << "Invalid game variant found in game_"
                    return 1;
                }

            }
            closedir(dir);
        }

        system(cpycmd.c_str());

    }

    return 0;

}