#include "level_system.hpp"

#include "keywords.hpp"
#include "managers/item_manager.hpp"
#include "managers/training_manager.hpp"

LevelCraftSystem::LevelCraftSystem(const char* name) : System(name) {}

void LevelCraftSystem::Fill_Pipeline(Character& character)
{
    const int character_level = character.Get_Skill_Level(m_Skill_Name);
    const char* item_code     = m_Default_Item_Code;

    if (character_level >= 10)
    {
        item_code = m_GT_10_Item_Code;
    }
    if (character_level >= 20)
    {
        item_code = m_GT_20_Item_Code;
    }
    if (character_level >= 30)
    {
        item_code = m_GT_30_Item_Code;
    }
    if (character_level >= 40)
    {
        item_code = m_GT_40_Item_Code;
    }

    if (character_level != 50)
    {
        const int craft_count = Make_Craft(character, m_Workshop_Coord, item_code, 100);
        if (craft_count > 0)
        {
            if (m_Recycle)
            {
                character.Add_Recycle_Item(this, { item_code, craft_count });
            }
            character.Make_Clear_Inventory(this, nullptr);
        }
    }
}

GearcraftingLevelSystem::GearcraftingLevelSystem() : LevelCraftSystem("GearcraftingLevelSystem")
{
    m_Skill_Name        = Keywords::Skills::gearcrafting;
    m_Default_Item_Code = Keywords::Items::Boots::copper_boots;
    m_GT_10_Item_Code   = Keywords::Items::Boots::iron_boots;
    m_GT_20_Item_Code   = Keywords::Items::Boots::steel_boots;
    m_GT_30_Item_Code   = Keywords::Items::Boots::gold_boots;
    m_GT_40_Item_Code   = Keywords::Items::Boots::mithril_boots;
    m_Workshop_Coord    = { 3, 1 };
}

WeaponcraftingLevelSystem::WeaponcraftingLevelSystem() : LevelCraftSystem("WeaponcraftingLevelSystem")
{
    m_Skill_Name        = Keywords::Skills::weaponcrafting;
    m_Default_Item_Code = Keywords::Items::Weapons::copper_dagger;
    m_GT_10_Item_Code   = Keywords::Items::Weapons::iron_sword;
    m_GT_20_Item_Code   = Keywords::Items::Weapons::battlestaff;
    m_GT_30_Item_Code   = Keywords::Items::Weapons::gold_sword;
    m_GT_40_Item_Code   = Keywords::Items::Weapons::mithril_sword;
    m_Workshop_Coord    = { 2, 1 };
}

JewelrycraftingLevelSystem::JewelrycraftingLevelSystem() : LevelCraftSystem("JewelrycraftingLevelSystem")
{
    m_Skill_Name        = Keywords::Skills::jewelrycrafting;
    m_Default_Item_Code = Keywords::Items::Rings::copper_ring;
    m_GT_10_Item_Code   = Keywords::Items::Rings::iron_ring;
    m_GT_20_Item_Code   = Keywords::Items::Rings::steel_ring;
    m_GT_30_Item_Code   = Keywords::Items::Rings::gold_ring;
    m_GT_40_Item_Code   = Keywords::Items::Rings::mithril_ring;
    m_Workshop_Coord    = { 1, 3 };
}

CookingLevelSystem::CookingLevelSystem() : LevelCraftSystem("CookingLevelSystem")
{
    m_Skill_Name        = Keywords::Skills::cooking;
    m_Default_Item_Code = Keywords::Items::Consumables::Food::cooked_gudgeon;
    m_GT_10_Item_Code   = Keywords::Items::Consumables::Food::cooked_shrimp;
    m_GT_20_Item_Code   = Keywords::Items::Consumables::Food::cooked_trout;
    m_GT_30_Item_Code   = Keywords::Items::Consumables::Food::cooked_bass;
    m_GT_40_Item_Code   = Keywords::Items::Consumables::Food::cooked_salmon;
    m_Workshop_Coord    = { 1, 1 };
    m_Recycle           = false;
}

AlchemyCraftLevelSystem::AlchemyCraftLevelSystem() : LevelCraftSystem("AlchemyCraftLevelSystem")
{
    m_Skill_Name        = Keywords::Skills::alchemy;
    m_Default_Item_Code = Keywords::Items::Utilities::small_health_potion;
    m_GT_10_Item_Code   = Keywords::Items::Utilities::water_boost_potion;
    m_GT_20_Item_Code   = Keywords::Items::Utilities::minor_health_potion;
    m_GT_30_Item_Code   = Keywords::Items::Utilities::health_potion;
    m_GT_40_Item_Code   = Keywords::Items::Utilities::greater_health_potion;
    m_Workshop_Coord    = { 2, 3 };
    m_Recycle           = false;
}

