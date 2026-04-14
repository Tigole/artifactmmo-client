#ifndef _FIGHT_EQUIPEMENT_SYSTEM_HPP
#define _FIGHT_EQUIPEMENT_SYSTEM_HPP 1

#include "system.hpp"

class FightEquipementSystem: public System
{
public:
    FightEquipementSystem(InventoryManager& bank) : System("FightEquipementSystem"), m_Bank(bank)
    {
        m_Items.push_back("small_health_potion");
        m_Items.push_back("apple");
        m_Items.push_back("cooked_chicken");
        m_Items.push_back("fried_eggs");
        m_Items.push_back("cooked_gudgeon");
        m_Items.push_back("cooked_beef");
    }

    void Fill_Pipeline(Character& character) override
    {
        for (std::size_t ii = 0; ii < m_Items.size(); ii++)
        {
            const char* l_Item = m_Items[ii];
            if ((m_Bank.Get_Bank_Item_Count(l_Item) >= 10) && (character.Get_Item_Count(l_Item) == 0) &&
                (character.Get_Inventory_Remaining_Slot_Count() > 5))
            {
                const MapCoord l_Bank_Coord = m_Bank.Get_Bank_Nearest_Coord(character);
                if (character.Should_Move(l_Bank_Coord) == true)
                {
                    character.Add_Move(this, l_Bank_Coord);
                    m_Bank.Deposit_Resources(this, character, nullptr);
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
    InventoryManager& m_Bank;
    std::vector<const char*> m_Items;
};

#endif  // _FIGHT_EQUIPEMENT_SYSTEM_HPP
