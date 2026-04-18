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
            SYSTEM_PRINT("no requirement for '%s'", order.item_code);
            continue;
        }

        const int character_skill_level = character.Get_Skill_Level(req->skill_name.c_str());
        if ((bank_item_count < order.target_amount) && (req->skill_level <= character_skill_level))
        {
            SYSTEM_PRINT("will gather '%s' x%d", order.item_code, order.target_amount - bank_item_count);
            const MapCoord* coord = ResourceManager::singleton.Get_Resource_Coord(character, order.item_code);
            if (coord == nullptr)
            {
                SYSTEM_PRINT("doesn't know where to gather '%s'", order.item_code);
                continue;
            }

            if (character.Get_Inventory_Remaining_Space() < ResourceManager::singleton.Get_Required_Inventory_Space(*coord))
            {
                SYSTEM_PRINT("has to make space", character.Get_Character());
                character.Make_Clear_Inventory(this, nullptr);
                return;
            }

            for (std::size_t jj = 0; jj < m_Equipements.size(); jj++)
            {
                const char* weapon       = m_Equipements[jj];
                const int required_level = ItemManager::singleton.Get_Required_Level(weapon);

                if (character_skill_level < required_level)
                {
                    SYSTEM_PRINT("skill '%s' is too low to equip '%s' (current: %d required: %d)", req->skill_name.c_str(), weapon,
                                 character_skill_level, required_level);
                    continue;
                }
                if (character.Get_Equiped_Weapon() == weapon)
                {
                    SYSTEM_PRINT("is already equiped with '%s'", weapon);
                    break;
                }
                else
                {
                    SYSTEM_PRINT("try to equip weapon '%s'", weapon);

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
                character.Make_Clear_Inventory(this, nullptr);
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

WoodcuttingGatheringSystem::WoodcuttingGatheringSystem() : GatherSystem("WoodcuttingGatheringSystem")
{
    static constexpr int item_amount = 200;

    m_Resources.push_back({ "palm_wood", item_amount });
    m_Resources.push_back({ "maple_wood", item_amount });
    m_Resources.push_back({ "magic_wood", item_amount });
    m_Resources.push_back({ "dead_wood", item_amount });
    m_Resources.push_back({ "hardwood_wood", item_amount });
    m_Resources.push_back({ "birch_wood", item_amount });
    m_Resources.push_back({ "spruce_wood", item_amount });
    m_Resources.push_back({ "ash_wood", item_amount });

    m_Equipements.push_back("voidstone_axe");
    m_Equipements.push_back("adamantite_axe");
    m_Equipements.push_back("mithril_axe");
    m_Equipements.push_back("gold_axe");
    m_Equipements.push_back("steel_axe");
    m_Equipements.push_back("iron_axe");
    m_Equipements.push_back("copper_axe");
}

MiningGatheringSystem MiningGatheringSystem::singleton;

MiningGatheringSystem::MiningGatheringSystem() : GatherSystem("MiningGatheringSystem")
{
    static constexpr int item_amount = 200;

    m_Resources.push_back({ "adamantine_ore", item_amount });
    m_Resources.push_back({ "mithril_ore", item_amount });
    m_Resources.push_back({ "strange_ore", item_amount });
    m_Resources.push_back({ "gold_ore", item_amount });
    m_Resources.push_back({ "coal", item_amount });
    m_Resources.push_back({ "iron_ore", item_amount });
    m_Resources.push_back({ "copper_ore", item_amount });

    m_Equipements.push_back("voidstone_pickaxe");
    m_Equipements.push_back("adamantite_pickaxe");
    m_Equipements.push_back("mithril_pickaxe");
    m_Equipements.push_back("gold_pickaxe");
    m_Equipements.push_back("steel_pickaxe");
    m_Equipements.push_back("iron_pickaxe");
    m_Equipements.push_back("copper_pickaxe");
}

AlchemyGatheringSystem AlchemyGatheringSystem::singleton;

AlchemyGatheringSystem::AlchemyGatheringSystem() : GatherSystem("AlchemyGatheringSystem")
{
    static constexpr int item_amount = 200;

    m_Resources.push_back({ "torch_cactus_flower", item_amount });
    m_Resources.push_back({ "glowstem_leaf", item_amount });
    m_Resources.push_back({ "nettle_leaf", item_amount });
    m_Resources.push_back({ "sunflower", item_amount });

    m_Equipements.push_back("voidstone_gloves");
    m_Equipements.push_back("adamantite_gloves");
    m_Equipements.push_back("mithril_gloves");
    m_Equipements.push_back("golden_gloves");
    m_Equipements.push_back("steel_gloves");
    m_Equipements.push_back("leather_gloves");
    m_Equipements.push_back("apprentice_gloves");
}

FishingGatherSystem FishingGatherSystem::singleton;

FishingGatherSystem::FishingGatherSystem() : GatherSystem("FishingGatherSystem")
{
    static constexpr int item_amount = 200;

    m_Resources.push_back({ "swordfish", item_amount });
    m_Resources.push_back({ "salmon", item_amount });
    m_Resources.push_back({ "bass", item_amount });
    m_Resources.push_back({ "trout", item_amount });
    m_Resources.push_back({ "shrimp", item_amount });
    m_Resources.push_back({ "gudgeon", item_amount });

    m_Equipements.push_back("voidstone_fishing_rod");
    m_Equipements.push_back("adamantite_fishing_rod");
    m_Equipements.push_back("mithril_fishing_rod");
    m_Equipements.push_back("gold_fishing_rod");
    m_Equipements.push_back("steel_fishing_rod");
    m_Equipements.push_back("spruce_fishing_rod");
    m_Equipements.push_back("fishing_net");
}
