#ifndef _LEVEL_SYSTEM_HPP
#define _LEVEL_SYSTEM_HPP 1

#include "system.hpp"

class ItemCraftingManager;
class TrainingManager;

class LevelSystem: public System
{
public:
    LevelSystem(TrainingManager& training_manager, ItemCraftingManager& item_crafting_manager, const char* skill);

    void Fill_Pipeline(Character& character) override;

private:
    TrainingManager& m_Training_Manager;
    ItemCraftingManager& m_Item_Crafting_Manager;
    const char* m_Skill;

    void Make_Train(Character& character, const char* skill_name, int skill_level) const;
};

class GearcraftingLevelSystem: public LevelSystem
{
public:
    GearcraftingLevelSystem(TrainingManager& training_manager, ItemCraftingManager& item_crafting_manager) :
        LevelSystem(training_manager, item_crafting_manager, "gearcrafting")
    {}
};

class WeaponcraftingLevelSystem: public LevelSystem
{
public:
    WeaponcraftingLevelSystem(TrainingManager& training_manager, ItemCraftingManager& item_crafting_manager) :
        LevelSystem(training_manager, item_crafting_manager, "weaponcrafting")
    {}
};

class JewelrycraftingLevelSystem: public LevelSystem
{
public:
    JewelrycraftingLevelSystem(TrainingManager& training_manager, ItemCraftingManager& item_crafting_manager) :
        LevelSystem(training_manager, item_crafting_manager, "jewelrycrafting")
    {}
};

class CookingLevelSystem: public LevelSystem
{
public:
    CookingLevelSystem(TrainingManager& training_manager, ItemCraftingManager& item_crafting_manager) :
        LevelSystem(training_manager, item_crafting_manager, "cooking")
    {}
};

class AlchemyLevelSystem: public LevelSystem
{
public:
    AlchemyLevelSystem(TrainingManager& training_manager, ItemCraftingManager& item_crafting_manager) :
        LevelSystem(training_manager, item_crafting_manager, "alchemy")
    {}
};

#endif  // _LEVEL_SYSTEM_HPP
