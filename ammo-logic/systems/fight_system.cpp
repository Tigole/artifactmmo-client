#include "fight_system.hpp"

#include <algorithm>
#include <cmath>

#include "keywords.hpp"
#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"
#include "managers/monster_manager.hpp"

FightConfig FightConfig::DefaultConfig(void)
{
    return { false, false, false };
}

FightConfig FightConfig::MonsterTaskConfig(void)
{
    return { true, false, false };
}

FightConfig FightConfig::GatherResourcesConfig(void)
{
    return { false, true, false };
}

FightSystem FightSystem::singleton;

FightSystem::FightSystem() : System("FightSystem")
{
    constexpr const int target_amount = 3;

    m_Monsters.push_back("");

    m_Healing_Items.push_back({ Keywords::Items::Consumables::Food::mushroom_soup, 240, 15, target_amount });
    m_Healing_Items.push_back({ Keywords::Items::Consumables::Food::cooked_trout, 225, 20, target_amount });
    m_Healing_Items.push_back({ Keywords::Items::Consumables::Food::cooked_wolf_meat, 200, 15, target_amount });
    m_Healing_Items.push_back({ Keywords::Items::Consumables::Food::cooked_shrimp, 150, 10, target_amount });
    m_Healing_Items.push_back({ Keywords::Items::Consumables::Food::cooked_beef, 150, 5, target_amount });
    m_Healing_Items.push_back({ Keywords::Items::Consumables::Food::fried_eggs, 150, 4, target_amount });
    m_Healing_Items.push_back({ Keywords::Items::Consumables::Food::cooked_chicken, 80, 0, target_amount });
    m_Healing_Items.push_back({ Keywords::Items::Consumables::Food::cooked_gudgeon, 75, 0, target_amount });
    m_Healing_Items.push_back({ Keywords::Items::Consumables::Food::apple, 50, 0, target_amount });

    m_Healing_Potions.push_back({ Keywords::Items::Utilities::health_potion, 100, 30, 0 });
    m_Healing_Potions.push_back({ Keywords::Items::Utilities::minor_health_potion, 70, 20, 0 });
    m_Healing_Potions.push_back({ Keywords::Items::Utilities::small_health_potion, 30, 5, 0 });
}

void FightSystem::Initialize(void)
{
    MonsterManager::singleton.Get_Monster_List(m_Monsters);
}

void FightSystem::Fill_Pipeline(Character& character)
{
    FightContext l_Context;

    for (std::size_t ii = 0; ii < m_Monsters.size(); ii++)
    {
        const char* l_Monster   = m_Monsters[ii].c_str();
        const MapCoord* l_Coord = MonsterManager::singleton.Get_Monster_Coord(l_Monster, character.Get_Map_Coord());
        if ((l_Coord != nullptr) && (MayWin(character, l_Monster, FightConfig::DefaultConfig(), l_Context) == true))
        {
            Fight_Against(this, character, l_Monster, l_Context);
            return;
        }
    }
}

