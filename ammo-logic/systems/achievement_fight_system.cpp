#include "achievement_fight_system.hpp"

#include <random>

#include "fight_system.hpp"

AchievementFightSystem::AchievementFightSystem(FightSystem& fight_system) : System("AchievementFightSystem"), m_Fight_System(fight_system)
{
    m_Target_Monsters.push_back("orc");
    // m_Target_Monsters.push_back("chicken");
    m_Target_Monsters.push_back("bandit_lizard");
    m_Target_Monsters.push_back("wolf");
    m_Target_Monsters.push_back("pig");
    m_Target_Monsters.push_back("cultist_emperor");
    m_Target_Monsters.push_back("spider");
    m_Target_Monsters.push_back("highwayman");
    m_Target_Monsters.push_back("rosenblood");
    m_Target_Monsters.push_back("demon");
    m_Target_Monsters.push_back("lich");
    m_Target_Monsters.push_back("goblin_wolfrider");
    m_Target_Monsters.push_back("cultist_acolyte");
    m_Target_Monsters.push_back("efreet_sultan");
    m_Target_Monsters.push_back("grimlet");
}

void AchievementFightSystem::Fill_Pipeline(Character& pipeline)
{
    static auto rng    = std::default_random_engine {};
    bool l_Should_Heal = false;
    std::vector<std::size_t> l_Indices;

    l_Indices.resize(m_Target_Monsters.size());
    for (std::size_t ii = 0; ii < m_Target_Monsters.size(); ii++)
    {
        l_Indices[ii] = ii;
    }
    std::shuffle(l_Indices.begin(), l_Indices.end(), rng);

    for (std::size_t ii = 0; ii < l_Indices.size(); ii++)
    {
        const char* l_Monster   = m_Target_Monsters[l_Indices[ii]].c_str();
        const MapCoord* l_Coord = m_Fight_System.Get_Monster_Coord(l_Monster);
        FightContext fight_context;
        if ((l_Coord != nullptr) && (m_Fight_System.MayWin(pipeline, l_Monster, fight_context) == true))
        {
            pipeline.Add_Move(*l_Coord);
            if (fight_context.should_heal == true)
            {
                m_Fight_System.Add_Healing(pipeline);
            }
            pipeline.Add_Fight();
            return;
        }
    }
}
