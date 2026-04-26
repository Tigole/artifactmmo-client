#include "gather_system.hpp"

#include "keywords.hpp"
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

            if (character.Get_Item_Count(order.item_code) + bank_item_count >= order.target_amount)
            {
                SYSTEM_PRINT("has enough in inventory");
                character.Make_Clear_Inventory(this, nullptr);
                return;
            }

            Make_Gather(character, *coord, req->skill_name.c_str(), m_Equipements);
            return;
        }
    }
}

const std::vector<const char*>& GatherSystem::Get_Equipements(void) const
{
    return m_Equipements;
}

WoodcuttingGatheringSystem WoodcuttingGatheringSystem::singleton;

WoodcuttingGatheringSystem::WoodcuttingGatheringSystem() : GatherSystem("WoodcuttingGatheringSystem")
{
    static constexpr int item_amount = 200;

    m_Resources.push_back({ Keywords::Items::Resources::Woodcutting::palm_wood, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Woodcutting::maple_wood, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Woodcutting::magic_wood, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Woodcutting::dead_wood, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Woodcutting::birch_wood, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Woodcutting::spruce_wood, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Woodcutting::ash_wood, item_amount });

    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Axes::voidstone_axe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Axes::adamantite_axe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Axes::mithril_axe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Axes::gold_axe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Axes::steel_axe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Axes::iron_axe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Axes::copper_axe);
}

MiningGatheringSystem MiningGatheringSystem::singleton;

MiningGatheringSystem::MiningGatheringSystem() : GatherSystem("MiningGatheringSystem")
{
    static constexpr int item_amount = 200;

    m_Resources.push_back({ Keywords::Items::Resources::Mining::adamantite_ore, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Mining::mithril_ore, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Mining::strange_ore, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Mining::gold_ore, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Mining::coal, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Mining::iron_ore, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Mining::copper_ore, item_amount });

    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Pickaxes::voidstone_pickaxe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Pickaxes::adamantite_pickaxe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Pickaxes::mithril_pickaxe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Pickaxes::gold_pickaxe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Pickaxes::steel_pickaxe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Pickaxes::iron_pickaxe);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Pickaxes::copper_pickaxe);
}

AlchemyGatheringSystem AlchemyGatheringSystem::singleton;

AlchemyGatheringSystem::AlchemyGatheringSystem() : GatherSystem("AlchemyGatheringSystem")
{
    static constexpr int item_amount = 200;

    m_Resources.push_back({ Keywords::Items::Resources::Alchemy::torch_cactus_flower, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Alchemy::glowstem_leaf, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Alchemy::nettle_leaf, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Alchemy::sunflower, item_amount });

    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Gloves::voidstone_gloves);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Gloves::adamantite_gloves);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Gloves::mithril_gloves);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Gloves::golden_gloves);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Gloves::steel_gloves);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Gloves::leather_gloves);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::Gloves::apprentice_gloves);
}

FishingGatherSystem FishingGatherSystem::singleton;

FishingGatherSystem::FishingGatherSystem() : GatherSystem("FishingGatherSystem")
{
    static constexpr int item_amount = 200;

    m_Resources.push_back({ Keywords::Items::Resources::Fishing::swordfish, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Fishing::salmon, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Fishing::bass, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Fishing::trout, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Fishing::shrimp, item_amount });
    m_Resources.push_back({ Keywords::Items::Resources::Fishing::gudgeon, item_amount });

    m_Equipements.push_back(Keywords::Items::Weapons::Tools::FishingRods::voidstone_fishing_rod);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::FishingRods::adamantite_fishing_rod);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::FishingRods::mithril_fishing_rod);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::FishingRods::gold_fishing_rod);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::FishingRods::steel_fishing_rod);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::FishingRods::spruce_fishing_rod);
    m_Equipements.push_back(Keywords::Items::Weapons::Tools::FishingRods::fishing_net);
}

MobGatherSystem::MobGatherSystem() : System("MobGatherSystem")
{
    m_Resources.push_back({ Keywords::Items::Resources::Mob::pig_skin, 10 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::raw_wolf_meat, 50 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::wolf_bone, 10 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::wolf_hair, 10 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::snake_hide, 10 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::flying_wing, 10 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::mushroom, 50 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::raw_beef, 50 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::red_slimeball, 50 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::blue_slimeball, 50 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::wool, 50 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::green_slimeball, 50 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::yellow_slimeball, 50 });
    m_Resources.push_back({ Keywords::Items::Resources::Mob::raw_chicken, 100 });
}

#include "fight_system.hpp"

void MobGatherSystem::Fill_Pipeline(Character& character)
{
    for (std::size_t ii = 0; ii < m_Resources.size(); ii++)
    {
        GatherOrder order               = m_Resources[ii];
        const int bank_inventory_amount = InventoryManager::singleton.Get_Bank_Item_Count(order.item_code);
        if (bank_inventory_amount < order.target_amount)
        {
            if (character.Get_Item_Count(order.item_code) + bank_inventory_amount >= order.target_amount)
            {
                SYSTEM_PRINT("has enough in inventory");
                character.Make_Clear_Inventory(this, nullptr);
                return;
            }
            const char* l_Monster_Name = ItemManager::singleton.Get_Loot_Monster_Name(order.item_code);
            FightContext fight_context;

            if (FightSystem::singleton.MayWin(character, l_Monster_Name, fight_context) == true)
            {
                const int required_inventory_space = 10;
                if (character.Get_Inventory_Remaining_Space() < required_inventory_space)
                {
                    SYSTEM_PRINT("has to make space", character.Get_Character());
                    character.Make_Clear_Inventory(this, nullptr);
                    return;
                }

                FightSystem::singleton.Fight_Against(this, character, l_Monster_Name, fight_context);
                return;
            }
        }
    }
}

MobGatherSystem MobGatherSystem::singleton;
