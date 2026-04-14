#ifndef _TASK_SYSTEM_HPP
#define _TASK_SYSTEM_HPP 1

#include "systems/system.hpp"
#include "types.hpp"

class InventoryManager;
class ItemCraftingManager;
class FightSystem;
class Character;

class TaskSystem: public System
{
public:
    TaskSystem(const char* system_name);

protected:
    const MapCoord m_Item_Task_Master_Coord    = { 4, 13 };
    const MapCoord m_Monster_Task_Master_Coord = { 1, 2 };

    void Trade_Item(Character& character, int item_count) const;
};

class TaskSystemMonster: public TaskSystem
{
    TaskSystemMonster();

public:
    static TaskSystemMonster singleton;

    void Fill_Pipeline(Character& character) override;
};

class TaskSystemItem: public TaskSystem
{
    TaskSystemItem();

public:
    static TaskSystemItem singleton;

    void Fill_Pipeline(Character& character) override;
};

#endif  // _TASK_SYSTEM_HPP
