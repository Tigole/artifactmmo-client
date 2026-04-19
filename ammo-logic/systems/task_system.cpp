#include "task_system.hpp"

#include "character/character.hpp"
#include "keywords.hpp"
#include "managers/achievement_manager.hpp"
#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"
#include "systems/fight_system.hpp"

TaskSystem::TaskSystem(const char* system_name) : System(system_name) {}

void TaskSystem::Trade_Item(Character& character, int item_count) const
{
    const std::string l_Item   = character.Get_Task();
    const int l_Task_Remaining = character.Get_Task_Remaining();
    character.Add_Move(this, m_Item_Task_Master_Coord);
    character.Add_Task_Trade(this, { l_Item, std::min(l_Task_Remaining, item_count) });
    if (l_Task_Remaining <= item_count)
    {
        character.Add_Task_Complete(this);
        character.Add_Move(this, InventoryManager::singleton.Get_Bank_Nearest_Coord(m_Item_Task_Master_Coord));
        character.Make_Clear_Inventory(this, nullptr);
    }
}

TaskSystemMonster::TaskSystemMonster() : TaskSystem("TaskSystemMonster") {}

void TaskSystemMonster::Fill_Pipeline(Character& character)
{
    if (character.Is_Task_Item() == true)
    {
        // Drop
    }
    else if (character.Is_Task_Monster() == true)
    {
        if (character.Get_Task_Remaining() > 0)
        {
            FightContext context;
            if (FightSystem::singleton.MayWin(character, character.Get_Task().c_str(), context) == true)
            {
                FightSystem::singleton.Fight_Against(this, character, character.Get_Task().c_str(), context);
            }
        }
        else
        {
            character.Add_Move(this, { 1, 2 });
            character.Add_Task_Complete(this);
        }
    }
    else
    {
        const int l_Task_Coin_Count = InventoryManager::singleton.Get_Bank_Item_Count(Keywords::Items::Currency::tasks_coin);

        if ((l_Task_Coin_Count < 50) || (AchivementManager::singleton.Is_Completed("tasks_farmer") == false))
        {
            character.Add_Move(this, m_Monster_Task_Master_Coord);
            character.Add_Task_New(this);
        }
    }
}

TaskSystemItem::TaskSystemItem() : TaskSystem("TaskSystemItem") {}

void TaskSystemItem::Fill_Pipeline(Character& character)
{
    if (character.Is_Task_Item() == true)
    {
        const std::string l_Item              = character.Get_Task();
        const int Bank_Item_Count             = InventoryManager::singleton.Get_Bank_Item_Count(l_Item.c_str());
        const int l_Task_Remaining            = character.Get_Task_Remaining();
        const int l_Inventory_Item_Count      = character.Get_Item_Count(l_Item.c_str());
        const int l_Inventory_Remaining_Space = character.Get_Inventory_Remaining_Space();
        if (l_Inventory_Remaining_Space > 0 && (l_Inventory_Item_Count < l_Task_Remaining))
        {
            if (Bank_Item_Count > 0)
            {
                const MapCoord Bank_Coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);
                if (character.Should_Move(Bank_Coord))
                {
                    character.Add_Move(this, Bank_Coord);
                    character.Make_Clear_Inventory(this, l_Item.c_str());
                }
                else
                {
                    const int l_Item_Count = l_Task_Remaining - l_Inventory_Item_Count;
                    const int l_Count      = std::min(std::min(l_Item_Count, l_Inventory_Remaining_Space), Bank_Item_Count);
                    SYSTEM_PRINT("Bank_Item_Count: %d l_Count: %d", Bank_Item_Count, l_Count);
                    character.Add_Withdraw_Item(this, { l_Item, l_Count });
                    Trade_Item(character, l_Count);
                }
            }
        }
        else
        {
            if (l_Inventory_Item_Count > 0)
            {
                Trade_Item(character, std::min(l_Inventory_Item_Count, l_Task_Remaining));
            }
        }
    }
    else if (character.Is_Task_Monster() == true)
    {
        // Drop
    }
    else
    {
        const int l_Task_Coin_Count = InventoryManager::singleton.Get_Bank_Item_Count(Keywords::Items::Currency::tasks_coin);

        printf("tasks_coin count: %d\n", l_Task_Coin_Count);
        if ((l_Task_Coin_Count < 50) || (AchivementManager::singleton.Is_Completed("tasks_farmer") == false))
        {
            character.Add_Move(this, m_Item_Task_Master_Coord);
            character.Add_Task_New(this);
        }
    }
}

TaskSystemMonster TaskSystemMonster::singleton;
TaskSystemItem TaskSystemItem::singleton;
