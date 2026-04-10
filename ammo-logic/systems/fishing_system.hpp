#ifndef _FISHING_SYSTEM_HPP
#define _FISHING_SYSTEM_HPP 1

class FishingSystem: public CraftOrderSystem
{
public:
    FishingSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("FishingSystem", item_crafting_manager, bank)
    {
        m_Items.push_back({ "gudgeon", 20, 500 });
        m_Items.push_back({ "shrimp", 20, 500 });
        m_Items.push_back({ "trout", 20, 500 });
        m_Items.push_back({ "bass", 20, 500 });
        m_Items.push_back({ "salmon", 20, 500 });
        m_Items.push_back({ "swordfish", 20, 500 });
    }
};

#endif  // _FISHING_SYSTEM_HPP