void FightSystem::Fight_Against(const System* sys, Character& character, const char* monster, const FightContext& context)
{
    const MapCoord* l_Coord = MonsterManager::singleton.Get_Monster_Coord(monster, character.Get_Map_Coord());
    if (l_Coord != nullptr)
    {
        const MapCoord bank_pos = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);
        if (character.Get_Equiped_Weapon() != context.weapon)
        {
            Handle_Equipment(sys, character, bank_pos, context.weapon.c_str(), 1, Keywords::ItemSlot::weapon);
            return;
        }
        if (character.Get_Equiped_Helmet() != context.helmet)
        {
            Handle_Equipment(sys, character, bank_pos, context.helmet.c_str(), 1, Keywords::ItemSlot::helmet);
            return;
        }
        if (character.Get_Equiped_Body_Armor() != context.body_armor)
        {
            Handle_Equipment(sys, character, bank_pos, context.body_armor.c_str(), 1, Keywords::ItemSlot::body_armor);
            return;
        }
        if (character.Get_Equiped_Leg_Armor() != context.leg_armor)
        {
            Handle_Equipment(sys, character, bank_pos, context.leg_armor.c_str(), 1, Keywords::ItemSlot::leg_armor);
            return;
        }
        if (character.Get_Equiped_Boots() != context.boots)
        {
            Handle_Equipment(sys, character, bank_pos, context.boots.c_str(), 1, Keywords::ItemSlot::boots);
            return;
        }
        if (character.Get_Equiped_Ring1() != context.ring1)
        {
            Handle_Equipment(sys, character, bank_pos, context.ring1.c_str(), 1, Keywords::ItemSlot::ring1);
            return;
        }
        if (character.Get_Equiped_Ring2() != context.ring2)
        {
            Handle_Equipment(sys, character, bank_pos, context.ring2.c_str(), 1, Keywords::ItemSlot::ring2);
            return;
        }
        if (character.Get_Equiped_Shield() != context.shield)
        {
            Handle_Equipment(sys, character, bank_pos, context.shield.c_str(), 1, Keywords::ItemSlot::shield);
            return;
        }
        if (character.Get_Equiped_Amulet() != context.amulet)
        {
            Handle_Equipment(sys, character, bank_pos, context.amulet.c_str(), 1, Keywords::ItemSlot::amulet);
            return;
        }
        if (context.utility1.size() > 0 &&
            (character.Get_Equiped_Utility1() != context.utility1 || character.Get_Equiped_Utility1_Quantity() < context.utility1_quantity))
        {
            Handle_Equipment(sys, character, bank_pos, context.utility1.c_str(), context.utility1_quantity, Keywords::ItemSlot::utility1);
            printf(
                "context.utility1: '%s' character.Get_Equiped_Utility1(): '%s' context.utility1_quantity: %d "
                "character.Get_Equiped_Utility1_Quantity(): %d\n",
                context.utility1.c_str(), character.Get_Equiped_Utility1().c_str(), context.utility1_quantity,
                character.Get_Equiped_Utility1_Quantity());
            // exit(0);
            return;
        }
        if (context.utility2.size() > 0 &&
            (character.Get_Equiped_Utility2() != context.utility2 || character.Get_Equiped_Utility2_Quantity() < context.utility2_quantity))
        {
            Handle_Equipment(sys, character, bank_pos, context.utility2.c_str(), context.utility2_quantity, Keywords::ItemSlot::utility2);
            return;
        }
        if (character.Get_Equiped_Artifact1() != context.artifact1)
        {
            Handle_Equipment(sys, character, bank_pos, context.artifact1.c_str(), 1, Keywords::ItemSlot::artifact1);
            return;
        }
        if (character.Get_Equiped_Artifact2() != context.artifact2)
        {
            Handle_Equipment(sys, character, bank_pos, context.artifact1.c_str(), 1, Keywords::ItemSlot::artifact2);
            return;
        }
        if (character.Get_Equiped_Artifact3() != context.artifact3)
        {
            Handle_Equipment(sys, character, bank_pos, context.artifact1.c_str(), 1, Keywords::ItemSlot::artifact3);
            return;
        }
        if (context.should_heal == true)
        {
            const int levelDiff = character.Get_Skill_Level(Keywords::Skills::combat) - context.monster_level;
            if (levelDiff < 5)
            {
                if (Equip_Healing_Stuff(sys, character, bank_pos) == true)
                {
                    return;
                }
                Add_Healing(sys, character);
            }
            else
            {
                character.Add_Rest(sys);
            }
            return;
        }
        character.Add_Fight(sys, monster);
    }
}

void FightSystem::Add_Healing(const System* sys, Character& character)
{
    const int l_Chararter_Max_Life     = character.Get_Life_Max();
    const int l_Character_Combat_Level = character.Get_Skill_Level(Keywords::Skills::combat);
    int l_Current_Hp                   = character.Get_Life_Current();
    std::vector<int> use;

    use.resize(m_Healing_Items.size());
    for (std::size_t ii = 0; ii < m_Healing_Items.size(); ii++)
    {
        for (int item_count = character.Get_Item_Count(m_Healing_Items[ii].code);
             (item_count > 0) && ((l_Chararter_Max_Life - l_Current_Hp) > m_Healing_Items[ii].heal) &&
             (l_Character_Combat_Level > m_Healing_Items[ii].required_level);
             item_count--)
        {
            use[ii]++;
            l_Current_Hp += m_Healing_Items[ii].heal;
        }
    }

    for (std::size_t ii = 0; ii < use.size(); ii++)
    {
        if (use[ii] != 0)
        {
            SYSTEM_PRINT("will use item '%s' x%d", m_Healing_Items[ii].code, use[ii]);
            character.Add_UseItem(sys, { m_Healing_Items[ii].code, use[ii] });
        }
    }

    if (l_Current_Hp < l_Chararter_Max_Life)
    {
        character.Add_Rest(sys);
    }
}

