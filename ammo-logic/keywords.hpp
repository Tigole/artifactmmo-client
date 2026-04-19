#ifndef _KEYWORDS_HPP
#define _KEYWORDS_HPP 1

#define KEYWORD(key) static constexpr const char* key = #key

struct Keywords
{
    struct Skills
    {
        KEYWORD(combat);
        KEYWORD(weaponcrafting);
        KEYWORD(alchemy);
        KEYWORD(fishing);
        KEYWORD(woodcutting);
        KEYWORD(gearcrafting);
        KEYWORD(jewelrycrafting);
        KEYWORD(cooking);
        KEYWORD(mining);
    };

    struct Items
    {
        struct Weapons
        {
            KEYWORD(iron_sword);
            KEYWORD(fire_staff);
            KEYWORD(water_bow);
            KEYWORD(sticky_sword);
            KEYWORD(wooden_staff);
            KEYWORD(sticky_dagger);
            KEYWORD(copper_dagger);

            KEYWORD(iron_dagger);
            KEYWORD(fire_bow);
            KEYWORD(king_slime_sword);
            KEYWORD(mushstaff);
            KEYWORD(mushmush_bow);
            KEYWORD(highwayman_dagger);
            KEYWORD(battlestaff);
            KEYWORD(forest_whip);
            KEYWORD(steel_battleaxe);
            KEYWORD(skull_staff);
            KEYWORD(hunting_bow);
            KEYWORD(shuriken);
            KEYWORD(dreadful_staff);
            KEYWORD(skull_wand);
            KEYWORD(wooden_club);
            KEYWORD(vampire_bow);
            KEYWORD(greater_dreadful_staff);
            KEYWORD(death_knight_sword);
            KEYWORD(gold_sword);
            KEYWORD(elderwood_staff);
            KEYWORD(enchanted_bow);
            KEYWORD(magic_bow);
            KEYWORD(cursed_sceptre);
            KEYWORD(strangold_sword);
            KEYWORD(dreadful_battleaxe);
            KEYWORD(diamond_sword);
            KEYWORD(sanguine_edge_of_rosen);
            KEYWORD(mithril_sword);
            KEYWORD(lightning_sword);
            KEYWORD(bloodblade);
            KEYWORD(wrathsword);
            KEYWORD(mithril_axe);
            KEYWORD(bow_from_hell);
            KEYWORD(hell_staff);
            KEYWORD(demoniac_dagger);
            KEYWORD(blade_of_hell);
            KEYWORD(hell_reaper);
            KEYWORD(desert_whip);
            KEYWORD(adamantite_sword);
            KEYWORD(dust_sword);
            KEYWORD(moonlight_staff);

            struct Tools
            {
                struct Axes
                {
                    KEYWORD(voidstone_axe);
                    KEYWORD(adamantite_axe);
                    KEYWORD(mithril_axe);
                    KEYWORD(gold_axe);
                    KEYWORD(steel_axe);
                    KEYWORD(iron_axe);
                    KEYWORD(copper_axe);
                };

                struct Pickaxes
                {
                    KEYWORD(voidstone_pickaxe);
                    KEYWORD(adamantite_pickaxe);
                    KEYWORD(mithril_pickaxe);
                    KEYWORD(gold_pickaxe);
                    KEYWORD(steel_pickaxe);
                    KEYWORD(iron_pickaxe);
                    KEYWORD(copper_pickaxe);
                };

                struct Gloves
                {
                    KEYWORD(voidstone_gloves);
                    KEYWORD(adamantite_gloves);
                    KEYWORD(mithril_gloves);
                    KEYWORD(golden_gloves);
                    KEYWORD(steel_gloves);
                    KEYWORD(leather_gloves);
                    KEYWORD(apprentice_gloves);
                };

                struct FishingRods
                {
                    KEYWORD(voidstone_fishing_rod);
                    KEYWORD(adamantite_fishing_rod);
                    KEYWORD(mithril_fishing_rod);
                    KEYWORD(gold_fishing_rod);
                    KEYWORD(steel_fishing_rod);
                    KEYWORD(spruce_fishing_rod);
                    KEYWORD(fishing_net);
                };
            };
        };

