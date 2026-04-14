#ifndef _GATHER_SYSTEM_HPP
#define _GATHER_SYSTEM_HPP 1

#include "system.hpp"

class Client;

struct GatherOrder
{
    const char* item_code;
    int threshold_amount;
    int target_amount;
};

class GatherSystem: public System
{
public:
    GatherSystem();
    void Initialize(Client& client);

    void Fill_Pipeline(Character& character) override;

    void Gather_Resource(Character& character, const char* resource_code);

protected:
    std::vector<GatherOrder> m_Resources;

private:
    std::vector<nlohmann::json> m_Spots;
    std::map<std::string, MapCoord> m_Resource_Coord;
};

#include "craft_order_system.hpp"

class WoodcuttingGatheringSystem: public CraftOrderSystem
{
public:
    WoodcuttingGatheringSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("WoodcuttingGatheringSystem", item_crafting_manager, bank)
    {
        m_Items.push_back({ "ash_wood", 20, 500 });
        m_Items.push_back({ "spruce_wood", 20, 500 });
        m_Items.push_back({ "birch_wood", 20, 500 });
        m_Items.push_back({ "hardwood_wood", 20, 500 });
        m_Items.push_back({ "dead_wood", 20, 500 });
        m_Items.push_back({ "magic_wood", 20, 500 });
        m_Items.push_back({ "maple_wood", 20, 500 });
        m_Items.push_back({ "palm_wood", 20, 500 });
    }
};

class MiningGatheringSystem: public CraftOrderSystem
{
public:
    MiningGatheringSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("MiningGatheringSystem", item_crafting_manager, bank)
    {
        m_Items.push_back({ "copper_ore", 20, 500 });
        m_Items.push_back({ "iron_ore", 20, 500 });
        m_Items.push_back({ "coal", 20, 500 });
        m_Items.push_back({ "gold_ore", 20, 500 });
        m_Items.push_back({ "strange_ore", 20, 500 });
        m_Items.push_back({ "mithril_ore", 20, 500 });
        m_Items.push_back({ "adamantine_ore", 20, 500 });
    }
};

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

class FishingGatherSystem: public CraftOrderSystem
{
public:
    FishingGatherSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("FishingGatherSystem", item_crafting_manager, bank)
    {
        m_Items.push_back({ "gudgeon", 20, 500 });
        m_Items.push_back({ "shrimp", 20, 500 });
        m_Items.push_back({ "trout", 20, 500 });
        m_Items.push_back({ "bass", 20, 500 });
        m_Items.push_back({ "salmon", 20, 500 });
        m_Items.push_back({ "swordfish", 20, 500 });
    }
};

#endif  // _GATHER_SYSTEM_HPP