#define FIGHT_SYSTEM_DEBUG

bool FightSystem::MayWin(const Character& character, const char* monster, FightConfig config, FightContext& context)
{
    static const std::array<const char*, 4> attck_names = {
        { "attack_fire", "attack_water", "attack_earth", "attack_air" }
    };

    const int l_Character_Combat_Level = character.Get_Skill_Level(Keywords::Skills::combat);
    const int l_Monster_Level          = MonsterManager::singleton.Get_Monster_Level(monster);
    if (l_Monster_Level > l_Character_Combat_Level)
    {
        return false;
    }
    const std::array<int, 4> l_Monster_Attack  = MonsterManager::singleton.Get_Monster_Attack(monster);
    std::array<int, 4> l_Monster_Resistance    = MonsterManager::singleton.Get_Monster_Resistance(monster);
    const std::array<int, 4> l_Monster_Damages = {
        { 0, 0, 0, 0 }
    };
    int l_Poison                              = MonsterManager::singleton.Get_Monster_Effect_Poison(monster);
    const int l_Corruption                    = MonsterManager::singleton.Get_Monster_Effect_Corruption(monster);
    std::array<int, 4> l_Character_Attack     = character.Get_Attack();
    std::array<int, 4> l_Character_Damages    = character.Get_Damage();
    std::array<int, 4> l_Character_Resistance = character.Get_Resistance();
    std::vector<InventoryWeapons> l_Weapons;
    std::vector<InventoryArmorPart> l_Helmets;
    std::vector<InventoryArmorPart> l_Body_Armor;
    std::vector<InventoryArmorPart> l_Leg_Armor;
    std::vector<InventoryArmorPart> l_Boots;
    std::vector<InventoryArmorPart> l_Rings;
    std::vector<InventoryArmorPart> l_Shields;
    std::vector<InventoryArmorPart> l_Amulets;
    int l_Character_Dmg                 = Calculate_Effective_Damages(l_Character_Attack, l_Character_Damages, l_Monster_Resistance, 0);
    const int l_Monster_Critical_Strike = MonsterManager::singleton.Get_Monster_Critical_Strike(monster);
    int l_Monster_Dmg = Calculate_Effective_Damages(l_Monster_Attack, l_Monster_Damages, l_Character_Resistance, l_Monster_Critical_Strike);

    int l_Monster_Life       = MonsterManager::singleton.Get_Monster_Hp(monster);
    int l_Character_Max_Life = character.Get_Life_Max();

    HealItem l_Equiped_Healing_Potion;

    memset(&l_Equiped_Healing_Potion, 0, sizeof(l_Equiped_Healing_Potion));

    auto armor_handler = [&](const std::vector<InventoryArmorPart>& armors, std::string& context_armor)
    {
        int current_armor_hp = ItemManager::singleton.Get_Armor_Hp(context_armor.c_str());
        SYSTEM_PRINT("current armor '%s'", context_armor.c_str());
        for (std::size_t ii = 0; ii < armors.size(); ii++)
        {
            const int l_Hp = ItemManager::singleton.Get_Armor_Hp(armors[ii].code.c_str());
            if (l_Hp < current_armor_hp)
            {
                continue;
            }

            // SYSTEM_PRINT("armor '%s' %d >= %d", armors[ii].code.c_str(), l_Hp, current_armor_hp);

            if (l_Hp == current_armor_hp)
            {
                const int l_Damages =
                    Calculate_Effective_Damages(l_Monster_Attack, l_Monster_Damages, armors[ii].resistances, l_Monster_Critical_Strike);
                if (l_Damages < l_Monster_Dmg)
                {
                    /*SYSTEM_PRINT("will try using armor '%s' l_Monster_Dmg: %d l_Damages: %d", armors[ii].code.c_str(), l_Monster_Dmg,
                                 l_Damages);*/
                    l_Monster_Dmg          = l_Damages;
                    l_Character_Resistance = armors[ii].resistances;
                    context_armor          = armors[ii].code;
                }
                continue;
            }

            if (armors[ii].code != context_armor)
            {
                current_armor_hp       = l_Hp;
                l_Character_Resistance = armors[ii].resistances;
                context_armor          = armors[ii].code;
                l_Monster_Dmg          = Calculate_Effective_Damages(l_Monster_Attack, l_Monster_Damages, armors[ii].resistances, 0);
                // SYSTEM_PRINT("will try using armor '%s'", armors[ii].code.c_str());
            }
        }
    };

    context.weapon            = character.Get_Equiped_Weapon();
    context.helmet            = character.Get_Equiped_Helmet();
    context.body_armor        = character.Get_Equiped_Body_Armor();
    context.leg_armor         = character.Get_Equiped_Leg_Armor();
    context.boots             = character.Get_Equiped_Boots();
    context.ring1             = character.Get_Equiped_Ring1();
    context.ring2             = character.Get_Equiped_Ring2();
    context.shield            = character.Get_Equiped_Shield();
    context.amulet            = character.Get_Equiped_Amulet();
    context.utility1          = character.Get_Equiped_Utility1();
    context.utility1_quantity = character.Get_Equiped_Utility1_Quantity();
    if (l_Character_Combat_Level > 9)
    {
        context.artifact1 = "novice_guide";
    }

    character.Get_Fight_Items(ItemManager::singleton, l_Character_Combat_Level, l_Weapons, l_Helmets, l_Body_Armor, l_Leg_Armor, l_Boots,
                              l_Shields, l_Rings, l_Amulets);
    InventoryManager::singleton.Get_Fight_Items(l_Character_Combat_Level, l_Weapons, l_Helmets, l_Body_Armor, l_Leg_Armor, l_Boots,
                                                l_Shields, l_Rings, l_Amulets);

    SYSTEM_PRINT("try to fight against '%s'", monster);

    context.monster_level = MonsterManager::singleton.Get_Monster_Level(monster);

    SYSTEM_PRINT("equipped weapon: '%s'", context.weapon.c_str());
    for (std::size_t ii = 0; ii < l_Weapons.size(); ii++)
    {
        const InventoryWeapons& l_Weapon = l_Weapons[ii];
        const int l_Weapon_Dmg           = Calculate_Effective_Damages(l_Weapon.attacks, l_Weapon.damages, l_Monster_Resistance, 0);
        SYSTEM_PRINT("weapon: '%s' [%d %d %d %d] dmg: %d", l_Weapon.code.c_str(), l_Weapon.attacks[0], l_Weapon.attacks[1],
                     l_Weapon.attacks[2], l_Weapon.attacks[3], l_Weapon_Dmg);
        if (l_Weapon_Dmg > l_Character_Dmg)
        {
            SYSTEM_PRINT("try using weapon '%s' (%d better than %d)", l_Weapon.code.c_str(), l_Weapon_Dmg, l_Character_Dmg);
            l_Character_Dmg     = l_Weapon_Dmg;
            l_Character_Attack  = l_Weapon.attacks;
            l_Character_Damages = l_Weapon.damages;
            context.weapon      = l_Weapon.code;
        }
    }

    armor_handler(l_Helmets, context.helmet);
    armor_handler(l_Body_Armor, context.body_armor);
    armor_handler(l_Leg_Armor, context.leg_armor);
    armor_handler(l_Boots, context.boots);
    armor_handler(l_Shields, context.shield);
    const std::string currentRing1 = context.ring1;
    armor_handler(l_Rings, context.ring1);
    if (currentRing1 != context.ring1)
    {
        l_Rings.erase(std::find_if(l_Rings.begin(), l_Rings.end(), [&](const InventoryArmorPart& p) { return p.code == context.ring1; }));
    }
    armor_handler(l_Rings, context.ring2);
    armor_handler(l_Amulets, context.amulet);
    {
        if (context.utility1.size())
        {
            l_Equiped_Healing_Potion.code                   = context.utility1.c_str();
            l_Equiped_Healing_Potion.inventory_target_count = context.utility1_quantity;
            auto it = std::find_if(m_Healing_Potions.begin(), m_Healing_Potions.end(),
                                   [&](const HealItem& h) { return strcmp(h.code, l_Equiped_Healing_Potion.code) == 0; });
            if (it != m_Healing_Potions.end())
            {
                l_Equiped_Healing_Potion.heal = it->heal;
            }
        }
    }

    if (l_Poison > 0)
    {
        SYSTEM_PRINT("Must use antidote");
        const char* item_code     = Keywords::Items::Utilities::small_antidote;
        const int bank_count      = InventoryManager::singleton.Get_Bank_Item_Count(item_code);
        const int inventory_count = character.Get_Item_Count(item_code);
        if (bank_count > 0)
        {
            context.utility2          = item_code;
            context.utility2_quantity = std::min(5, bank_count);
            l_Poison                  = 0;
        }
        else if (inventory_count > 0)
        {
            context.utility2          = item_code;
            context.utility2_quantity = inventory_count;
            l_Poison                  = 0;
        }
    }
    else if (config.may_use_potion)
    {
        const int fire      = l_Monster_Resistance[0];
        const int water     = l_Monster_Resistance[1];
        const int earth     = l_Monster_Resistance[2];
        const int air       = l_Monster_Resistance[3];
        const int fire_att  = l_Character_Attack[0];
        const int water_att = l_Character_Attack[1];
        const int earth_att = l_Character_Attack[2];
        const int air_att   = l_Character_Attack[3];
        std::size_t idx;

        const char* item_code = nullptr;

        SYSTEM_PRINT("res [fire: %d water: %d earth: %d air: %d]", fire, water, earth, air);
        SYSTEM_PRINT("att [fire: %d water: %d earth: %d air: %d]", fire_att, water_att, earth_att, air_att);

        if (fire < 0 && fire_att > 0 && fire <= water && fire <= earth && fire <= air)
        {
            item_code = Keywords::Items::Utilities::fire_boost_potion;
            idx       = 0;
        }
        else if (water < 0 && water_att > 0 && water <= earth && water <= air)
        {
            item_code = Keywords::Items::Utilities::water_boost_potion;
            idx       = 1;
        }
        else if (earth < 0 && earth_att > 0 && earth <= air)
        {
            item_code = Keywords::Items::Utilities::earth_boost_potion;
            idx       = 2;
        }
        else if (air < 0 && air_att > 0)
        {
            item_code = Keywords::Items::Utilities::air_boost_potion;
            idx       = 3;
        }

        if (item_code != nullptr && (InventoryManager::singleton.Get_Bank_Item_Count(item_code) > 0))
        {
            context.utility2          = item_code;
            context.utility2_quantity = std::min(5, InventoryManager::singleton.Get_Bank_Item_Count(item_code));
            l_Character_Damages[idx] += 12;
            SYSTEM_PRINT("will equip '%s' x%d", item_code, context.utility2_quantity);
        }
    }

    context.turn_count = 0;
    bool l_Player_Turn = character.Get_Initiative() > MonsterManager::singleton.Get_Monster_Initiative(monster);
    while (l_Monster_Life > 0)
    {
        const int l_Character_Dmg = Calculate_Effective_Damages(l_Character_Attack, l_Character_Damages, l_Monster_Resistance, 0);
        const int l_Monster_Dmg =
            Calculate_Effective_Damages(l_Monster_Attack, l_Monster_Damages, l_Character_Resistance, l_Monster_Critical_Strike) + l_Poison;

        /// update data
        {
            /// Corruption
            for (std::size_t ii = 0; ii < 4; ii++)
            {
                l_Monster_Resistance[ii] -= l_Corruption * (l_Character_Damages[ii] > 0);
            }
        }

// #error "Handle properly healing during fight ?"
// #error "Make multiple time the same fight but with potions ?"
#if 0
        if (l_Character_Max_Life < character.Get_Life_Max() / 2)
        {
            if (l_Equiped_Healing_Potion.inventory_target_count > 0)
            {
                l_Character_Max_Life += l_Equiped_Healing_Potion.heal;
                l_Equiped_Healing_Potion.inventory_target_count--;
            }
        }
#endif

        if (l_Player_Turn == true)
        {
            l_Monster_Life -= l_Character_Dmg;
            l_Player_Turn = false;
        }
        else
        {
            l_Character_Max_Life -= l_Monster_Dmg;
            l_Player_Turn = true;
        }
        context.turn_count++;
#ifdef FIGHT_SYSTEM_DEBUG
        if (strcmp(character.Get_Character(), "Niva") == 0 && strcmp(monster, "spider") == 0)
        {
            SYSTEM_PRINT("turn %d '%s' %d/%d (monster dmg %d) vs '%s' %d/%d (character dmg %d)", context.turn_count,
                         character.Get_Character(), l_Character_Max_Life, character.Get_Life_Max(), l_Monster_Dmg, monster, l_Monster_Life,
                         MonsterManager::singleton.Get_Monster_Hp(monster), l_Character_Dmg);
        }
#endif
    }

    const int level_diff = l_Character_Combat_Level - l_Monster_Level;
    if (config.may_use_potion && l_Character_Max_Life <= 0 && (level_diff < 10))
    {
        SYSTEM_PRINT("may win using potions?");
        /// Even while healing potions character failed
        for (std::size_t ii = 0; ii < m_Healing_Potions.size(); ii++)
        {
            const HealItem& hi = m_Healing_Potions[ii];
            if (l_Character_Combat_Level < hi.required_level)
            {
                SYSTEM_PRINT("can't equip '%s' (level: %d required: %d)", hi.code, l_Character_Combat_Level, hi.required_level);
                continue;
            }
            // #error "Have to count exactly how many are required and get all but equip what is needed"
            const int bank_item_count = InventoryManager::singleton.Get_Bank_Item_Count(hi.code);

            if (bank_item_count <= 0)
            {
                SYSTEM_PRINT("no '%s' in bank", hi.code);
                continue;
            }

            {
                const int l_Monster_Dmg =
                    Calculate_Effective_Damages(l_Monster_Attack, l_Monster_Damages, l_Character_Resistance, l_Monster_Critical_Strike) +
                    l_Poison;
                if (hi.heal < (l_Monster_Dmg / 2))
                {
                    SYSTEM_PRINT("'%s' is not powerful enough", hi.code);
                    continue;
                }
            }

            const int max_potion_count      = std::min(bank_item_count, character.Get_Inventory_Remaining_Space() - 1);
            const int hp_to_win             = abs(l_Character_Max_Life) + 1;
            const int required_potion_count = ceil((float)hp_to_win / hi.heal);
            SYSTEM_PRINT("may win using '%s' x%d", hi.code, required_potion_count);
            if ((required_potion_count < max_potion_count) && (required_potion_count < 10))
            {
                context.utility1          = hi.code;
                context.utility1_quantity = required_potion_count;
                l_Character_Max_Life += required_potion_count * hi.heal;
                SYSTEM_PRINT("will equip with '%s' x%d (l_Character_Max_Life: %d)", hi.code, required_potion_count, l_Character_Max_Life);
                break;
            }
        }
    }

    context.should_heal = character.Get_Life_Current() < (character.Get_Life_Max() - l_Character_Max_Life);

    SYSTEM_PRINT(
        "vs '%s': %s (hp diff: %d - turn count: %d - heal: %d - weapon: '%s' - helmet: '%s' body_armor: '%s' leg_armor: '%s' boots: "
        "'%s' shield: '%s' ring1: '%s' ring2: '%s' amulet: '%s' utility1: '%s' x%d utility2: '%s' x%d artifact1: '%s' artifact2: '%s' "
        "artifact3: '%s')",
        monster, (l_Character_Max_Life > 0) ? "win" : "loose", l_Character_Max_Life - l_Monster_Life, context.turn_count,
        context.should_heal, context.weapon.c_str(), context.helmet.c_str(), context.body_armor.c_str(), context.leg_armor.c_str(),
        context.boots.c_str(), context.shield.c_str(), context.ring1.c_str(), context.ring2.c_str(), context.amulet.c_str(),
        context.utility1.c_str(), context.utility1_quantity, context.utility2.c_str(), context.utility2_quantity, context.artifact1.c_str(),
        context.artifact2.c_str(), context.artifact3.c_str());

    return l_Character_Max_Life > 0;
}