        struct BodyArmors
        {
            KEYWORD(feather_coat);
            KEYWORD(copper_armor);
            KEYWORD(leather_armor);
            KEYWORD(iron_armor);
            KEYWORD(adventurer_vest);
            KEYWORD(mushmush_jacket);
            KEYWORD(steel_armor);
            KEYWORD(skeleton_armor);
            KEYWORD(hard_leather_armor);
            KEYWORD(bandit_armor);
            KEYWORD(lizard_skin_armor);
            KEYWORD(snakeskin_armor);
            KEYWORD(piggy_armor);
            KEYWORD(stormforged_armor);
            KEYWORD(gold_platebody);
            KEYWORD(obsidian_armor);
            KEYWORD(royal_skeleton_armor);
            KEYWORD(conjurer_cloak);
            KEYWORD(strangold_armor);
            KEYWORD(malefic_armor);
            KEYWORD(dreadful_armor);
            KEYWORD(mithril_platebody);
            KEYWORD(cultist_cloak);
            KEYWORD(wratharmor);
            KEYWORD(white_knight_armor);
            KEYWORD(hell_armor);
            KEYWORD(sand_snakeskin_armor);
            KEYWORD(darkforged_plate);
            KEYWORD(mesh_armor);
            KEYWORD(vital_armor);
            KEYWORD(duskarmor);
            KEYWORD(adamantite_platebody);
            KEYWORD(skullforged_armor);
        };

        struct LegArmors
        {
            KEYWORD(copper_legs_armor);
            KEYWORD(iron_legs_armor);
            KEYWORD(leather_legs_armor);
            KEYWORD(adventurer_pants);
            KEYWORD(steel_legs_armor);
            KEYWORD(skeleton_pants);
            KEYWORD(hard_leather_pants);
            KEYWORD(snakeskin_legs_armor);
            KEYWORD(lizard_skin_legs_armor);
            KEYWORD(piggy_pants);
            KEYWORD(stormforged_pants);
            KEYWORD(gold_platelegs);
            KEYWORD(obsidian_legs_armor);
            KEYWORD(royal_skeleton_pants);
            KEYWORD(conjurer_skirt);
            KEYWORD(strangold_legs_armor);
            KEYWORD(ancient_jean);
            KEYWORD(enchanter_pants);
            KEYWORD(mithril_platelegs);
            KEYWORD(cultist_pants);
            KEYWORD(wrathpants);
            KEYWORD(white_knight_pants);
            KEYWORD(hell_legs_armor);
            KEYWORD(sand_snakeskin_pants);
            KEYWORD(mesh_legs_armor);
            KEYWORD(duskpants);
            KEYWORD(adamantite_platelegs);
            KEYWORD(skullforged_pants);
        };

        struct Helmets
        {
            KEYWORD(copper_helmet);
            KEYWORD(adventurer_helmet);
            KEYWORD(iron_helm);
            KEYWORD(leather_hat);
            KEYWORD(mushmush_wizard_hat);
            KEYWORD(lucky_wizard_hat);
            KEYWORD(wolf_ears);
            KEYWORD(magic_wizard_hat);
            KEYWORD(steel_helm);
            KEYWORD(skeleton_helmet);
            KEYWORD(tromatising_mask);
            KEYWORD(hard_leather_helmet);
            KEYWORD(piggy_helmet);
            KEYWORD(lich_crown);
            KEYWORD(gold_mask);
            KEYWORD(gold_helm);
            KEYWORD(obsidian_helmet);
            KEYWORD(royal_skeleton_helmet);
            KEYWORD(cursed_hat);
            KEYWORD(strangold_helmet);
            KEYWORD(jester_hat);
            KEYWORD(batwing_helmet);
            KEYWORD(hork_helmet);
            KEYWORD(mithril_helm);
            KEYWORD(cultist_hat);
            KEYWORD(wrathelmet);
            KEYWORD(white_knight_helmet);
            KEYWORD(corrupted_crown);
            KEYWORD(hell_helmet);
            KEYWORD(sand_snakeskin_bandana);
            KEYWORD(darkforged_helmet);
            KEYWORD(desert_wrap);
            KEYWORD(dark_horned_helmet);
            KEYWORD(adamantite_mask);
            KEYWORD(dust_helmet);
        };

