#ifndef _TRAINING_MANAGER_HPP
#define _TRAINING_MANAGER_HPP 1

class Character;
class ItemCraftingManager;
class System;

class TrainingManager
{
public:
    TrainingManager(ItemCraftingManager& item_crafting_manager);

    void Train_Woodcutting(const System* sys, Character& character, int skill_level);
    void Train_Fishing(const System* sys, Character& character, int skill_level);
    void Train_Weaponcrafting(const System* sys, Character& character, int skill_level);
    void Train_Gearcrafting(const System* sys, Character& character, int skill_level);
    void Train_Jewelrycrafting(const System* sys, Character& character, int skill_level);
    void Train_Cooking(const System* sys, Character& character, int skill_level);
    void Train_Alchemy(const System* sys, Character& character, int skill_level);

private:
    ItemCraftingManager& m_Item_Crafting_Manager;

    void Make_Craft_One_Of(const System* sys, Character& character, const char* item_code) const;
};

#endif  // _TRAINING_MANAGER_HPP
