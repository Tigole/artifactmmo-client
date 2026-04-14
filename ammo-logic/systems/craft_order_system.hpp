#ifndef _CRAFT_ORDER_SYSTEM_HPP
#define _CRAFT_ORDER_SYSTEM_HPP 1

#include "system.hpp"

class ItemCraftingManager;
class InventoryManager;

struct CraftOrder
{
    const char* item_code;
    int threshold_amount;
    int target_amount;
};

class CraftOrderSystem: public System
{
public:
    CraftOrderSystem(const char* system_name, ItemCraftingManager& item_crafting_manager, InventoryManager& bank);

    virtual ~CraftOrderSystem() = default;

    void Fill_Pipeline(Character& character) override;

protected:
    std::vector<CraftOrder> m_Items;

private:
    InventoryManager& m_Bank;
    ItemCraftingManager& m_Item_Crafting_Manager;
};

#endif  // _CRAFT_ORDER_SYSTEM_HPP