        struct Boots
        {
            KEYWORD(copper_boots);
            KEYWORD(iron_boots);
            KEYWORD(leather_boots);
            KEYWORD(adventurer_boots);
            KEYWORD(steel_boots);
            KEYWORD(snakeskin_boots);
            KEYWORD(old_boots);
            KEYWORD(hard_leather_boots);
            KEYWORD(lizard_boots);
            KEYWORD(gold_boots);
            KEYWORD(flying_boots);
            KEYWORD(enchanter_boots);
            KEYWORD(cultist_boots);
            KEYWORD(mithril_boots);
            KEYWORD(sand_snakeskin_boots);
            KEYWORD(darkforged_boots);
            KEYWORD(vital_boots);
            KEYWORD(adamantite_boots);
        };

        struct Shields
        {
            KEYWORD(wooden_shield);
            KEYWORD(iron_shield);
            KEYWORD(slime_shield);
            KEYWORD(gold_shield);
            KEYWORD(dreadful_shield);
            KEYWORD(goblin_guard_shield);
            KEYWORD(fire_shield);
            KEYWORD(water_shield);
            KEYWORD(air_shield);
            KEYWORD(earth_shield);
            KEYWORD(mithril_shield);
            KEYWORD(white_knight_shield);
            KEYWORD(demoniac_shield);
            KEYWORD(darkforged_shield);
            KEYWORD(adamantite_shield);
            KEYWORD(magic_shield);
        };

        struct Rings
        {
            KEYWORD(copper_ring);
            KEYWORD(iron_ring);
            KEYWORD(forest_ring);
            KEYWORD(air_ring);
            KEYWORD(earth_ring);
            KEYWORD(fire_ring);
            KEYWORD(life_ring);
            KEYWORD(water_ring);
            KEYWORD(ring_of_chance);
            KEYWORD(dreadful_ring);
            KEYWORD(steel_ring);
            KEYWORD(skull_ring);
            KEYWORD(ring_of_the_adept);
            KEYWORD(ruby_ring);
            KEYWORD(topaz_ring);
            KEYWORD(gold_ring);
            KEYWORD(sapphire_ring);
            KEYWORD(emerald_ring);
            KEYWORD(royal_skeleton_ring);
            KEYWORD(malefic_ring);
            KEYWORD(sacred_ring);
            KEYWORD(divinity_ring);
            KEYWORD(eternity_ring);
            KEYWORD(celest_ring);
            KEYWORD(mithril_ring);
            KEYWORD(hell_ring);
            KEYWORD(adamantite_ring);
            KEYWORD(skullforged_ring);
            KEYWORD(eternal_red_ring);
        };

        struct Consumables
        {
            struct Food
            {
                KEYWORD(cooked_gudgeon);
                KEYWORD(cooked_chicken);
                KEYWORD(apple);
                KEYWORD(cooked_beef);
                KEYWORD(fried_eggs);
                KEYWORD(cooked_shrimp);
                KEYWORD(cheese);
                KEYWORD(cooked_wolf_meat);
                KEYWORD(mushroom_soup);
                KEYWORD(cooked_trout);
                KEYWORD(apple_pie);
                KEYWORD(cookie);
                KEYWORD(cooked_bass);
                KEYWORD(cooked_rat_meat);
                KEYWORD(corrupted_fruit);
                KEYWORD(fish_soup);
                KEYWORD(cooked_salmon);
                KEYWORD(cooked_hellhound_meat);
                KEYWORD(maple_syrup);
                KEYWORD(cooked_swordfish);
                KEYWORD(coconut);
                KEYWORD(cooked_desert_scorpion_meat);
            };

            struct Bags
            {
                KEYWORD(bag_of_gold);
                KEYWORD(small_bag_of_gold);
            };

            struct Teleport
            {
                KEYWORD(recall_potion);
                KEYWORD(forest_bank_potion);
            };
        };

