#ifndef _ACHIEVEMENT_FIGHT_SYSTEM_HPP
#define _ACHIEVEMENT_FIGHT_SYSTEM_HPP 1

#include "system.hpp"

class FightSystem;

class AchievementFightSystem: public System
{
    AchievementFightSystem();

public:
    static AchievementFightSystem singleton;

    void Initialize(void);

    void Fill_Pipeline(Character& pipeline) override;

private:
    std::vector<AchievementProgress> m_Target_Monsters;
};

#endif  // _ACHIEVEMENT_FIGHT_SYSTEM_HPP
