#ifndef _MINING_SYSTEM_HPP
#define _MINING_SYSTEM_HPP 1

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

class MiningCraftingSystem: public CraftOrderSystem
{
public:
    MiningCraftingSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("MiningCraftingSystem", item_crafting_manager, bank)
    {
        m_Items.push_back({ "copper_bar", 5, 50 });
        m_Items.push_back({ "iron_bar", 20, 50 });
        m_Items.push_back({ "steal_bar", 20, 50 });
        m_Items.push_back({ "gold_bar", 20, 50 });
        m_Items.push_back({ "strangold_bar", 20, 50 });
        m_Items.push_back({ "mithril_bar", 20, 50 });
        m_Items.push_back({ "adamantine_bar", 20, 50 });
    }
};

#endif  // _MINING_SYSTEM_HPP
