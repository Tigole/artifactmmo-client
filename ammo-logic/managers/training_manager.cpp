#include "training_manager.hpp"

#include "character/character.hpp"
#include "managers/item_manager.hpp"

TrainingManager::TrainingManager(ItemCraftingManager& item_crafting_manager) : m_Item_Crafting_Manager(item_crafting_manager) {}

void TrainingManager::Train_Woodcutting(const System* sys, Character& character, int skill_level)
{
    if (skill_level < 10)
    {
        Make_Craft_One_Of(sys, character, "ash_wood");
    }
}

void TrainingManager::Train_Fishing(const System* sys, Character& character, int skill_level)
{
    if (skill_level < 10)
    {
        Make_Craft_One_Of(sys, character, "gudgeon");
    }
}

void TrainingManager::Train_Weaponcrafting(const System* sys, Character& character, int skill_level)
{
    Make_Craft_One_Of(sys, character, "copper_dagger");
    /*if ((character.Get_Equiped_Weapon() == "copper_dagger") && (character.Get_Item_Count("copper_dagger") > 0))
    {
        m_Item_Crafting_Manager.Make_Recycle_Item(character, { "copper_dagger", character.Get_Item_Count("copper_dagger") });
    }*/
}

void TrainingManager::Train_Gearcrafting(const System* sys, Character& character, int skill_level)
{
    if (skill_level < 5)
    {
        Make_Craft_One_Of(sys, character, "wooden_shield");
        /*if ((character.Get_Equiped_Shield() == "wooden_shield") && (character.Get_Item_Count("wooden_shield") > 0))
        {
            m_Item_Crafting_Manager.Make_Recycle_Item(character, { "wooden_shield", character.Get_Item_Count("wooden_shield") });
        }*/
    }
    else if (skill_level < 10)
    {
        Make_Craft_One_Of(sys, character, "feather_coat");
    }
}

void TrainingManager::Train_Jewelrycrafting(const System* sys, Character& character, int skill_level)
{
    Make_Craft_One_Of(sys, character, "copper_ring");
    /*if (character.Get_Item_Count("copper_ring") > 0)
    {
        if (character.Get_Equiped_Ring1() != "copper_ring")
        {
            character.Add_Equip_Item("ring1", "copper_ring");
        }
        else if (character.Get_Equiped_Ring2() != "copper_ring")
        {
            character.Add_Equip_Item("ring2", "copper_ring");
        }
        else
        {
            m_Item_Crafting_Manager.Make_Recycle_Item(character, { "copper_ring", character.Get_Item_Count("copper_ring") });
        }
    }*/
}

void TrainingManager::Train_Cooking(const System* sys, Character& character, int skill_level)
{
    //
}

void TrainingManager::Train_Alchemy(const System* sys, Character& character, int skill_level)
{
    if (skill_level < 5)
    {
        Make_Craft_One_Of(sys, character, "sunflower");
    }
    else if (skill_level < 10)
    {
        Make_Craft_One_Of(sys, character, "small_health_potion");
    }
}

void TrainingManager::Make_Craft_One_Of(const System* sys, Character& character, const char* item_code) const
{
    m_Item_Crafting_Manager.Make_Craft_Item(sys, character, { item_code, character.Get_Item_Count(item_code) + 1 });
}
