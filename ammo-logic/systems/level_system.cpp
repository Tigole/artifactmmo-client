#include "level_system.hpp"

#include "keywords.hpp"
#include "managers/item_manager.hpp"
#include "managers/training_manager.hpp"

LevelSystem::LevelSystem(const char* name) : System(name) {}

void LevelSystem::Fill_Pipeline(Character& character)
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

GearcraftingLevelSystem::GearcraftingLevelSystem() : LevelSystem("GearcraftingLevelSystem")
{
    m_Skill_Name        = Keywords::Skills::gearcrafting;
    m_Default_Item_Code = Keywords::Items::Boots::copper_boots;
    m_GT_10_Item_Code   = Keywords::Items::Boots::iron_boots;
    m_GT_20_Item_Code   = Keywords::Items::Boots::steel_boots;
    m_GT_30_Item_Code   = Keywords::Items::Boots::gold_boots;
    m_GT_40_Item_Code   = Keywords::Items::Boots::mithril_boots;
    m_Workshop_Coord    = { 3, 1 };
}

WeaponcraftingLevelSystem::WeaponcraftingLevelSystem() : LevelSystem("WeaponcraftingLevelSystem")
{
    m_Skill_Name        = Keywords::Skills::weaponcrafting;
    m_Default_Item_Code = Keywords::Items::Weapons::copper_dagger;
    m_GT_10_Item_Code   = Keywords::Items::Weapons::iron_sword;
    m_GT_20_Item_Code   = Keywords::Items::Weapons::battlestaff;
    m_GT_30_Item_Code   = Keywords::Items::Weapons::gold_sword;
    m_GT_40_Item_Code   = Keywords::Items::Weapons::mithril_sword;
    m_Workshop_Coord    = { 2, 1 };
}

JewelrycraftingLevelSystem::JewelrycraftingLevelSystem() : LevelSystem("JewelrycraftingLevelSystem")
{
    m_Skill_Name        = Keywords::Skills::jewelrycrafting;
    m_Default_Item_Code = Keywords::Items::Rings::copper_ring;
    m_GT_10_Item_Code   = Keywords::Items::Rings::iron_ring;
    m_GT_20_Item_Code   = Keywords::Items::Rings::steel_ring;
    m_GT_30_Item_Code   = Keywords::Items::Rings::gold_ring;
    m_GT_40_Item_Code   = Keywords::Items::Rings::mithril_ring;
    m_Workshop_Coord    = { 1, 3 };
}

CookingLevelSystem::CookingLevelSystem() : LevelSystem("CookingLevelSystem")
{
    m_Skill_Name        = Keywords::Skills::cooking;
    m_Default_Item_Code = Keywords::Items::Consumables::Food::cooked_gudgeon;
    m_GT_10_Item_Code   = Keywords::Items::Consumables::Food::cooked_shrimp;
    m_GT_20_Item_Code   = Keywords::Items::Consumables::Food::cooked_trout;
    m_GT_30_Item_Code   = Keywords::Items::Consumables::Food::cooked_bass;
    m_GT_40_Item_Code   = Keywords::Items::Consumables::Food::cooked_salmon;
    m_Workshop_Coord    = { 1, 1 };
}

AlchemyLevelSystem::AlchemyLevelSystem() : LevelSystem("AlchemyLevelSystem")
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
AlchemyLevelSystem AlchemyLevelSystem::singleton;
