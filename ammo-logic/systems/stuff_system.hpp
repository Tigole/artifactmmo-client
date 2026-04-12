#ifndef _STUFF_SYSTEM_HPP
#define _STUFF_SYSTEM_HPP 1

struct StuffOrder
{
    int required_combat_level;
    EquipementType equipment_type;
    std::string target_item_code;
};

class StuffSystem: public System
{
public:
    StuffSystem(ItemManager& item_manager, ItemCraftingManager& item_crafting_manager) :
        System("StuffSystem"), m_Item_Manager(item_manager), m_Item_Crafting_Manager(item_crafting_manager)
    {
        m_Orders.push_back({
            1,
            EquipementType::Weapon,
            "copper_pickaxe",
        });
        m_Orders.push_back({
            1,
            EquipementType::Weapon,
            "copper_axe",
        });
        m_Orders.push_back({
            1,
            EquipementType::Weapon,
            "fishing_net",
        });
        m_Orders.push_back({
            1,
            EquipementType::Helmet,
            "copper_helmet",
        });
        m_Orders.push_back({
            1,
            EquipementType::Boots,
            "copper_boots",
        });
        m_Orders.push_back({
            1,
            EquipementType::Ring1,
            "copper_ring",
        });
        m_Orders.push_back({
            1,
            EquipementType::Ring2,
            "copper_ring",
        });
        m_Orders.push_back({
            1,
            EquipementType::Shield,
            "wooden_shield",
        });
        m_Orders.push_back({
            1,
            EquipementType::Weapon,
            "apprentice_gloves",
        });

        m_Orders.push_back({
            5,
            EquipementType::BodyArmor,
            "feather_coat",
        });
        m_Orders.push_back({
            5,
            EquipementType::Weapon,
            "sticky_dagger",
        });
        m_Orders.push_back({
            5,
            EquipementType::Weapon,
            "sticky_sword",
        });
        m_Orders.push_back({
            5,
            EquipementType::Weapon,
            "water_bow",
        });
        m_Orders.push_back({
            5,
            EquipementType::Weapon,
            "fire_staff",
        });
        m_Orders.push_back({
            5,
            EquipementType::Amulet,
            "life_amulet",
        });

        m_Orders.push_back({
            10,
            EquipementType::Weapon,
            "iron_pickaxe",
        });
        m_Orders.push_back({
            10,
            EquipementType::Weapon,
            "iron_axe",
        });
        m_Orders.push_back({
            10,
            EquipementType::Weapon,
            "spruce_fishing_rod",
        });
        m_Orders.push_back({
            10,
            EquipementType::Boots,
            "leather_boots",
        });
        m_Orders.push_back({
            10,
            EquipementType::BodyArmor,
            "leather_armor",
        });
        m_Orders.push_back({
            10,
            EquipementType::BodyArmor,
            "iron_armor",
        });
        m_Orders.push_back({
            10,
            EquipementType::LegArmor,
            "iron_legs_armor",
        });
    }

    void Fill_Pipeline(Character& character) override
    {
        for (std::size_t ii = 0; ii < m_Orders.size() && character.Is_Empty(); ii++)
        {
            const StuffOrder& l_Order          = m_Orders[ii];
            const bool l_May_Object_Be_Crafted = m_Item_Crafting_Manager.May_Craft(character, l_Order.target_item_code.c_str());
            const bool l_Is_Combat_Level_Ok    = character.Get_Skill_Level("combat") >= l_Order.required_combat_level;
            const bool l_Is_Object_Crafted     = character.Is_Item_Equiped(l_Order.target_item_code.c_str()) ||
                                                 character.Get_Item_Count(l_Order.target_item_code.c_str()) > 0;
            const int l_Target_Object_Level    = m_Item_Manager.Get_Item_Level(l_Order.target_item_code.c_str());
            const int l_Equipped_Object_Level  = m_Item_Manager.Get_Item_Level(character.Get_Equiped_Item(l_Order.equipment_type).c_str());
            const bool l_Is_Target_Object_Better = l_Target_Object_Level > l_Equipped_Object_Level;
            const bool l_Is_Object_To_Be_Crafted =
                l_May_Object_Be_Crafted && l_Is_Combat_Level_Ok && !l_Is_Object_Crafted && l_Is_Target_Object_Better;

            if (l_Is_Object_To_Be_Crafted == true)
            {
                m_Item_Crafting_Manager.Make_Craft_Item(this, character, { l_Order.target_item_code, 1 });
            }
        }
    }

private:
    ItemCraftingManager& m_Item_Crafting_Manager;
    ItemManager& m_Item_Manager;
    std::vector<StuffOrder> m_Orders;
};

#endif  // _STUFF_SYSTEM_HPP
