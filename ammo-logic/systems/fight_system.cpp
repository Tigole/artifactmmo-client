#include "fight_system.hpp"

#include <cmath>

#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"
#include "managers/monster_manager.hpp"

FightSystem FightSystem::singleton;

FightSystem::FightSystem() : System("FightSystem")
{
    m_Monsters.push_back("");

    // m_Healing_Items.push_back({ "fried_eggs", 150, 4, 20 });
    m_Healing_Items.push_back({ "cooked_chicken", 80, 0, 20 });
    m_Healing_Items.push_back({ "cooked_gudgeon", 75, 0, 20 });
    m_Healing_Items.push_back({ "apple", 50, 0, 20 });
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
        const MapCoord* l_Coord = MonsterManager::singleton.Get_Monster_Coord(l_Monster);
        if ((l_Coord != nullptr) && (MayWin(character, l_Monster, l_Context) == true))
        {
            Fight_Against(this, character, l_Monster, l_Context);
            return;
        }
    }
}

void FightSystem::Fight_Against(const System* sys, Character& character, const char* monster, const FightContext& context)
{
    const MapCoord* l_Coord = MonsterManager::singleton.Get_Monster_Coord(monster);
    if (l_Coord != nullptr)
    {
        const MapCoord bank_pos = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);
        if (character.Get_Equiped_Weapon() != context.weapon)
        {
            Handle_Equipment(sys, character, bank_pos, context.weapon.c_str(), "weapon");
            return;
        }
        if (character.Get_Equiped_Helmet() != context.helmet)
        {
            Handle_Equipment(sys, character, bank_pos, context.helmet.c_str(), "helmet");
            return;
        }
        if (character.Get_Equiped_Body_Armor() != context.body_armor)
        {
            Handle_Equipment(sys, character, bank_pos, context.body_armor.c_str(), "body_armor");
            return;
        }
        if (character.Get_Equiped_Leg_Armor() != context.leg_armor)
        {
            Handle_Equipment(sys, character, bank_pos, context.leg_armor.c_str(), "leg_armor");
            return;
        }
        if (character.Get_Equiped_Boots() != context.boots)
        {
            Handle_Equipment(sys, character, bank_pos, context.boots.c_str(), "boots");
            return;
        }
        if (character.Get_Equiped_Ring1() != context.ring1)
        {
            Handle_Equipment(sys, character, bank_pos, context.ring1.c_str(), "ring1");
            return;
        }
        if (character.Get_Equiped_Ring2() != context.ring2)
        {
            Handle_Equipment(sys, character, bank_pos, context.ring2.c_str(), "ring2");
            return;
        }
        if (character.Get_Equiped_Shield() != context.shield)
        {
            Handle_Equipment(sys, character, bank_pos, context.shield.c_str(), "shield");
            return;
        }
        if (character.Get_Equiped_Amulet() != context.amulet)
        {
            Handle_Equipment(sys, character, bank_pos, context.amulet.c_str(), "amulet");
            return;
        }
        if (character.Get_Equiped_Utility1() != context.utility1)
        {
            Handle_Equipment(sys, character, bank_pos, context.utility1.c_str(), "utility1");
            return;
        }
        if (character.Get_Equiped_Artifact1() != context.artifact1)
        {
            Handle_Equipment(sys, character, bank_pos, context.artifact1.c_str(), "artifact1");
            return;
        }
        if (character.Get_Equiped_Artifact2() != context.artifact2)
        {
            Handle_Equipment(sys, character, bank_pos, context.artifact1.c_str(), "artifact2");
            return;
        }
        if (character.Get_Equiped_Artifact3() != context.artifact3)
        {
            Handle_Equipment(sys, character, bank_pos, context.artifact1.c_str(), "artifact3");
            return;
        }
        if (Equip_Healing_Stuff(sys, character, bank_pos) == true)
        {
            return;
        }
        if (context.should_heal == true)
        {
            Add_Healing(sys, character);
        }
        character.Add_Move(sys, *l_Coord);
        character.Add_Fight(sys);
    }
}

