#include "task_system.hpp"

#include "character/character.hpp"
#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"
#include "systems/fight_system.hpp"

TaskSystem::TaskSystem(const char* system_name, InventoryManager& inventory_management, ItemCraftingManager& item_crafting_manager,
                       FightSystem fight_system) :
    System(system_name),
    m_Inventory_Manager(inventory_management),
    m_Item_Crafting_Manager(item_crafting_manager),
    m_Fight_System(fight_system)
{}

void TaskSystem::Trade_Item(Character& character, int item_count) const
{
    const std::string l_Item   = character.Get_Task();
    const int l_Task_Remaining = character.Get_Task_Remaining();
    character.Add_Move(this, m_Item_Task_Master_Coord);
    character.Add_Task_Trade(this, { l_Item, std::min(l_Task_Remaining, item_count) });
    if (l_Task_Remaining <= item_count)
    {
        {
            character.Add_Move(this, m_Item_Task_Master_Coord);
            character.Add_Task_Complete(this);
        }
    }
}

TaskSystemMonster::TaskSystemMonster(InventoryManager& inventory_management, ItemCraftingManager& item_crafting_manager,
                                     FightSystem fight_system) :
    TaskSystem("TaskSystemMonster", inventory_management, item_crafting_manager, fight_system)
{}

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
            if (m_Fight_System.MayWin(character, character.Get_Task().c_str(), context) == true)
            {
                m_Fight_System.Fight_Against(this, character, character.Get_Task().c_str(), context);
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
        const int l_Task_Coin_Count = m_Inventory_Manager.Get_Bank_Item_Count("tasks_coin");
        m_Inventory_Manager.Deposit_Resources(this, character, character.Get_Task().c_str());

        if (l_Task_Coin_Count < 50)
        {
            character.Add_Move(this, m_Monster_Task_Master_Coord);
            character.Add_Task_New(this);
        }
    }
}

TaskSystemItem::TaskSystemItem(InventoryManager& inventory_management, ItemCraftingManager& item_crafting_manager,
                               FightSystem fight_system) :
    TaskSystem("TaskSystemItem", inventory_management, item_crafting_manager, fight_system)
{}

void TaskSystemItem::Fill_Pipeline(Character& character)
{
    if (character.Is_Task_Item() == true)
    {
        const std::string l_Item              = character.Get_Task();
        const int Bank_Item_Count             = m_Inventory_Manager.Get_Bank_Item_Count(l_Item.c_str());
        const int l_Task_Remaining            = character.Get_Task_Remaining();
        const int l_Inventory_Item_Count      = character.Get_Item_Count(l_Item.c_str());
        const int l_Inventory_Remaining_Space = character.Get_Inventory_Remaining_Space();
        if (l_Inventory_Remaining_Space > 0 && (l_Inventory_Item_Count < l_Task_Remaining))
        {
            if (Bank_Item_Count > 0)
            {
                const MapCoord Bank_Coord = m_Inventory_Manager.Get_Bank_Nearest_Coord(character);
                if (character.Should_Move(Bank_Coord))
                {
                    character.Add_Move(this, Bank_Coord);
                }
                else
                {
                    const int l_Item_Count = l_Task_Remaining - l_Inventory_Item_Count;
                    const int l_Count      = std::min(std::min(l_Item_Count, l_Inventory_Remaining_Space), Bank_Item_Count);
                    character.Add_Withdraw_Item(this, { l_Item, l_Count });
                    Trade_Item(character, l_Count);
                }
            }
            else if (m_Item_Crafting_Manager.May_Craft(character, l_Item.c_str()))
            {
                if ((l_Inventory_Item_Count < l_Task_Remaining) && (l_Inventory_Remaining_Space > 5))
                {
                    m_Item_Crafting_Manager.Make_Craft_Item(this, character, { l_Item, l_Task_Remaining });
                }
                else if (l_Inventory_Item_Count > 0)
                {
                    Trade_Item(character, l_Inventory_Item_Count);
                }
                else
                {
                    //
                }
            }
        }
        else
        {
            Trade_Item(character, std::min(l_Inventory_Item_Count, l_Task_Remaining));
        }
    }
    else if (character.Is_Task_Monster() == true)
    {
        // Drop
    }
    else
    {
        const int l_Task_Coin_Count = m_Inventory_Manager.Get_Bank_Item_Count("tasks_coin");

        printf("tasks_coin count: %d\n", l_Task_Coin_Count);
        if (l_Task_Coin_Count < 50)
        {
            m_Inventory_Manager.Deposit_Resources(this, character, character.Get_Task().c_str());
            character.Add_Move(this, m_Item_Task_Master_Coord);
            character.Add_Task_New(this);
        }
    }
}