int FightSystem::Calculate_Effective_Damages(const std::array<int, 4>& attack, const std::array<int, 4>& damages,
                                             const std::array<int, 4>& resistance, int critical_strike)
{
    const std::array<int, 4> l_Tmp = {
        { static_cast<int>(round(attack[0] * (1.0f + 0.01f * (damages[0] - resistance[0])))),
         static_cast<int>(round(attack[1] * (1.0f + 0.01f * (damages[1] - resistance[1])))),
         static_cast<int>(round(attack[2] * (1.0f + 0.01f * (damages[2] - resistance[2])))),
         static_cast<int>(round(attack[3] * (1.0f + 0.01f * (damages[3] - resistance[3])))) }
    };
    const int sum   = l_Tmp[0] + l_Tmp[1] + l_Tmp[2] + l_Tmp[3];
    const int total = sum + round((sum * critical_strike) / 100.0f);
    // printf("Calculate_Effective_Damages: sum: %d total: %d\n", sum, total);
    return total;
}

void FightSystem::Handle_Equipment(const System* sys, Character& character, const MapCoord& bank_pos, const char* equipment_name,
                                   int equipement_count, const char* equipmenet_type)
{
    if (character.Is_Empty() == true)
    {
        if (character.Get_Life_Current() < ItemManager::singleton.Get_Armor_Hp(equipment_name))
        {
            Add_Healing(this, character);
            return;
        }
        if (character.Get_Item_Count(equipment_name) < equipement_count)
        {
            if (character.Should_Move(bank_pos) == true)
            {
                character.Add_Move(sys, bank_pos);
            }
            else
            {
                const int item_count_to_withdraw = /*strcmp(equipmenet_type, Keywords::EquipementSlot::utility1_slot) == 0
                                                     ? InventoryManager::singleton.Get_Bank_Item_Count(equipment_name)
                                                     : */
                    equipement_count - character.Get_Item_Count(equipment_name);
                character.Add_Withdraw_Item(sys, { equipment_name, item_count_to_withdraw });
                if (character.Get_Equiped_Item(equipmenet_type).size() && character.Get_Equiped_Item(equipmenet_type) != equipment_name)
                {
                    const char* equiped_item = character.Get_Equiped_Item(equipmenet_type).c_str();
                    character.Add_Unequip_Item(sys, equipmenet_type, 1);  /// "1": has to be updated with utilities
                    character.Add_Deposit_Item(sys, { equiped_item, character.Get_Item_Count(equiped_item) + 1 });
                    // character.Add_Equip_Item(sys, equipmenet_type, equipment_name, equipement_count);
                }
            }
        }
        else
        {
            character.Add_Equip_Item(sys, equipmenet_type, equipment_name, character.Get_Item_Count(equipment_name));
        }
    }
}

