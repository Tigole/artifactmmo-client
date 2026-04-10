#include "craft_system.hpp"

#include "managers/item_manager.hpp"

CraftSystem::CraftSystem(ItemManager& item_manager) : System("CraftSystem"), m_Item_Manager(item_manager)
{
    m_Workshop_Coords["mining"]          = { 1, 5 };
    m_Workshop_Coords["woodcutting"]     = { -2, -3 };
    m_Workshop_Coords["fishing"]         = { 0, 0 };
    m_Workshop_Coords["alchemy"]         = { 2, 3 };
    m_Workshop_Coords["weaponcrafting"]  = { 2, 1 };
    m_Workshop_Coords["gearcrafting"]    = { 3, 1 };
    m_Workshop_Coords["jewelrycrafting"] = { 1, 3 };
    m_Workshop_Coords["cooking"]         = { 1, 1 };
}

void CraftSystem::Initialize(void)
{
    m_Item_Manager.Get_Items(m_Items);
}

void CraftSystem::Fill_Pipeline(Character& pipeline)
{
    std::vector<std::size_t> l_Available_Items;

    for (std::size_t ii = 0; ii < m_Items.size(); ii++)
    {
        const Recipe* r = m_Item_Manager.Get_Recipe(m_Items[ii].c_str());
        if (r != nullptr)
        {
            if (pipeline.Get_Skill_Level(r->skill_name.c_str()) >= r->skill_level)
            {
                bool l_Has_Enough_Ingredients = true;
                for (const auto& i: r->required_items)
                {
                    l_Has_Enough_Ingredients &= pipeline.Get_Item_Count(i.code.c_str()) >= i.quantity;
                }
                if (l_Has_Enough_Ingredients)
                {
                    l_Available_Items.push_back(ii);
                }
            }
        }
    }

    if (l_Available_Items.size() > 0)
    {
        std::size_t index = rand() % l_Available_Items.size();
        const Recipe* r   = m_Item_Manager.Get_Recipe(m_Items[l_Available_Items[index]].c_str());

        pipeline.Add_Move(m_Workshop_Coords[r->skill_name]);
        pipeline.Add_Craft({ r->target_item, 1 });
    }
}