        struct Utilities
        {
            KEYWORD(small_health_potion);
            KEYWORD(earth_boost_potion);
            KEYWORD(air_boost_potion);
            KEYWORD(fire_boost_potion);
            KEYWORD(water_boost_potion);
            KEYWORD(minor_health_potion);
            KEYWORD(small_antidote);
            KEYWORD(health_potion);
            KEYWORD(antidote);
            KEYWORD(health_splash_potion);
            KEYWORD(greater_health_potion);
            KEYWORD(health_boost_potion);
            KEYWORD(enchanted_boost_potion);
            KEYWORD(earth_res_potion);
            KEYWORD(fire_res_potion);
            KEYWORD(water_res_potion);
            KEYWORD(air_res_potion);
            KEYWORD(enchanted_health_potion);
            KEYWORD(diabolic_elixir);
            KEYWORD(enchanted_antidote);
            KEYWORD(enchanted_health_splash_potion);
        };

        struct Resources
        {
            struct Mining
            {
                KEYWORD(copper_ore);
                KEYWORD(iron_ore);
                KEYWORD(coal);
                KEYWORD(emerald_stone);
                KEYWORD(topaz_stone);
                KEYWORD(ruby_stone);
                KEYWORD(sapphire_stone);
                KEYWORD(gold_ore);
                KEYWORD(strange_ore);
                KEYWORD(diamond_stone);
                KEYWORD(mithril_ore);
                KEYWORD(adamantite_ore);
                KEYWORD(alexandrite_stone);
            };

            struct Bar
            {
                KEYWORD(copper_bar);
                KEYWORD(iron_bar);
                KEYWORD(steel_bar);
                KEYWORD(gold_bar);
                KEYWORD(obsidian_bar);
                KEYWORD(strangold_bar);
                KEYWORD(mithril_bar);
                KEYWORD(adamantite_bar);
            };

            struct Woodcutting
            {
                KEYWORD(ash_wood);
                KEYWORD(spruce_wood);
                KEYWORD(birch_wood);
                KEYWORD(dead_wood);
                KEYWORD(magic_wood);
                KEYWORD(maple_wood);
                KEYWORD(palm_wood);
            };

            struct Sap
            {
                KEYWORD(sap);
                KEYWORD(magic_sap);
                KEYWORD(maple_sap);
            };

            struct Plank
            {
                KEYWORD(ash_plank);
                KEYWORD(spruce_plank);
                KEYWORD(hardwood_plank);
                KEYWORD(dead_wood_plank);
                KEYWORD(magical_plank);
                KEYWORD(cursed_plank);
                KEYWORD(maple_plank);
                KEYWORD(palm_plank);
            };

            struct Fishing
            {
                KEYWORD(gudgeon);
                KEYWORD(algae);
                KEYWORD(shell);
                KEYWORD(shrimp);
                KEYWORD(golden_shrimp);
                KEYWORD(trout);
                KEYWORD(small_pearls);
                KEYWORD(bass);
                KEYWORD(salmon);
                KEYWORD(swordfish);
                KEYWORD(holey_boot);
            };

            struct Alchemy
            {
                KEYWORD(sunflower);
                KEYWORD(nettle_leaf);
                KEYWORD(glowstem_leaf);
                KEYWORD(torch_cactus_flower);
            };

