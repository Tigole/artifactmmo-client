#include "level_system.hpp"

#include "managers/item_manager.hpp"
#include "managers/training_manager.hpp"

LevelSystem::LevelSystem(TrainingManager& training_manager, ItemCraftingManager& item_crafting_manager, const char* skill) :
    System(skill), m_Training_Manager(training_manager), m_Item_Crafting_Manager(item_crafting_manager), m_Skill(skill)
{}

void LevelSystem::Fill_Pipeline(Character& character)
{
    int l_Min_Value         = std::numeric_limits<int>::max();
    int l_Max_Value         = std::numeric_limits<int>::min();
    std::size_t l_Min_Index = 0;

    if (character.Is_Task_Item() == true)
    {
        const std::string l_Item        = character.Get_Task();
        const ItemRequiredSkill l_Skill = m_Item_Crafting_Manager.Get_Required_Skill(l_Item.c_str());

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
    if (strcmp(skill_name, "alchemy") == 0)
    {
        m_Training_Manager.Train_Alchemy(character, skill_level);
    }
    else if (strcmp(skill_name, "fishing") == 0)
    {
        m_Training_Manager.Train_Fishing(character, skill_level);
    }
    else if (strcmp(skill_name, "woodcutting") == 0)
    {
        m_Training_Manager.Train_Woodcutting(character, skill_level);
    }
    else if (strcmp(skill_name, "weaponcrafting") == 0)
    {
        m_Training_Manager.Train_Weaponcrafting(character, skill_level);
    }
    else if (strcmp(skill_name, "gearcrafting") == 0)
    {
        m_Training_Manager.Train_Gearcrafting(character, skill_level);
    }
    else if (strcmp(skill_name, "jewelrycrafting") == 0)
    {
        m_Training_Manager.Train_Jewelrycrafting(character, skill_level);
    }
    else if (strcmp(skill_name, "cooking") == 0)
    {
        m_Training_Manager.Train_Cooking(character, skill_level);
    }
}
