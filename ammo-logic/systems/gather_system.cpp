#include "gather_system.hpp"

#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"
#include "managers/resource_manager.hpp"
#include "net/client.hpp"

GatherSystem::GatherSystem(const char* system_name) : System(system_name) {}

void GatherSystem::Initialize() {}

void GatherSystem::Fill_Pipeline(Character& character)
{
    for (std::size_t ii = 0; ii < m_Resources.size(); ii++)
    {
        const GatherOrder order         = m_Resources[ii];
        const int bank_item_count       = InventoryManager::singleton.Get_Bank_Item_Count(order.item_code);
        const GatheringRequirement* req = ItemManager::singleton.Get_Gathering_Skill(order.item_code);

        if (req == nullptr)
        {
            printf("No requirement for '%s'\n", order.item_code);
            continue;
        }

        const int character_skill_level = character.Get_Skill_Level(req->skill_name.c_str());
        if ((bank_item_count < order.target_amount) && (req->skill_level <= character_skill_level))
        {
            printf("[%s] will gather '%s' x%d\n", character.Get_Character(), order.item_code, order.target_amount - bank_item_count);
            const MapCoord* coord = ResourceManager::singleton.Get_Resource_Coord(character, order.item_code);
            if (coord == nullptr)
            {
                printf("Don't know where to gather '%s'\n", order.item_code);
                continue;
            }

            if (character.Get_Inventory_Remaining_Space() < ResourceManager::singleton.Get_Required_Inventory_Space(*coord))
            {
                printf("[%s] has to make space\n", character.Get_Character());
                InventoryManager::singleton.Deposit_Resources(this, character, nullptr);
                return;
            }

            for (std::size_t jj = 0; jj < m_Equipements.size(); jj++)
            {
                const char* weapon       = m_Equipements[jj];
                const int required_level = ItemManager::singleton.Get_Required_Level(weapon);

                if (character_skill_level < required_level)
                {
                    printf("[%s] skill '%s' is too low to equip '%s' (current: %d required: %d)\n", character.Get_Character(),
                           req->skill_name.c_str(), weapon, character_skill_level, required_level);
                    continue;
                }
                if (character.Get_Equiped_Weapon() == weapon)
                {
                    printf("[%s] is already equiped with '%s'\n", character.Get_Character(), weapon);
                    break;
                }
                else
                {
                    printf("[%s] try to equip weapon '%s'\n", character.Get_Character(), weapon);

                    /// if is in inventory
                    if (character.Get_Item_Count(weapon) > 0)
                    {
                        character.Add_Equip_Item(this, "weapon", weapon);
                        return;
                    }
                    /// if in bank
                    else if (InventoryManager::singleton.Get_Bank_Item_Count(weapon) > 0)
                    {
                        const MapCoord bank_coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);
                        if (character.Should_Move(bank_coord))
                        {
                            character.Add_Move(this, bank_coord);
                            return;
                        }

                        character.Add_Withdraw_Item(this, { weapon, 1 });
                        return;
                    }
                    /// Else try with the next one
                }
            }

            if ((character.Get_Item_Count(order.item_code) == 0) && (character.Is_Inventory_Empty() == false))
            {
                InventoryManager::singleton.Deposit_Resources(this, character, nullptr);
                return;
            }

            if (character.Should_Move(*coord) == true)
            {
                character.Add_Move(this, *coord);
                return;
            }
            else
            {
                character.Add_Gathering(this);
                return;
            }
        }
    }
}

WoodcuttingGatheringSystem WoodcuttingGatheringSystem::singleton;
MiningGatheringSystem MiningGatheringSystem::singleton;
AlchemyGatheringSystem AlchemyGatheringSystem::singleton;
FishingGatherSystem FishingGatherSystem::singleton;
