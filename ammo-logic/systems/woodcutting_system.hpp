#ifndef _WOODCUTTING_SYSTEM_HPP
#define _WOODCUTTING_SYSTEM_HPP 1

class WoodcuttingCraftingSystem: public CraftOrderSystem
{
public:
    WoodcuttingCraftingSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("WoodcuttingCraftingSystem", item_crafting_manager, bank)
    {
        m_Items.push_back({ "ash_plank", 0, 50 });
        m_Items.push_back({ "spruce_plank", 0, 50 });
        m_Items.push_back({ "birch_plank", 0, 50 });
        m_Items.push_back({ "hardwood_plank", 0, 50 });
        m_Items.push_back({ "dead_wood_plank", 0, 50 });
        m_Items.push_back({ "magical_plank", 0, 50 });
        m_Items.push_back({ "maple_plank", 0, 50 });
        m_Items.push_back({ "palm_plank", 0, 50 });
    }
};

#endif  // _WOODCUTTING_SYSTEM_HPP
