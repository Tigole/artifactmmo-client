#ifndef _GEARCRAFTING_SYSTEM_HPP
#define _GEARCRAFTING_SYSTEM_HPP 1

class GearcraftingSystem: public CraftOrderSystem  // System
{
public:
    GearcraftingSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("GearcraftingSystem", item_crafting_manager, bank)
    {
        constexpr const int target_amout = 3;
        m_Items.push_back({ "copper_helmet", 0, target_amout });
        m_Items.push_back({ "copper_boots", 0, target_amout });
        // m_Items.push_back({ "copper_ring", 0, 5 });
        m_Items.push_back({ "copper_legs_armor", 0, target_amout });
        m_Items.push_back({ "wooden_shield", 0, target_amout });
        m_Items.push_back({ "feather_coat", 0, target_amout });
        m_Items.push_back({ "life_amulet", 0, target_amout });
        m_Items.push_back({ "leather_boots", 0, target_amout });
        m_Items.push_back({ "leather_armor", 0, target_amout });
        m_Items.push_back({ "adventurer_helmet", 0, target_amout });
        m_Items.push_back({ "iron_legs_armor", 0, target_amout });
        m_Items.push_back({ "iron_armor", 0, target_amout });
        m_Items.push_back({ "adventurer_vest", 0, target_amout });
        m_Items.push_back({ "leather_hat", 0, target_amout });
        m_Items.push_back({ "leather_legs_armor", 0, target_amout });
    }
};

#endif  // _GEARCRAFTING_SYSTEM_HPP
