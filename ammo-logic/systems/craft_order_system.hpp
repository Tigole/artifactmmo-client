#ifndef _CRAFT_ORDER_SYSTEM_HPP
#define _CRAFT_ORDER_SYSTEM_HPP 1

#include "system.hpp"

class ItemCraftingManager;
class InventoryManager;

struct CraftOrder
{
    const char* item_code;
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
    MapCoord m_Workshop_Coord;
};

class AlchemyCraftingSystem: public CraftOrderSystem
{
    AlchemyCraftingSystem() : CraftOrderSystem("AlchemyCraftingSystem")
    {
        m_Items.push_back({ "enchanted_health_potion", 50 });
        m_Items.push_back({ "greater_health_potion", 50 });
        m_Items.push_back({ "health_boost_potion", 50 });
        m_Items.push_back({ "health_splash_potion", 50 });
        m_Items.push_back({ "health_potion", 50 });
        m_Items.push_back({ "minor_health_potion", 50 });
        m_Items.push_back({ "small_health_potion", 50 });

        m_Workshop_Coord = { 2, 3 };
    }

public:
    static AlchemyCraftingSystem singleton;
};

class CookingSystem: public CraftOrderSystem
{
    CookingSystem() : CraftOrderSystem("CookingSystem")
    {
        m_Items.push_back({ "cooked_shrimp", 50 });
        m_Items.push_back({ "cooked_beef", 50 });
        m_Items.push_back({ "cooked_gudgeon", 300 });
        m_Items.push_back({ "fried_eggs", 10 });
        m_Items.push_back({ "cooked_chicken", 50 });

        m_Workshop_Coord = { 1, 1 };
    }

public:
    static CookingSystem singleton;
};

class MiningCraftingSystem: public CraftOrderSystem
{
    MiningCraftingSystem() : CraftOrderSystem("MiningCraftingSystem")
    {
        constexpr const int target_amout = 50;
        m_Items.push_back({ "adamantine_bar", target_amout });
        m_Items.push_back({ "mithril_bar", target_amout });
        m_Items.push_back({ "strangold_bar", target_amout });
        m_Items.push_back({ "gold_bar", target_amout });
        m_Items.push_back({ "steal_bar", target_amout });
        m_Items.push_back({ "iron_bar", target_amout });
        m_Items.push_back({ "copper_bar", target_amout });

        m_Workshop_Coord = { 1, 5 };
    }

public:
    static MiningCraftingSystem singleton;
};

class WoodcuttingCraftingSystem: public CraftOrderSystem
{
    WoodcuttingCraftingSystem() : CraftOrderSystem("WoodcuttingCraftingSystem")
    {
        constexpr const int target_amout = 5;
        m_Items.push_back({ "maple_plank", target_amout });
        m_Items.push_back({ "magical_plank", target_amout });
        m_Items.push_back({ "dead_wood_plank", target_amout });
        m_Items.push_back({ "palm_plank", target_amout });
        m_Items.push_back({ "hardwood_plank", target_amout });
        m_Items.push_back({ "birch_plank", target_amout });
        m_Items.push_back({ "spruce_plank", target_amout });
        m_Items.push_back({ "ash_plank", target_amout });

        m_Workshop_Coord = { -2, -3 };
    }

public:
    static WoodcuttingCraftingSystem singleton;
};

class ToolCraftSystem: public CraftOrderSystem
{
    ToolCraftSystem();

public:
    static ToolCraftSystem singleton;
};

class GearcraftingSystem: public CraftOrderSystem
{
    GearcraftingSystem() : CraftOrderSystem("GearcraftingSystem")
    {
        constexpr const int target_amout = 3;
        m_Items.push_back({ "copper_helmet", target_amout });
        m_Items.push_back({ "copper_boots", target_amout });
        m_Items.push_back({ "copper_legs_armor", target_amout });
        m_Items.push_back({ "wooden_shield", target_amout });
        m_Items.push_back({ "feather_coat", target_amout });
        m_Items.push_back({ "life_amulet", target_amout });
        m_Items.push_back({ "leather_boots", target_amout });
        m_Items.push_back({ "leather_armor", target_amout });
        m_Items.push_back({ "adventurer_helmet", target_amout });
        m_Items.push_back({ "iron_legs_armor", target_amout });
        m_Items.push_back({ "iron_armor", target_amout });
        m_Items.push_back({ "adventurer_vest", target_amout });
        m_Items.push_back({ "leather_hat", target_amout });
        m_Items.push_back({ "leather_legs_armor", target_amout });

        m_Workshop_Coord = { 3, 1 };
    }

public:
    static GearcraftingSystem singleton;
};

class BuyingSystem: public System
{
    BuyingSystem();

public:
    static BuyingSystem singleton;

    void Fill_Pipeline(Character& character) override;
};

#endif  // _CRAFT_ORDER_SYSTEM_HPP
