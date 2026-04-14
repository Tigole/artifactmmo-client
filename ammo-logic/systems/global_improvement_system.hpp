#ifndef _GLOBAL_IMPROVEMENT_SYSTEM_HPP
#define _GLOBAL_IMPROVEMENT_SYSTEM_HPP 1

#include "system.hpp"

class GlobalImprovementSystem: public System
{
public:
    GlobalImprovementSystem(FightSystem& fight_system) : System("GlobalImprovementSystem"), m_Fight_System(fight_system)
    {
        m_Positions.push_back({ -1, 0 });  /// Ash Wood
        m_Positions.push_back({ 2, 0 });   /// Copper
        m_Positions.push_back({ 2, 2 });   /// Sunflower
        m_Positions.push_back({ 4, 2 });   /// Fish
    }

    void Fill_Pipeline(Character& pipeline) override
    {
        return;
        if (rand() % 100 < 50)
        {
            m_Fight_System.Fill_Pipeline(pipeline);
        }
        else if (rand() % 100 < 10)
        {
            if (rand() % 100 < 50)
            {
                pipeline.Add_Move(this, m_Positions[2 + rand() % 2]);
            }
            else
            {
                pipeline.Add_Move(this, m_Positions[rand() % 2]);
            }
            pipeline.Add_Gathering(this);
        }
    }

private:
    std::vector<MapCoord> m_Positions;
    FightSystem& m_Fight_System;
};

#endif  // _GLOBAL_IMPROVEMENT_SYSTEM_HPP
