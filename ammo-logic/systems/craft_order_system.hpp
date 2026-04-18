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
    AlchemyCraftingSystem();

public:
    static AlchemyCraftingSystem singleton;
};

class CookingSystem: public CraftOrderSystem
{
    CookingSystem();

public:
    static CookingSystem singleton;
};

class MiningCraftingSystem: public CraftOrderSystem
{
    MiningCraftingSystem();

public:
    static MiningCraftingSystem singleton;
};

class WoodcuttingCraftingSystem: public CraftOrderSystem
{
    WoodcuttingCraftingSystem();

public:
    static WoodcuttingCraftingSystem singleton;
};

class ToolCraftSystem: public CraftOrderSystem
{
    ToolCraftSystem();

public:
    static ToolCraftSystem singleton;
};

class WeaponCraftSystem: public CraftOrderSystem
{
    WeaponCraftSystem();

public:
    static WeaponCraftSystem singleton;
};

class GearcraftingSystem: public CraftOrderSystem
{
    GearcraftingSystem();

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
