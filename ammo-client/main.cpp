#include <array>
#include <iostream>

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
#include "systems/craft_system.hpp"
#include "systems/fight_equipement_system.hpp"
#include "systems/fight_system.hpp"
#include "systems/gather_system.hpp"
#include "systems/global_improvement_system.hpp"
#include "systems/inventory_management_system.hpp"
#include "systems/level_system.hpp"
#include "systems/stuff_system.hpp"
#include "systems/task_system.hpp"
#include "ui/ui.hpp"

int main(int argc, char** argv)
{
    Token::LoadFromFile("token.txt");
    Client::singleton.Initialize();
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

    std::array<CharacterPipeline, 5> l_Pipeline = {
        { CharacterPipeline(), CharacterPipeline(), CharacterPipeline(), CharacterPipeline(), CharacterPipeline() }
    };
    CharacterPipeline& l_Gear_Crafting_Pipeling = l_Pipeline[0];
    auto clk                                    = std::chrono::high_resolution_clock::now();
    ArtifactUI l_UI(l_Pipeline);

    l_Pipeline[0].Set_Character("Niva");
    l_Pipeline[1].Set_Character("Jackie");
    l_Pipeline[2].Set_Character("Eldra");
    l_Pipeline[3].Set_Character("Randy");
    l_Pipeline[4].Set_Character("Helen");

    // l_Gear_Crafting_Pipeling.Add_System(&GearcraftingSystem::singleton);

    l_Pipeline[0].Add_System(&InventoryManagementSystem::singleton);
    l_Pipeline[0].Add_System(&ToolCraftSystem::singleton);
    // l_Pipeline[0].Add_System(&FightEquipementSystem::singleton);
    l_Pipeline[0].Add_System(&WoodcuttingCraftingSystem::singleton);
    l_Pipeline[0].Add_System(&WoodcuttingGatheringSystem::singleton);
    l_Pipeline[0].Add_System(&MiningGatheringSystem::singleton);
    l_Pipeline[0].Add_System(&AlchemyGatheringSystem::singleton);
    // l_Pipeline[0].Add_System(&StuffSystem::singleton);
    //  l_Pipeline[0].Add_System(&l_Task_System_Monster);
    l_Pipeline[0].Add_System(&WeaponcraftingLevelSystem::singleton);
    l_Pipeline[0].Add_System(&GlobalImprovementSystem::singleton);
    l_Pipeline[0].Add_System(&AchievementFightSystem::singleton);

    l_Pipeline[1].Add_System(&InventoryManagementSystem::singleton);
    l_Pipeline[1].Add_System(&TaskSystemItem::singleton);
    l_Pipeline[1].Add_System(&AlchemyCraftingSystem::singleton);
    l_Pipeline[1].Add_System(&AlchemyGatheringSystem::singleton);
    l_Pipeline[1].Add_System(&MiningGatheringSystem::singleton);
    l_Pipeline[1].Add_System(&WoodcuttingGatheringSystem::singleton);
    // l_Pipeline[1].Add_System(&FightEquipementSystem::singleton);
    // l_Pipeline[1].Add_System(&StuffSystem::singleton);
    l_Pipeline[1].Add_System(&AlchemyLevelSystem::singleton);
    l_Pipeline[1].Add_System(&GlobalImprovementSystem::singleton);
    l_Pipeline[1].Add_System(&AchievementFightSystem::singleton);

    l_Pipeline[2].Add_System(&InventoryManagementSystem::singleton);
    l_Pipeline[2].Add_System(&TaskSystemItem::singleton);
    l_Pipeline[2].Add_System(&GearcraftingSystem::singleton);
    l_Pipeline[2].Add_System(&MiningCraftingSystem::singleton);
    l_Pipeline[2].Add_System(&MiningGatheringSystem::singleton);
    l_Pipeline[2].Add_System(&WoodcuttingGatheringSystem::singleton);
    // l_Pipeline[2].Add_System(&FightEquipementSystem::singleton);
    // l_Pipeline[2].Add_System(&StuffSystem::singleton);
    l_Pipeline[2].Add_System(&GearcraftingLevelSystem::singleton);
    l_Pipeline[2].Add_System(&GlobalImprovementSystem::singleton);
    l_Pipeline[2].Add_System(&AchievementFightSystem::singleton);

    l_Pipeline[3].Add_System(&InventoryManagementSystem::singleton);
    l_Pipeline[3].Add_System(&TaskSystemItem::singleton);
    l_Pipeline[3].Add_System(&CookingSystem::singleton);
    l_Pipeline[3].Add_System(&AlchemyGatheringSystem::singleton);
    l_Pipeline[3].Add_System(&WoodcuttingGatheringSystem::singleton);
    l_Pipeline[3].Add_System(&MiningGatheringSystem::singleton);
    // l_Pipeline[3].Add_System(&FightEquipementSystem::singleton);
    // l_Pipeline[3].Add_System(&StuffSystem::singleton);
    l_Pipeline[3].Add_System(&CookingLevelSystem::singleton);
    l_Pipeline[3].Add_System(&GlobalImprovementSystem::singleton);
    l_Pipeline[3].Add_System(&AchievementFightSystem::singleton);

    l_Pipeline[4].Add_System(&InventoryManagementSystem::singleton);
    l_Pipeline[4].Add_System(&TaskSystemItem::singleton);
    l_Pipeline[4].Add_System(&FishingGatherSystem::singleton);
    l_Pipeline[4].Add_System(&AlchemyGatheringSystem::singleton);
    l_Pipeline[4].Add_System(&MiningGatheringSystem::singleton);
    l_Pipeline[4].Add_System(&WoodcuttingGatheringSystem::singleton);
    // l_Pipeline[4].Add_System(&FightEquipementSystem::singleton);
    // l_Pipeline[4].Add_System(&StuffSystem::singleton);
    l_Pipeline[4].Add_System(&JewelrycraftingLevelSystem::singleton);
    l_Pipeline[4].Add_System(&GlobalImprovementSystem::singleton);
    l_Pipeline[4].Add_System(&AchievementFightSystem::singleton);

    std::vector<std::size_t> l_Characters_To_Update = { 0, 1, 2, 3, 4 };
    // std::vector<std::size_t> l_Characters_To_Update = { 3 };
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

    l_UI.Initialize();
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
        l_UI.Update(elapsed_time);
        l_UI.Render();
    }

    return 0;
}
