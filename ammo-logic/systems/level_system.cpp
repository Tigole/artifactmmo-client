#include "level_system.hpp"

#include "keywords.hpp"
#include "managers/item_manager.hpp"
#include "managers/training_manager.hpp"

LevelSystem::LevelSystem(const char* skill) : System(skill), m_Skill(skill) {}

void LevelSystem::Fill_Pipeline(Character& character)
{
    int l_Min_Value         = std::numeric_limits<int>::max();
    int l_Max_Value         = std::numeric_limits<int>::min();
    std::size_t l_Min_Index = 0;

    if (character.Is_Task_Item() == true)
    {
        const std::string l_Item        = character.Get_Task();
        const ItemRequiredSkill l_Skill = ItemCraftingManager::singleton.Get_Required_Skill(l_Item.c_str());

        for (auto& r: l_Skill.requirements)
        {
            const int l_Skill_Level = character.Get_Skill_Level(r.first.c_str());
            if (l_Skill_Level < r.second)
            {
                Make_Train(character, r.first.c_str(), l_Skill_Level);
                return;
            }
        }
    }

    Make_Train(character, m_Skill, character.Get_Skill_Level(m_Skill));
}

void LevelSystem::Make_Train(Character& character, const char* skill_name, int skill_level) const
{
    /*if (strcmp(skill_name, Keywords::Skills::alchemy) == 0)
    {
        TrainingManager::singleton.Train_Alchemy(this, character, skill_level);
    }
    else if (strcmp(skill_name, Keywords::Skills::fishing) == 0)
    {
        TrainingManager::singleton.Train_Fishing(this, character, skill_level);
    }
    else if (strcmp(skill_name, Keywords::Skills::woodcutting) == 0)
    {
        TrainingManager::singleton.Train_Woodcutting(this, character, skill_level);
    }
    else if (strcmp(skill_name, Keywords::Skills::weaponcrafting) == 0)
    {
        TrainingManager::singleton.Train_Weaponcrafting(this, character, skill_level);
    }
    else if (strcmp(skill_name, Keywords::Skills::gearcrafting) == 0)
    {
        TrainingManager::singleton.Train_Gearcrafting(this, character, skill_level);
    }
    else if (strcmp(skill_name, Keywords::Skills::jewelrycrafting) == 0)
    {
        TrainingManager::singleton.Train_Jewelrycrafting(this, character, skill_level);
    }
    else if (strcmp(skill_name, Keywords::Skills::cooking) == 0)
    {
        TrainingManager::singleton.Train_Cooking(this, character, skill_level);
    }*/
}

GearcraftingLevelSystem GearcraftingLevelSystem::singleton;
WeaponcraftingLevelSystem WeaponcraftingLevelSystem::singleton;
JewelrycraftingLevelSystem JewelrycraftingLevelSystem::singleton;
CookingLevelSystem CookingLevelSystem::singleton;
AlchemyLevelSystem AlchemyLevelSystem::singleton;

void WeaponcraftingLevelSystem::Fill_Pipeline(Character& character)
{
    const int character_level = character.Get_Skill_Level(Keywords::Skills::weaponcrafting);
}
