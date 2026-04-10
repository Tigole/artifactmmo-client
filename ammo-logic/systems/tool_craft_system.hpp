#ifndef _TOOL_CRAFT_SYSTEM_HPP
#define _TOOL_CRAFT_SYSTEM_HPP 1

class ToolCraftSystem: public CraftOrderSystem
{
public:
    ToolCraftSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("ToolCraftSystem", item_crafting_manager, bank)
    {
        m_Items.push_back({ "apprentice_gloves", 0, 2 });
        m_Items.push_back({ "copper_pickaxe", 0, 2 });
        m_Items.push_back({ "copper_axe", 0, 2 });
        m_Items.push_back({ "fishing_net", 0, 2 });
    }
};

#endif  // _TOOL_CRAFT_SYSTEM_HPP
