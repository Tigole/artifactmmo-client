#include "achievement_fight_system.hpp"

#include <random>

#include "fight_system.hpp"
#include "managers/monster_manager.hpp"
#include "net/client.hpp"

AchievementFightSystem AchievementFightSystem::singleton;

AchievementFightSystem::AchievementFightSystem() : System("AchievementFightSystem")
{
    // m_Target_Monsters.push_back({ 0, 100, "orc" });
    // // m_Target_Monsters.push_back("chicken");
    // m_Target_Monsters.push_back({ 0, 100, "bandit_lizard" });
    // m_Target_Monsters.push_back({ 0, 100, "wolf" });
    // m_Target_Monsters.push_back({ 0, 100, "pig" });
    // m_Target_Monsters.push_back({ 0, 100, "cultist_emperor" });
    // m_Target_Monsters.push_back({ 0, 100, "spider" });
    // m_Target_Monsters.push_back({ 0, 100, "highwayman" });
    // m_Target_Monsters.push_back({ 0, 100, "rosenblood" });
    // m_Target_Monsters.push_back({ 0, 100, "demon" });
    // m_Target_Monsters.push_back({ 0, 100, "lich" });
    // m_Target_Monsters.push_back({ 0, 100, "goblin_wolfrider" });
    // m_Target_Monsters.push_back({ 0, 100, "cultist_acolyte" });
    // m_Target_Monsters.push_back({ 0, 100, "efreet_sultan" });
    // m_Target_Monsters.push_back({ 0, 100, "grimlet" });
}

void AchievementFightSystem::Initialize(void)
{
    Client::singleton.Get_Achievement_Kill(m_Target_Monsters);
}

void AchievementFightSystem::Fill_Pipeline(Character& pipeline)
{
    static auto rng    = std::default_random_engine {};
    bool l_Should_Heal = false;

    for (std::size_t ii = 0; ii < m_Target_Monsters.size(); ii++)
    {
        AchievementProgress ap  = m_Target_Monsters[ii];
        const char* l_Monster   = ap.target.c_str();
        const MapCoord* l_Coord = MonsterManager::singleton.Get_Monster_Coord(l_Monster, pipeline.Get_Map_Coord());
        FightContext fight_context;
        if ((l_Coord != nullptr) && (ap.progress < ap.total) &&
            (FightSystem::singleton.MayWin(pipeline, l_Monster, FightConfig::MonsterTaskConfig(ap.total - ap.progress), fight_context) ==
             true))
        {
            FightSystem::singleton.Fight_Against(this, pipeline, l_Monster, fight_context);
            ap.progress++;
            return;
        }
    }
}
