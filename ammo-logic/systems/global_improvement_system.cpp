#include "global_improvement_system.hpp"

#include "fight_system.hpp"

GlobalImprovementSystem GlobalImprovementSystem::singleton;

GlobalImprovementSystem::GlobalImprovementSystem() : System("GlobalImprovementSystem")
{
    m_Positions.push_back({ -1, 0 });  /// Ash Wood
    m_Positions.push_back({ 2, 0 });   /// Copper
    m_Positions.push_back({ 2, 2 });   /// Sunflower
    m_Positions.push_back({ 4, 2 });   /// Fish
}

void GlobalImprovementSystem::Fill_Pipeline(Character& pipeline)
{
    return;
    if (rand() % 100 < 50)
    {
        FightSystem::singleton.Fill_Pipeline(pipeline);
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
