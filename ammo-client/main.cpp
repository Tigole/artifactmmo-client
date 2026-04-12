#include <array>
#include <iostream>

#include "character/character_pipeline.hpp"
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
#include "systems/alchemy_system.hpp"
#include "systems/cooking_system.hpp"
#include "systems/craft_system.hpp"
#include "systems/fight_equipement_system.hpp"
#include "systems/fight_system.hpp"
#include "systems/fishing_system.hpp"
#include "systems/gather_system.hpp"
#include "systems/gearcrafting_system.hpp"
#include "systems/global_improvement_system.hpp"
#include "systems/inventory_management_system.hpp"
#include "systems/level_system.hpp"
#include "systems/mining_system.hpp"
#include "systems/stuff_system.hpp"
#include "systems/task_system.hpp"
#include "systems/tool_craft_system.hpp"
#include "systems/woodcutting_system.hpp"
#include "ui/ui.hpp"

int main(int argc, char** argv)
{
    Client l_Client;
    Token::LoadFromFile("token.txt");
    l_Client.Initialize();

    MapManager l_Map_Manager(l_Client);
    ResourceManager l_Resource_Manager;
    ItemManager l_Items_Manager;
    InventoryManager l_Inventory_Manager(l_Client, l_Items_Manager);
    MonsterManager l_Monsters_Manager(l_Map_Manager);
    FightSystem l_Fight_System(l_Monsters_Manager, l_Items_Manager, l_Inventory_Manager);
    NPCManager l_NPC_Manager;
    ItemCraftingManager l_Item_Crafting_Manager(l_Resource_Manager, l_Items_Manager, l_Inventory_Manager, l_NPC_Manager, l_Fight_System);
    AchievementFightSystem l_Achievement_Fight_System(l_Fight_System);
    TrainingManager l_Training_Manager(l_Item_Crafting_Manager);
    CraftSystem l_Craft_System(l_Items_Manager);
    GlobalImprovementSystem l_Global_Improvement_System(l_Fight_System);
    GearcraftingSystem l_Gearcrafting_System(l_Item_Crafting_Manager, l_Inventory_Manager);
    StuffSystem l_Stuff_System(l_Items_Manager, l_Item_Crafting_Manager);
    TaskSystem l_Task_System(l_Inventory_Manager, l_Item_Crafting_Manager, l_Fight_System);
    GearcraftingLevelSystem l_Gearcrafting_Level_System(l_Training_Manager, l_Item_Crafting_Manager);
    WeaponcraftingLevelSystem l_Weaponcrafting_Level_System(l_Training_Manager, l_Item_Crafting_Manager);
    JewelrycraftingLevelSystem l_Jewelrycrafting_Level_System(l_Training_Manager, l_Item_Crafting_Manager);
    CookingLevelSystem l_Cooking_Level_System(l_Training_Manager, l_Item_Crafting_Manager);
    AlchemyLevelSystem l_Alchemy_Level_System(l_Training_Manager, l_Item_Crafting_Manager);
    InventoryManagementSystem l_Inventory_Management_System(l_Inventory_Manager);
    FightEquipementSystem l_Fight_Equipement_System(l_Inventory_Manager);
    AlchemySystem l_Alchemy_System(l_Item_Crafting_Manager, l_Inventory_Manager);
    CookingSystem l_Cooking_System(l_Item_Crafting_Manager, l_Inventory_Manager);
    WoodcuttingSystem l_Woodcutting_System(l_Item_Crafting_Manager, l_Inventory_Manager);
    FishingSystem l_Fishing_System(l_Item_Crafting_Manager, l_Inventory_Manager);
    ToolCraftSystem l_Tool_Craft_System(l_Item_Crafting_Manager, l_Inventory_Manager);
    MiningSystem l_Mining_System(l_Item_Crafting_Manager, l_Inventory_Manager);
    std::array<CharacterPipeline, 5> l_Pipeline = {
        { CharacterPipeline(l_Client, l_Inventory_Manager), CharacterPipeline(l_Client, l_Inventory_Manager),
         CharacterPipeline(l_Client, l_Inventory_Manager), CharacterPipeline(l_Client, l_Inventory_Manager),
         CharacterPipeline(l_Client, l_Inventory_Manager) }
    };
    CharacterPipeline& l_Gear_Crafting_Pipeling = l_Pipeline[0];
    auto clk                                    = std::chrono::high_resolution_clock::now();
    ArtifactUI l_UI(l_Pipeline);

    l_Pipeline[0].Set_Character("Niva");
    l_Pipeline[1].Set_Character("Jackie");
    l_Pipeline[2].Set_Character("Eldra");
    l_Pipeline[3].Set_Character("Randy");
    l_Pipeline[4].Set_Character("Helen");

    // l_Gear_Crafting_Pipeling.Add_System(&l_Gearcrafting_System);

    l_Pipeline[0].Add_System(&l_Inventory_Management_System);
    l_Pipeline[0].Add_System(&l_Tool_Craft_System);
    l_Pipeline[0].Add_System(&l_Woodcutting_System);
    l_Pipeline[0].Add_System(&l_Fight_Equipement_System);
    l_Pipeline[0].Add_System(&l_Stuff_System);
    l_Pipeline[0].Add_System(&l_Task_System);
    l_Pipeline[0].Add_System(&l_Weaponcrafting_Level_System);
    l_Pipeline[0].Add_System(&l_Global_Improvement_System);
    l_Pipeline[0].Add_System(&l_Achievement_Fight_System);

    l_Pipeline[1].Add_System(&l_Inventory_Management_System);
    l_Pipeline[1].Add_System(&l_Alchemy_System);
    l_Pipeline[1].Add_System(&l_Fight_Equipement_System);
    l_Pipeline[1].Add_System(&l_Stuff_System);
    l_Pipeline[1].Add_System(&l_Task_System);
    l_Pipeline[1].Add_System(&l_Alchemy_Level_System);
    l_Pipeline[1].Add_System(&l_Global_Improvement_System);
    l_Pipeline[1].Add_System(&l_Achievement_Fight_System);

    l_Pipeline[2].Add_System(&l_Inventory_Management_System);
    l_Pipeline[2].Add_System(&l_Mining_System);
    l_Pipeline[2].Add_System(&l_Gearcrafting_System);
    l_Pipeline[2].Add_System(&l_Fight_Equipement_System);
    l_Pipeline[2].Add_System(&l_Stuff_System);
    l_Pipeline[2].Add_System(&l_Task_System);
    l_Pipeline[2].Add_System(&l_Gearcrafting_Level_System);
    l_Pipeline[2].Add_System(&l_Global_Improvement_System);
    l_Pipeline[2].Add_System(&l_Achievement_Fight_System);

    l_Pipeline[3].Add_System(&l_Inventory_Management_System);
    l_Pipeline[3].Add_System(&l_Cooking_System);
    l_Pipeline[3].Add_System(&l_Fight_Equipement_System);
    l_Pipeline[3].Add_System(&l_Stuff_System);
    l_Pipeline[3].Add_System(&l_Task_System);
    l_Pipeline[3].Add_System(&l_Cooking_Level_System);
    l_Pipeline[3].Add_System(&l_Global_Improvement_System);
    l_Pipeline[3].Add_System(&l_Achievement_Fight_System);

    l_Pipeline[4].Add_System(&l_Inventory_Management_System);
    l_Pipeline[4].Add_System(&l_Fishing_System);
    l_Pipeline[4].Add_System(&l_Fight_Equipement_System);
    l_Pipeline[4].Add_System(&l_Stuff_System);
    l_Pipeline[4].Add_System(&l_Task_System);
    l_Pipeline[4].Add_System(&l_Jewelrycrafting_Level_System);
    l_Pipeline[4].Add_System(&l_Global_Improvement_System);
    l_Pipeline[4].Add_System(&l_Achievement_Fight_System);

    l_Map_Manager.Initialize();
    l_Resource_Manager.Initialize(l_Client, l_Map_Manager);
    l_Monsters_Manager.Initialize(l_Client);
    l_Items_Manager.Initialize(l_Client, l_Monsters_Manager);
    l_NPC_Manager.Initialize(l_Client);

    l_Fight_System.Initialize();
    l_Craft_System.Initialize();

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
    for (;;)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        const float elapsed_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - clk).count() * 0.001f;
        for (std::size_t ii = 0; ii < l_Characters_To_Update.size(); ii++)
        {
            CharacterPipeline& p = l_Pipeline[l_Characters_To_Update[ii]];
            p.Update(elapsed_time);
        }
        l_UI.Update(elapsed_time);
        l_UI.Render();
        clk = std::chrono::high_resolution_clock::now();
    }

    return 0;
}
