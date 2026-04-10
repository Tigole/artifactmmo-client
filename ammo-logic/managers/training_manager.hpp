#ifndef _TRAINING_MANAGER_HPP
#define _TRAINING_MANAGER_HPP 1

class Character;
class ItemCraftingManager;

class TrainingManager
{
public:
    TrainingManager(ItemCraftingManager& item_crafting_manager);

    void Train_Woodcutting(Character& character, int skill_level);
    void Train_Fishing(Character& character, int skill_level);
    void Train_Weaponcrafting(Character& character, int skill_level);
    void Train_Gearcrafting(Character& character, int skill_level);
    void Train_Jewelrycrafting(Character& character, int skill_level);
    void Train_Cooking(Character& character, int skill_level);
    void Train_Alchemy(Character& character, int skill_level);

private:
    ItemCraftingManager& m_Item_Crafting_Manager;

    void Make_Craft_One_Of(Character& character, const char* item_code) const;
};

#endif  // _TRAINING_MANAGER_HPP