void FightSystem::Add_Healing(const System* sys, Character& character)
{
    const int l_Chararter_Max_Life     = character.Get_Life_Max();
    const int l_Character_Combat_Level = character.Get_Skill_Level("combat");
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

bool FightSystem::MayWin(const Character& character, const char* monster, FightContext& context)
{
    static const std::array<const char*, 4> attck_names = {
        { "attack_fire", "attack_water", "attack_earth", "attack_air" }
    };

    const int l_Character_Combat_Level            = character.Get_Skill_Level("combat");
    const std::array<int, 4> l_Monster_Attack     = MonsterManager::singleton.Get_Monster_Attack(monster);
    const std::array<int, 4> l_Monster_Resistance = MonsterManager::singleton.Get_Monster_Resistance(monster);
    const std::array<int, 4> l_Monster_Damages    = {
        { 0, 0, 0, 0 }
    };
    std::array<int, 4> l_Character_Attack     = character.Get_Attack();
    std::array<int, 4> l_Character_Damages    = character.Get_Damage();
    std::array<int, 4> l_Character_Resistance = character.Get_Resistance();
    std::vector<InventoryWeapons> l_Weapons;
    std::vector<InventoryArmorPart> l_Helmets;
    std::vector<InventoryArmorPart> l_Body_Armor;
    std::vector<InventoryArmorPart> l_Leg_Armor;
    std::vector<InventoryArmorPart> l_Boots;
    std::vector<InventoryArmorPart> l_Rings1;
    std::vector<InventoryArmorPart> l_Rings2;
    std::vector<InventoryArmorPart> l_Shields;
    std::vector<InventoryArmorPart> l_Amulets;
    int l_Character_Dmg = Calculate_Effective_Damages(l_Character_Attack, l_Character_Damages, l_Monster_Resistance);
    int l_Monster_Dmg   = Calculate_Effective_Damages(l_Monster_Attack, l_Monster_Damages, l_Character_Resistance);

    int l_Monster_Life        = MonsterManager::singleton.Get_Monster_Hp(monster);
    int l_Chararcter_Max_Life = character.Get_Life_Max();

    int l_Small_Potion_Count = 0;

    auto armor_handler = [&](const std::vector<InventoryArmorPart>& armors, std::string& context_armor)
    {
        for (std::size_t ii = 0; ii < armors.size(); ii++)
        {
            const int l_Damages = Calculate_Effective_Damages(l_Monster_Attack, l_Monster_Damages, armors[ii].resistances);
            if (l_Damages < l_Monster_Dmg)
            {
                l_Monster_Dmg          = l_Damages;
                l_Character_Resistance = armors[ii].resistances;
                context_armor          = armors[ii].code;
            }
        }
    };

    context.weapon     = character.Get_Equiped_Weapon();
    context.helmet     = character.Get_Equiped_Helmet();
    context.body_armor = character.Get_Equiped_Body_Armor();
    context.leg_armor  = character.Get_Equiped_Leg_Armor();
    context.boots      = character.Get_Equiped_Boots();
    context.ring1      = character.Get_Equiped_Ring1();
    context.ring2      = character.Get_Equiped_Ring2();
    context.shield     = character.Get_Equiped_Shield();
    context.amulet     = character.Get_Equiped_Amulet();
    context.utility1   = character.Get_Equiped_Utility1();
    if (l_Character_Combat_Level > 9)
    {
        context.artifact1 = "novice_guide";
    }

    InventoryManager::singleton.Get_Fight_Items(l_Character_Combat_Level, l_Weapons, l_Helmets, l_Body_Armor, l_Leg_Armor, l_Boots,
                                                l_Shields, l_Rings1, l_Rings2, l_Amulets);
    character.Get_Fight_Items(ItemManager::singleton, l_Character_Combat_Level, l_Weapons, l_Helmets, l_Body_Armor, l_Leg_Armor, l_Boots,
                              l_Shields, l_Rings1, l_Rings2, l_Amulets);

    SYSTEM_PRINT("equipped weapon: '%s'", context.weapon.c_str());
    for (std::size_t ii = 0; ii < l_Weapons.size(); ii++)
    {
        const InventoryWeapons& l_Weapon = l_Weapons[ii];
        const int l_Weapon_Dmg           = Calculate_Effective_Damages(l_Weapon.attacks, l_Weapon.damages, l_Monster_Resistance);
        SYSTEM_PRINT("weapon: '%s' [%d %d %d %d] dmg: %d", l_Weapon.code.c_str(), l_Weapon.attacks[0], l_Weapon.attacks[1],
                     l_Weapon.attacks[2], l_Weapon.attacks[3], l_Weapon_Dmg);
        if (l_Weapon_Dmg > l_Character_Dmg)
        {
            SYSTEM_PRINT("try using weapon '%s' (%d better than %d)", l_Weapon.code.c_str(), l_Character_Dmg, l_Weapon_Dmg);
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
    armor_handler(l_Rings1, context.ring1);
    armor_handler(l_Rings2, context.ring2);
    armor_handler(l_Amulets, context.amulet);

    context.turn_count = 0;
    bool l_Player_Turn = true;
    while ((l_Monster_Life > 0) && (l_Chararcter_Max_Life > 0))
    {
        const int l_Character_Dmg = Calculate_Effective_Damages(l_Character_Attack, l_Character_Damages, l_Monster_Resistance);
        const int l_Monster_Dmg   = Calculate_Effective_Damages(l_Monster_Attack, l_Monster_Damages, l_Character_Resistance);

        if (l_Chararcter_Max_Life < character.Get_Life_Max() / 2)
        {
            if (l_Small_Potion_Count > 0)
            {
                l_Chararcter_Max_Life += 30;
                l_Small_Potion_Count--;
            }
        }

        if (l_Player_Turn == true)
        {
            l_Monster_Life -= l_Character_Dmg;
            l_Player_Turn = false;
        }
        else
        {
            l_Chararcter_Max_Life -= l_Monster_Dmg;
            l_Player_Turn = true;
        }
        context.turn_count++;
        SYSTEM_PRINT("turn %d '%s' %d/%d (monster dmg %d) vs '%s' %d/%d (character dmg %d)", context.turn_count, character.Get_Character(),
                     l_Chararcter_Max_Life, character.Get_Life_Max(), l_Monster_Dmg, monster, l_Monster_Life,
                     MonsterManager::singleton.Get_Monster_Hp(monster), l_Character_Dmg);
    }

    if (l_Chararcter_Max_Life <= 0)
    {
        if (l_Chararcter_Max_Life > -30 && (character.Get_Equiped_Utility1() == "small_health_potion"))
        {
            l_Chararcter_Max_Life += 30;
            context.utility1 = "small_health_potion";
        }
    }

    context.should_heal = character.Get_Life_Current() < (character.Get_Life_Max() - l_Chararcter_Max_Life);

    SYSTEM_PRINT(
        "vs '%s': %s (hp diff: %d - turn count: %d - heal: %d - weapon: '%s' - helmet: '%s' body_armor: '%s' leg_armor: '%s' boots: "
        "'%s' shield: '%s' ring1: '%s' ring2: '%s' amulet: '%s' utility1: '%s' artifact1: '%s' artifact2: '%s' artifact3: '%s'",
        monster, (l_Chararcter_Max_Life > 0) ? "win" : "loose", l_Chararcter_Max_Life - l_Monster_Life, context.turn_count,
        context.should_heal, context.weapon.c_str(), context.helmet.c_str(), context.body_armor.c_str(), context.leg_armor.c_str(),
        context.boots.c_str(), context.shield.c_str(), context.ring1.c_str(), context.ring2.c_str(), context.amulet.c_str(),
        context.utility1.c_str(), context.artifact1.c_str(), context.artifact2.c_str(), context.artifact3.c_str());

    return l_Chararcter_Max_Life > 0;
}

int FightSystem::Calculate_Effective_Damages(const std::array<int, 4>& attack, const std::array<int, 4>& damages,
                                             const std::array<int, 4>& resistance)
{
    const std::array<int, 4> l_Tmp = {
        { static_cast<int>(round(attack[0] * (1.0f + 0.01f * (damages[0] - resistance[0])))),
         static_cast<int>(round(attack[1] * (1.0f + 0.01f * (damages[1] - resistance[1])))),
         static_cast<int>(round(attack[2] * (1.0f + 0.01f * (damages[2] - resistance[2])))),
         static_cast<int>(round(attack[3] * (1.0f + 0.01f * (damages[3] - resistance[3])))) }
    };
    for (std::size_t ii = 0; ii < 4 && false; ii++)
    {
        printf("[%d] att: %d dmg: %d res: %d tot: %d\n", ii, attack[ii], damages[ii], resistance[ii], l_Tmp[ii]);
    }
    return l_Tmp[0] + l_Tmp[1] + l_Tmp[2] + l_Tmp[3];
}

const MapCoord* FightSystem::Get_Monster_Coord(const char* monster)
{
    return MonsterManager::singleton.Get_Monster_Coord(monster);
}

void FightSystem::Handle_Equipment(const System* sys, Character& character, const MapCoord& bank_pos, const char* equipment_name,
                                   const char* equipmenet_type)
{
    if (character.Is_Empty() == true)
    {
        if (character.Get_Item_Count(equipment_name) < 1)
        {
            if (character.Should_Move(bank_pos) == true)
            {
                character.Add_Move(sys, bank_pos);
            }
            else
            {
                if (character.Get_Equiped_Item(equipmenet_type).size())
                {
                    const char* equiped_item = character.Get_Equiped_Item(equipmenet_type).c_str();
                    character.Add_Unequip_Item(sys, equipmenet_type);
                    character.Add_Deposit_Item(sys, { equiped_item, character.Get_Item_Count(equiped_item) + 1 });
                }
                character.Add_Withdraw_Item(sys, { equipment_name, 1 });
            }
        }
        else
        {
            character.Add_Equip_Item(sys, equipmenet_type, equipment_name);
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

    for (const HealItem& hi: m_Healing_Items)
    {
        const char* item_code          = hi.code;
        const int item_target_quantity = hi.inventory_target_count;
        const int bank_item_count      = InventoryManager::singleton.Get_Bank_Item_Count(item_code);
        const int character_item_count = character.Get_Item_Count(item_code);

        if (bank_item_count > 0 && character_item_count == 0)
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
