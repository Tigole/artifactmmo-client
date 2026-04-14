#ifndef _ALCHEMY_SYSTEM_HPP
#define _ALCHEMY_SYSTEM_HPP 1

#include "craft_order_system.hpp"

class AlchemyGatheringSystem: public CraftOrderSystem
{
public:
    AlchemyGatheringSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("AlchemyGatheringSystem", item_crafting_manager, bank)
    {
        m_Items.push_back({ "sunflower", 20, 500 });
        m_Items.push_back({ "nettle_leaf", 20, 500 });
        m_Items.push_back({ "glowstem_leaf", 20, 500 });
        m_Items.push_back({ "torch_cactus_flower", 20, 500 });
    }
};

class AlchemyCraftingSystem: public CraftOrderSystem
{
public:
    AlchemyCraftingSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("AlchemyCraftingSystem", item_crafting_manager, bank)
    {
        m_Items.push_back({ "small_health_potion", 10, 50 });
        m_Items.push_back({ "minor_health_potion", 10, 50 });
        m_Items.push_back({ "health_potion", 10, 50 });
        m_Items.push_back({ "health_splash_potion", 10, 50 });
        m_Items.push_back({ "health_boost_potion", 10, 50 });
        m_Items.push_back({ "greater_health_potion", 10, 50 });
        m_Items.push_back({ "enchanted_health_potion", 10, 50 });
    }
};

#endif  // _ALCHEMY_SYSTEM_HPP