bool FightSystem::Equip_Healing_Stuff(const System* sys, Character& character, const MapCoord& bank_pos) const
{
    bool inventory_has_healing_item = true;

    for (const HealItem& hi: m_Healing_Items)
    {
        inventory_has_healing_item &= character.Get_Item_Count(hi.code) > 0;
    }

    if (inventory_has_healing_item == true)
    {
        SYSTEM_PRINT("has healing item in inventory");
        return false;
    }

    if (character.Get_Inventory_Remaining_Slot_Count() < 5)
    {
        SYSTEM_PRINT("has to keep free space");
        return false;
    }

    for (const HealItem& hi: m_Healing_Items)
    {
        const char* item_code          = hi.code;
        const int item_target_quantity = hi.inventory_target_count;
        const int bank_item_count      = InventoryManager::singleton.Get_Bank_Item_Count(item_code);
        const int character_item_count = character.Get_Item_Count(item_code);
        const bool enough_hp           = character.Get_Life_Max() > (hi.heal * 3);

        if (enough_hp && bank_item_count > 0 && character_item_count == 0)
        {
            if (character.Should_Move(bank_pos) == true)
            {
                character.Add_Move(sys, bank_pos);
                return true;
            }

            const int item_quantity = std::min(std::min(character.Get_Inventory_Remaining_Space(), item_target_quantity), bank_item_count);
            character.Add_Withdraw_Item(sys, { item_code, item_quantity });

            /// If loop, return and do again in another frame (bank may have been updated and character cache will be updated)
            return true;
        }
    }

    SYSTEM_PRINT("no healing item in bank");
    return false;
}