GearcraftingLevelSystem GearcraftingLevelSystem::singleton;
WeaponcraftingLevelSystem WeaponcraftingLevelSystem::singleton;
JewelrycraftingLevelSystem JewelrycraftingLevelSystem::singleton;
CookingLevelSystem CookingLevelSystem::singleton;
AlchemyCraftLevelSystem AlchemyCraftLevelSystem::singleton;

LevelGatherSystem::LevelGatherSystem(const char* name) : System(name) {}

void LevelGatherSystem::Fill_Pipeline(Character& character)
{
    const int character_level = character.Get_Skill_Level(m_Skill_Name);
    MapCoord spot_coord       = m_Default_Spot_Coord;

    if (character_level >= 10)
    {
        spot_coord = m_GT_10_Spot_Coord;
    }
    if (character_level >= 20)
    {
        spot_coord = m_GT_20_Spot_Coord;
    }
    if (character_level >= 30)
    {
        spot_coord = m_GT_30_Spot_Coord;
    }
    if (character_level >= 40)
    {
        spot_coord = m_GT_40_Spot_Coord;
    }

    if (character_level != 50)
    {
        Make_Gather(character, spot_coord, m_Skill_Name, *m_Equipements);
    }
}

#include "gather_system.hpp"

MiningLevelSystem::MiningLevelSystem() : LevelGatherSystem("MiningLevelSystem")
{
    m_Skill_Name         = Keywords::Skills::mining;
    m_Equipements        = &MiningGatheringSystem::singleton.Get_Equipements();
    m_Default_Spot_Coord = { 2, 0 };
    m_GT_10_Spot_Coord   = { 1, 7 };
    m_GT_20_Spot_Coord   = m_Default_Spot_Coord;
    m_GT_30_Spot_Coord   = m_Default_Spot_Coord;
    m_GT_40_Spot_Coord   = m_Default_Spot_Coord;
}

WoodcuttingLevelSystem::WoodcuttingLevelSystem() : LevelGatherSystem("WoodcuttingLevelSystem")
{
    m_Skill_Name         = Keywords::Skills::woodcutting;
    m_Equipements        = &WoodcuttingGatheringSystem::singleton.Get_Equipements();
    m_Default_Spot_Coord = { 6, 1 };
    m_GT_10_Spot_Coord   = { 2, 6 };
    m_GT_20_Spot_Coord   = { 3, 5 };
    m_GT_30_Spot_Coord   = m_Default_Spot_Coord;
    m_GT_40_Spot_Coord   = { 4, 14 };
}

FishingLevelSystem::FishingLevelSystem() : LevelGatherSystem("FishingLevelSystem")
{
    m_Skill_Name         = Keywords::Skills::fishing;
    m_Equipements        = &FishingGatherSystem::singleton.Get_Equipements();
    m_Default_Spot_Coord = { 4, 2 };
    m_GT_10_Spot_Coord   = { 5, 2 };
    m_GT_20_Spot_Coord   = { 7, 12 };
    m_GT_30_Spot_Coord   = { 6, 12 };
    m_GT_40_Spot_Coord   = { -2, -4 };
}

AlchemyGatherLevelSystem::AlchemyGatherLevelSystem() : LevelGatherSystem("AlchemyGatherLevelSystem")
{
    m_Skill_Name         = Keywords::Skills::alchemy;
    m_Equipements        = &AlchemyGatheringSystem::singleton.Get_Equipements();
    m_Default_Spot_Coord = { 2, 2 };
    m_GT_10_Spot_Coord   = m_Default_Spot_Coord;
    m_GT_20_Spot_Coord   = { 7, 14 };
    m_GT_30_Spot_Coord   = m_Default_Spot_Coord;
    m_GT_40_Spot_Coord   = { 1, 10 };
}

MiningLevelSystem MiningLevelSystem::singleton;
WoodcuttingLevelSystem WoodcuttingLevelSystem::singleton;
FishingLevelSystem FishingLevelSystem::singleton;
AlchemyGatherLevelSystem AlchemyGatherLevelSystem::singleton;
