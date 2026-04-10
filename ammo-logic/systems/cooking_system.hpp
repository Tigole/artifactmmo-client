#ifndef _COOKING_SYSTEM_HPP
#define _COOKING_SYSTEM_HPP 1

class CookingSystem: public CraftOrderSystem
{
public:
    CookingSystem(ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        CraftOrderSystem("CookingSystem", item_crafting_manager, bank)
    {
        m_Items.push_back({ "apple", 20, 50 });
        m_Items.push_back({ "cooked_chicken", 20, 50 });
        m_Items.push_back({ "fried_eggs", 5, 10 });
        m_Items.push_back({ "cooked_gudgeon", 20, 300 });
        m_Items.push_back({ "cooked_beef", 20, 50 });
        m_Items.push_back({ "cooked_shrimp", 20, 50 });
    }
};

#endif  // _COOKING_SYSTEM_HPP
