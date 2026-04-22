#include "logic_application.hpp"

#include "character/character_pipeline.hpp"
#include "managers/achievement_manager.hpp"
#include "managers/fight_manager.hpp"
#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"
#include "managers/map_manager.hpp"
#include "managers/monster_manager.hpp"
#include "managers/npc_manager.hpp"
#include "managers/resource_manager.hpp"
#include "managers/training_manager.hpp"
#include "net/client.hpp"
#include "net/token.hpp"
#include "systems/achievement_fight_system.hpp"
#include "systems/craft_order_system.hpp"
#include "systems/fight_equipement_system.hpp"
#include "systems/fight_system.hpp"
#include "systems/gather_system.hpp"
#include "systems/inventory_management_system.hpp"
#include "systems/level_system.hpp"
#include "systems/stuff_system.hpp"
#include "systems/task_system.hpp"

void LogicApplication::Run(int argc, char** argv)
{
    auto clk                                     = std::chrono::high_resolution_clock::now();
    std::array<CharacterPipeline, 5>& l_Pipeline = m_Pipeline;

    Token::LoadFromFile("token.txt");
    Client::singleton.Initialize();

    {
        InventoryManager::singleton.Initialize();

        MonsterManager::singleton.Initialize();
        NPCManager::singleton.Initialize();
        ItemCraftingManager::singleton.Initialize();
        MapManager::singleton.Initialize();
        ResourceManager::singleton.Initialize();
        MonsterManager::singleton.Initialize();
        ItemManager::singleton.Initialize();
        NPCManager::singleton.Initialize();
        AchivementManager::singleton.Initialize();

        FightSystem::singleton.Initialize();
        // CraftSystem::sin l_Craft_System.Initialize();
    }

    {
        static constexpr int idx = 0;
        l_Pipeline[idx].Set_Character("Niva");
        l_Pipeline[idx].Add_System(&InventoryManagementSystem::singleton);
        l_Pipeline[idx].Add_System(&ToolCraftSystem::singleton);
        l_Pipeline[idx].Add_System(&WeaponCraftSystem::singleton);
        l_Pipeline[idx].Add_System(&TaskSystemMonster::singleton);
        l_Pipeline[idx].Add_System(&WeaponcraftingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingCraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&MobGatherSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyCraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&FishingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyGatherLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&AchievementFightSystem::singleton);
    }

    {
        static constexpr int idx = 1;
        l_Pipeline[idx].Set_Character("Jackie");
        l_Pipeline[idx].Add_System(&InventoryManagementSystem::singleton);
        l_Pipeline[idx].Add_System(&CookingSystem::singleton);
        l_Pipeline[idx].Add_System(&TaskSystemItem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyCraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningCraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingCraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&FishingGatherSystem::singleton);
        l_Pipeline[idx].Add_System(&MobGatherSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyCraftLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&FishingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyGatherLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&AchievementFightSystem::singleton);
    }

    {
        static constexpr int idx = 2;
        l_Pipeline[idx].Set_Character("Eldra");
        l_Pipeline[idx].Add_System(&InventoryManagementSystem::singleton);
        l_Pipeline[idx].Add_System(&BuyingSystem::singleton);
        l_Pipeline[idx].Add_System(&TaskSystemItem::singleton);
        l_Pipeline[idx].Add_System(&GearcraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningCraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&FishingGatherSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingCraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&MobGatherSystem::singleton);
        l_Pipeline[idx].Add_System(&GearcraftingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&FishingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyGatherLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&AchievementFightSystem::singleton);
    }

    {
        static constexpr int idx = 3;
        l_Pipeline[idx].Set_Character("Randy");
        l_Pipeline[idx].Add_System(&InventoryManagementSystem::singleton);
        l_Pipeline[idx].Add_System(&CookingSystem::singleton);
        l_Pipeline[idx].Add_System(&WeaponCraftSystem::singleton);
        l_Pipeline[idx].Add_System(&TaskSystemMonster::singleton);
        l_Pipeline[idx].Add_System(&FishingGatherSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&FishingGatherSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingCraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningCraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&MobGatherSystem::singleton);
        l_Pipeline[idx].Add_System(&CookingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyCraftLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyGatherLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&FishingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&AchievementFightSystem::singleton);
    }

    {
        static constexpr int idx = 4;
        l_Pipeline[idx].Set_Character("Helen");
        l_Pipeline[idx].Add_System(&InventoryManagementSystem::singleton);
        l_Pipeline[idx].Add_System(&TaskSystemItem::singleton);
        l_Pipeline[idx].Add_System(&FishingGatherSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingGatheringSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningCraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&JewerlyCraftSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingCraftingSystem::singleton);
        l_Pipeline[idx].Add_System(&MobGatherSystem::singleton);
        l_Pipeline[idx].Add_System(&JewelrycraftingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&FishingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&AlchemyGatherLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&WoodcuttingLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&MiningLevelSystem::singleton);
        l_Pipeline[idx].Add_System(&AchievementFightSystem::singleton);
    }

    std::vector<std::size_t> l_Characters_To_Update = { 0, 1, 2, 3, 4 };
    if (argc > 1)
    {
        l_Characters_To_Update.clear();
        for (std::size_t ii = 0; ii < l_Pipeline.size(); ii++)
        {
            for (int a = 1; a < argc; a++)
            {
                if (strcmp(argv[a], l_Pipeline[ii].Get_Character()) == 0)
                {
                    l_Characters_To_Update.push_back(ii);
                }
            }
        }
    }

    m_Initialized                    = true;
    float achievement_update_timeout = 0.0f;
    for (;;)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        const float elapsed_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - clk).count() * 0.001f;
        clk = std::chrono::high_resolution_clock::now();

        achievement_update_timeout -= elapsed_time;
        if (achievement_update_timeout <= 0.0f)
        {
            achievement_update_timeout = 60.0f * 5.0f;
            AchivementManager::singleton.Update_Cache();
        }
        for (std::size_t ii = 0; ii < l_Characters_To_Update.size(); ii++)
        {
            CharacterPipeline& p = l_Pipeline[l_Characters_To_Update[ii]];
            p.Update(elapsed_time);
        }
    }
}

const std::array<CharacterPipeline, 5>& LogicApplication::Get_Pipelines(void) const
{
    return m_Pipeline;
}

bool LogicApplication::Is_Initialized(void) const
{
    return m_Initialized;
}