            struct Mob
            {
                KEYWORD(raw_chicken);
                KEYWORD(egg);
                KEYWORD(feather);
                KEYWORD(raw_beef);
                KEYWORD(milk_bucket);
                KEYWORD(wool);
                KEYWORD(golden_egg);
                KEYWORD(yellow_slimeball);
                KEYWORD(green_slimeball);
                KEYWORD(blue_slimeball);
                KEYWORD(red_slimeball);
                KEYWORD(cowhide);
                KEYWORD(mushroom);
                KEYWORD(flying_wing);
                KEYWORD(snake_hide);
                KEYWORD(raw_wolf_meat);
                KEYWORD(wolf_bone);
                KEYWORD(wolf_hair);
                KEYWORD(green_cloth);
                KEYWORD(king_slimeball);
                KEYWORD(skeleton_bone);
                KEYWORD(skeleton_skull);
                KEYWORD(ogre_skin);
                KEYWORD(ogre_eye);
                KEYWORD(pig_skin);
                KEYWORD(spider_leg);
                KEYWORD(vampire_blood);
                KEYWORD(vampire_tooth);
                KEYWORD(lizard_skin);
                KEYWORD(cyclops_eye);
                KEYWORD(lizard_eye);
                KEYWORD(rat_hide);
                KEYWORD(red_cloth);
                KEYWORD(demoniac_dust);
                KEYWORD(imp_tail);
                KEYWORD(owlbear_hair);
                KEYWORD(demon_horn);
                KEYWORD(piece_of_obsidian);
                KEYWORD(owlbear_claw);
                KEYWORD(life_crystal_shard);
                KEYWORD(raw_rat_meat);
                KEYWORD(cursed_book);
                KEYWORD(corrupted_stone);
                KEYWORD(goblin_tooth);
                KEYWORD(goblin_eye);
                KEYWORD(malefic_cloth);
                KEYWORD(cursed_wood);
                KEYWORD(malefic_shard);
                KEYWORD(goblin_guard_foot);
                KEYWORD(priestess_orb);
                KEYWORD(wolfrider_ponytail);
                KEYWORD(bat_wing);
                KEYWORD(orc_skin);
                KEYWORD(orc_bone);
                KEYWORD(rosenblood_elixir);
                KEYWORD(wolfrider_hair);
                KEYWORD(broken_sword);
                KEYWORD(hellhound_hair);
                KEYWORD(raw_hellhound_meat);
                KEYWORD(book_from_hell);
                KEYWORD(efreet_cloth);
                KEYWORD(page_from_hell);
                KEYWORD(elemental_page);
                KEYWORD(dark_essence);
                KEYWORD(cursed_flask);
                KEYWORD(hellhound_collar);
                KEYWORD(grimlet_bone);
                KEYWORD(lava_bucket);
                KEYWORD(sand_snake_hide);
                KEYWORD(marauder_hand);
                KEYWORD(dusk_beetle_shell);
                KEYWORD(duskworm_skin);
                KEYWORD(golden_dust);
                KEYWORD(adventurer_skull);
                KEYWORD(codex_page);
                KEYWORD(desert_scorpion_carapace);
                KEYWORD(desert_scorpion_meat);
                KEYWORD(sand_snake_poison);
            };

            struct NPC
            {
                KEYWORD(cloth);
                KEYWORD(hard_leather);
                KEYWORD(snakeskin);
                KEYWORD(vermin_leather);
                KEYWORD(sand_snakeskin);
            };

            struct Task
            {
                KEYWORD(jasper_crystal);
                KEYWORD(magical_cure);
                KEYWORD(astralyte_crystal);
                KEYWORD(enchanted_fabric);
            };

            struct PreciousStone
            {
                KEYWORD(sapphire);
                KEYWORD(emerald);
                KEYWORD(ruby);
                KEYWORD(topaz);
                KEYWORD(diamond);
                KEYWORD(alexandrite);
            };

            struct Key
            {
                KEYWORD(lich_tomb_key);
                KEYWORD(priestess_hideout_key);
                KEYWORD(sandwhisper_key);
            };
        };

        struct Currency
        {
            KEYWORD(tasks_coin);
            KEYWORD(event_ticket);
            KEYWORD(corrupted_gem);
            KEYWORD(sandwhisper_coin);
        };

        struct Amulets
        {
            KEYWORD(life_amulet);
            KEYWORD(fire_and_earth_amulet);
            KEYWORD(air_and_water_amulet);
            KEYWORD(wisdom_amulet);
            KEYWORD(dreadful_amulet);
            KEYWORD(skull_amulet);
            KEYWORD(topaz_amulet);
            KEYWORD(emerald_amulet);
            KEYWORD(sapphire_amulet);
            KEYWORD(ruby_amulet);
            KEYWORD(greater_dreadful_amulet);
            KEYWORD(lost_amulet);
            KEYWORD(prospecting_amulet);
            KEYWORD(diamond_amulet);
            KEYWORD(corrupted_stone_amulet);
            KEYWORD(masterful_necklace);
            KEYWORD(ancestral_talisman);
            KEYWORD(greater_emerald_amulet);
            KEYWORD(greater_sapphire_amulet);
            KEYWORD(greater_topaz_amulet);
            KEYWORD(greater_ruby_amulet);
            KEYWORD(heart_amulet);
            KEYWORD(dust_amulet);
            KEYWORD(amulet_of_the_grand_master);
        };
    };
};

#endif  // _KEYWORDS_HPP
