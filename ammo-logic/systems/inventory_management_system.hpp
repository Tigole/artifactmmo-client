#ifndef _INVENTORY_MANAGEMENT_SYSTEM_HPP
#define _INVENTORY_MANAGEMENT_SYSTEM_HPP 1

#include "system.hpp"

class InventoryManager;

class InventoryManagementSystem: public System
{
    InventoryManagementSystem();

public:
    static InventoryManagementSystem singleton;

    void Fill_Pipeline(Character& character) override;

private:
    bool Has_Task_Item(Character& character);
};

#endif  // _INVENTORY_MANAGEMENT_SYSTEM_HPP
