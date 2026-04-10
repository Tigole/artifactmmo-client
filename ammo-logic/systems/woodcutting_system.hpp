#ifndef _WOODCUTTING_SYSTEM_HPP
#define _WOODCUTTING_SYSTEM_HPP 1

class WoodcuttingSystem: public CraftOrderSystem
{
public:
    WoodcuttingSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("WoodcuttingSystem", item_crafting_manager, bank)
    {
        m_Items.push_back({ "ash_wood", 20, 500 });
        m_Items.push_back({ "ash_plank", 0, 50 });
        m_Items.push_back({ "spruce_wood", 20, 500 });
        m_Items.push_back({ "spruce_plank", 0, 50 });
        m_Items.push_back({ "birch_wood", 20, 500 });
        m_Items.push_back({ "birch_plank", 0, 50 });
        m_Items.push_back({ "hardwood_wood", 20, 500 });
        m_Items.push_back({ "hardwood_plank", 0, 50 });
        m_Items.push_back({ "dead_wood", 20, 500 });
        m_Items.push_back({ "dead_wood_plank", 0, 50 });
        m_Items.push_back({ "magic_wood", 20, 500 });
        m_Items.push_back({ "magical_plank", 0, 50 });
        m_Items.push_back({ "maple_wood", 20, 500 });
        m_Items.push_back({ "maple_plank", 0, 50 });
        m_Items.push_back({ "palm_wood", 20, 500 });
        m_Items.push_back({ "palm_plank", 0, 50 });
    }
};

#endif  // _WOODCUTTING_SYSTEM_HPP
