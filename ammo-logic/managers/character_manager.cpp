#include "character_manager.hpp"

#include "character/character.hpp"
#include "keywords.hpp"
#include "logic_application.hpp"

CharacterManager CharacterManager::singleton;

int CharacterManager::GetMinCombatLevel(void)
{
    int minLevel = 0;
    auto& p      = LogicApplication::singleton.Get_Pipelines();
    for (auto& c: p)
    {
        const Character& ch = c.Get_Character_Obj();
        minLevel            = std::min(minLevel, ch.Get_Skill_Level(Keywords::Skills::combat));
    }
    return minLevel;
}
