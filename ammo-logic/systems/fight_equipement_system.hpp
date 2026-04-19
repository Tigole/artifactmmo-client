#ifndef _FIGHT_EQUIPEMENT_SYSTEM_HPP
#define _FIGHT_EQUIPEMENT_SYSTEM_HPP 1

#include "system.hpp"

#if 0

class FightEquipementSystem: public System
{
    FightEquipementSystem() : System("FightEquipementSystem")
    {
        m_Items.push_back(Keywords::Items::Utilities::small_health_potion);
        m_Items.push_back(Keywords::Items::Consumables::Food::apple);
        m_Items.push_back(Keywords::Items::Consumables::Food::cooked_chicken);
        m_Items.push_back(Keywords::Items::Consumables::Food::fried_eggs);
        m_Items.push_back(Keywords::Items::Consumables::Food::cooked_gudgeon);
        m_Items.push_back(Keywords::Items::Consumables::Food::cooked_beef);
    }

public:
    static FightEquipementSystem singleton;

    void Fill_Pipeline(Character& character) override
    {
        for (std::size_t ii = 0; ii < m_Items.size(); ii++)
        {
            const char* l_Item = m_Items[ii];
            if ((InventoryManager::singleton.Get_Bank_Item_Count(l_Item) >= 10) && (character.Get_Item_Count(l_Item) == 0) &&
                (character.Get_Inventory_Remaining_Slot_Count() > 5))
            {
                const MapCoord l_Bank_Coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);
                if (character.Should_Move(l_Bank_Coord) == true)
                {
                    character.Add_Move(this, l_Bank_Coord);
                    InventoryManager::singleton.Deposit_Resources(this, character, nullptr);
                }
                else
                {
                    character.Add_Withdraw_Item(this, { l_Item, std::min(10, character.Get_Inventory_Remaining_Space() - 5) });
                }
                return;
            }
        }
    }

private:
    std::vector<const char*> m_Items;
};

#endif

#endif  // _FIGHT_EQUIPEMENT_SYSTEM_HPP
