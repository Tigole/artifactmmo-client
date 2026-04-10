#ifndef _ACHIEVEMENT_FIGHT_SYSTEM_HPP
#define _ACHIEVEMENT_FIGHT_SYSTEM_HPP 1

#include "system.hpp"

class FightSystem;

class AchievementFightSystem: public System
{
public:
    AchievementFightSystem(FightSystem& fight_system);

    void Fill_Pipeline(Character& pipeline) override;

private:
    FightSystem& m_Fight_System;
    std::vector<std::string> m_Target_Monsters;
};

#endif  // _ACHIEVEMENT_FIGHT_SYSTEM_HPP
