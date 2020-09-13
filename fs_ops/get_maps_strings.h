#include <vector>
#include <string>
#include <algorithm>

bool in_vector(const std::string &value, const std::vector<std::string> &list);

std::vector<std::string> get_halo1_maps() {

    std::vector<std::string> halo1_maps;

    halo1_maps.push_back("a10.map");
    halo1_maps.push_back("a30.map");
    halo1_maps.push_back("a50.map");
    halo1_maps.push_back("b30.map");
    halo1_maps.push_back("b40.map");
    halo1_maps.push_back("c10.map");
    halo1_maps.push_back("c20.map");
    halo1_maps.push_back("c40.map");
    halo1_maps.push_back("d20.map");
    halo1_maps.push_back("d40.map");
    halo1_maps.push_back("ui.map");

    return halo1_maps;

}

std::vector<std::string> get_halo2_maps() {

    std::vector<std::string> halo2_maps;

    halo2_maps.push_back("00a_introduction.map");
    halo2_maps.push_back("01a_tutorial.map");
    halo2_maps.push_back("01b_spacestation.map");
    halo2_maps.push_back("03a_oldmombasa.map");
    halo2_maps.push_back("03b_newmombasa.map");
    halo2_maps.push_back("04a_gasgiant.map");
    halo2_maps.push_back("04b_floodlab.map");
    halo2_maps.push_back("05a_deltaapproach.map");
    halo2_maps.push_back("05b_deltatowers.map");
    halo2_maps.push_back("06a_sentinelwalls.map");
    halo2_maps.push_back("06b_floodzone.map");
    halo2_maps.push_back("07a_highcharity.map");
    halo2_maps.push_back("07b_forerunnership.map");
    halo2_maps.push_back("08a_deltacliffs.map");
    halo2_maps.push_back("08b_deltacontrol.map");
    halo2_maps.push_back("mainmenu.map");
    halo2_maps.push_back("shared.map");
    halo2_maps.push_back("single_player_shared.map");

    return halo2_maps;

}

std::vector<std::string> get_halo3_maps() {

    std::vector<std::string> halo3_maps;

    halo3_maps.push_back("005_intro.map");
    halo3_maps.push_back("010_jungle.map");
    halo3_maps.push_back("020_base.map");
    halo3_maps.push_back("030_outskirts.map");
    halo3_maps.push_back("040_voi.map");
    halo3_maps.push_back("050_floodvoi.map");
    halo3_maps.push_back("070_waste.map");
    halo3_maps.push_back("100_citadel.map");
    halo3_maps.push_back("110_hc.map");
    halo3_maps.push_back("120_halo.map");
    halo3_maps.push_back("130_epilogue.map");
    halo3_maps.push_back("armory.map");
    halo3_maps.push_back("bunkerworld.map");
    halo3_maps.push_back("campaign.map");
    halo3_maps.push_back("chill.map");
    halo3_maps.push_back("chillout.map");
    halo3_maps.push_back("construct.map");
    halo3_maps.push_back("cyberdyne.map");
    halo3_maps.push_back("deadlock.map");
    halo3_maps.push_back("descent.map");
    halo3_maps.push_back("docks.map");
    halo3_maps.push_back("fortress.map"); 
    halo3_maps.push_back("ghosttown.map"); 
    halo3_maps.push_back("guardian.map"); 
    halo3_maps.push_back("isolation.map"); 
    halo3_maps.push_back("lockout.map"); 
    halo3_maps.push_back("mainmenu.map"); 
    halo3_maps.push_back("midship.map"); 
    halo3_maps.push_back("riverworld.map"); 
    halo3_maps.push_back("salvation.map"); 
    halo3_maps.push_back("sandbox.map"); 
    halo3_maps.push_back("shared.map"); 
    halo3_maps.push_back("shrine.map"); 
    halo3_maps.push_back("sidewinder.map"); 
    halo3_maps.push_back("snowbound.map"); 
    halo3_maps.push_back("spacecamp.map"); 
    halo3_maps.push_back("warehouse.map");
    halo3_maps.push_back("zanzibar.map");

    return halo3_maps;

}

std::vector<std::string> get_haloreach_maps() {

    std::vector<std::string> haloreach_maps;

    haloreach_maps.push_back("20_sword_slayer.map");
    haloreach_maps.push_back("30_settlement.map");
    haloreach_maps.push_back("35_island.map");
    haloreach_maps.push_back("45_aftship.map");
    haloreach_maps.push_back("45_launch_station.map");
    haloreach_maps.push_back("50_panopticon.map");
    haloreach_maps.push_back("52_ivory_tower.map");
    haloreach_maps.push_back("70_boneyard.map");
    haloreach_maps.push_back("campaign.map");
    haloreach_maps.push_back("cex_beaver_creek.map");
    haloreach_maps.push_back("cex_damnation.map");
    haloreach_maps.push_back("cex_ff_halo.map");
    haloreach_maps.push_back("cex_hangemhigh.map");
    haloreach_maps.push_back("cex_headlong.map");
    haloreach_maps.push_back("cex_prisoner.map");
    haloreach_maps.push_back("cex_timberland.map");
    haloreach_maps.push_back("condemned.map");
    haloreach_maps.push_back("dlc_invasion.map");
    haloreach_maps.push_back("dlc_medium.map");
    haloreach_maps.push_back("dlc_slayer.map");
    haloreach_maps.push_back("ff_unearthed.map");
    haloreach_maps.push_back("ff10_prototype.map");
    haloreach_maps.push_back("ff20_courtyard.map");
    haloreach_maps.push_back("ff30_waterfront.map");
    haloreach_maps.push_back("ff45_corvette.map");
    haloreach_maps.push_back("ff50_park.map");
    haloreach_maps.push_back("ff60_airview.map");
    haloreach_maps.push_back("ff60_icecave.map");
    haloreach_maps.push_back("ff70_holdout.map");
    haloreach_maps.push_back("forge_halo.map");
    haloreach_maps.push_back("m05.map");
    haloreach_maps.push_back("m10.map");
    haloreach_maps.push_back("m20.map");
    haloreach_maps.push_back("m30.map");
    haloreach_maps.push_back("m35.map");
    haloreach_maps.push_back("m45.map");
    haloreach_maps.push_back("m50.map");
    haloreach_maps.push_back("m52.map");
    haloreach_maps.push_back("m60.map");
    haloreach_maps.push_back("m70_a.map");
    haloreach_maps.push_back("m70_bonus.map");
    haloreach_maps.push_back("m70.map");
    haloreach_maps.push_back("shared.map");
    haloreach_maps.push_back("trainingpreserve.map");

    return haloreach_maps;

}

bool check_validity(std::string map_name, std::string game_selected, std::vector<std::string> halo1_maps, std::vector<std::string> halo2_maps, std::vector<std::string> halo3_maps, std::vector<std::string> haloreach_maps) {

    if ( (game_selected == "halo1") && (in_vector(map_name, halo1_maps)) ) return true;

    else if ( (game_selected == "halo2") && (in_vector(map_name, halo2_maps)) ) return true;

    else if ((game_selected == "halo3") && (in_vector(map_name, halo3_maps)) ) return true;

    else if ( (game_selected == "haloreach") && (in_vector(map_name, haloreach_maps)) ) return true;

    return false;
}

bool in_vector(const std::string &value, const std::vector<std::string> &list) {

    return std::find(list.begin(), list.end(), value) != list.end();

}