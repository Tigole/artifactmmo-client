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
protected:
    CraftOrderSystem(const char* system_name);

public:
    virtual ~CraftOrderSystem() = default;

    void Fill_Pipeline(Character& character) override;

protected:
    std::vector<CraftOrder> m_Items;
};

class AlchemyCraftingSystem: public CraftOrderSystem
{
    AlchemyCraftingSystem() : CraftOrderSystem("AlchemyCraftingSystem")
    {
        m_Items.push_back({ "small_health_potion", 10, 50 });
        m_Items.push_back({ "minor_health_potion", 10, 50 });
        m_Items.push_back({ "health_potion", 10, 50 });
        m_Items.push_back({ "health_splash_potion", 10, 50 });
        m_Items.push_back({ "health_boost_potion", 10, 50 });
        m_Items.push_back({ "greater_health_potion", 10, 50 });
        m_Items.push_back({ "enchanted_health_potion", 10, 50 });
    }

public:
    static AlchemyCraftingSystem singleton;
};

class CookingSystem: public CraftOrderSystem
{
    CookingSystem() : CraftOrderSystem("CookingSystem")
    {
        m_Items.push_back({ "cooked_chicken", 20, 50 });
        m_Items.push_back({ "fried_eggs", 5, 10 });
        m_Items.push_back({ "cooked_gudgeon", 20, 300 });
        m_Items.push_back({ "cooked_beef", 20, 50 });
        m_Items.push_back({ "cooked_shrimp", 20, 50 });
    }

public:
    static CookingSystem singleton;
};

class MiningCraftingSystem: public CraftOrderSystem
{
    MiningCraftingSystem() : CraftOrderSystem("MiningCraftingSystem")
    {
        m_Items.push_back({ "copper_bar", 5, 50 });
        m_Items.push_back({ "iron_bar", 20, 50 });
        m_Items.push_back({ "steal_bar", 20, 50 });
        m_Items.push_back({ "gold_bar", 20, 50 });
        m_Items.push_back({ "strangold_bar", 20, 50 });
        m_Items.push_back({ "mithril_bar", 20, 50 });
        m_Items.push_back({ "adamantine_bar", 20, 50 });
    }

public:
    static MiningCraftingSystem singleton;
};

class WoodcuttingCraftingSystem: public CraftOrderSystem
{
    WoodcuttingCraftingSystem() : CraftOrderSystem("WoodcuttingCraftingSystem")
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

public:
    static WoodcuttingCraftingSystem singleton;
};

class ToolCraftSystem: public CraftOrderSystem
{
    ToolCraftSystem() : CraftOrderSystem("ToolCraftSystem")
    {
        m_Items.push_back({ "apprentice_gloves", 0, 2 });
        m_Items.push_back({ "copper_pickaxe", 0, 2 });
        m_Items.push_back({ "copper_axe", 0, 2 });
        m_Items.push_back({ "fishing_net", 0, 2 });
    }

public:
    static ToolCraftSystem singleton;
};

class GearcraftingSystem: public CraftOrderSystem
{
    GearcraftingSystem() : CraftOrderSystem("GearcraftingSystem")
    {
        constexpr const int target_amout = 3;
        m_Items.push_back({ "copper_helmet", 0, target_amout });
        m_Items.push_back({ "copper_boots", 0, target_amout });
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

public:
    static GearcraftingSystem singleton;
};

#endif  // _CRAFT_ORDER_SYSTEM_HPP
