#include "fight_system.hpp"

#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"
#include "managers/monster_manager.hpp"

FightSystem FightSystem::singleton;

FightSystem::FightSystem() : System("FightSystem")
{
    m_Monsters.push_back("");
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
        /*if (character.Get_Equiped_Helmet() != context.helmet)
        {
            Handle_Equipment(character, bank_pos, context.helmet.c_str(), "helmet");
            return;
        }
        if (character.Get_Equiped_Body_Armor() != context.body_armor)
        {
            Handle_Equipment(character, bank_pos, context.body_armor.c_str(), "body_armor");
            return;
        }
        if (character.Get_Equiped_Leg_Armor() != context.leg_armor)
        {
            Handle_Equipment(character, bank_pos, context.leg_armor.c_str(), "leg_armor");
            return;
        }
        if (character.Get_Equiped_Boots() != context.boots)
        {
            Handle_Equipment(character, bank_pos, context.boots.c_str(), "boots");
            return;
        }
        if (character.Get_Equiped_Ring1() != context.ring1)
        {
            Handle_Equipment(character, bank_pos, context.ring1.c_str(), "ring1");
            return;
        }
        if (character.Get_Equiped_Ring2() != context.ring2)
        {
            Handle_Equipment(character, bank_pos, context.ring2.c_str(), "ring2");
            return;
        }
        if (character.Get_Equiped_Shield() != context.shield)
        {
            Handle_Equipment(character, bank_pos, context.shield.c_str(), "shield");
            return;
        }
        if (character.Get_Equiped_Amulet() != context.amulet)
        {
            Handle_Equipment(character, bank_pos, context.amulet.c_str(), "amulet");
            return;
        }
        if (character.Get_Equiped_Utility1() != context.utility1)
        {
            Handle_Equipment(character, bank_pos, context.utility1.c_str(), "utility1");
            return;
        }*/
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
    struct HealItem
    {
        std::string code;
        int heal;
    };
    static const std::array<HealItem, 4> l_Items = {
        { { "fried_eggs", 150 }, { "cooked_chicken", 80 }, { "cooked_gudgeon", 75 }, { "apple", 50 } }
    };

    const int l_Chararcter_Max_Life = character.Get_Life_Max();
    int l_Current_Hp                = character.Get_Life_Current();

    for (std::size_t ii = 0; ii < l_Items.size(); ii++)
    {
        if (character.Get_Item_Count(l_Items[ii].code.c_str()) > 0)
        {
            if ((l_Chararcter_Max_Life - l_Current_Hp) > l_Items[ii].heal)
            {
                character.Add_UseItem(sys, { l_Items[ii].code, 1 });
                l_Current_Hp += l_Items[ii].heal;
            }
        }
    }
    if (l_Current_Hp < l_Chararcter_Max_Life)
    {
        character.Add_Rest(sys);
    }
}

/*template <>
struct fmt::formatter<FightContext> :
    fmt::formatter<std::string> {
  auto format(const FightContext& conste, format_context& ctx) const {
    return fmt::format();
  }
};*/

bool FightSystem::MayWin(const Character& character, const char* monster, FightContext& context)
{
    static const std::array<const char*, 4> attck_names = {
        { "attack_fire", "attack_water", "attack_earth", "attack_air" }
    };

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

    int l_Small_Potion_Count = 1;

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

    InventoryManager::singleton.Get_Fight_Items(character.Get_Skill_Level("combat"), l_Weapons, l_Helmets, l_Body_Armor, l_Leg_Armor,
                                                l_Boots, l_Shields, l_Rings1, l_Rings2, l_Amulets);
    character.Get_Fight_Items(ItemManager::singleton, character.Get_Skill_Level("combat"), l_Weapons, l_Helmets, l_Body_Armor, l_Leg_Armor,
                              l_Boots, l_Shields, l_Rings1, l_Rings2, l_Amulets);

    printf("equipped weapon: '%s'\n", context.weapon.c_str());
    for (std::size_t ii = 0; ii < l_Weapons.size(); ii++)
    {
        const InventoryWeapons& l_Weapon = l_Weapons[ii];
        printf("weapon: '%s'\n", l_Weapon.code.c_str());
        const int l_Weapon_Dmg = Calculate_Effective_Damages(l_Weapon.attacks, l_Weapon.damages, l_Monster_Resistance);
        if (l_Weapon_Dmg > l_Character_Dmg)
        {
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

    /*printf("'%s' %d (turn count: %d - heal: %d - weapon: '%s') <-> '%s' %d\n", character.Get_Character(), l_Chararcter_Max_Life,
           context.turn_count, context.should_heal, context.weapon.c_str(), monster, l_Monster_Life);*/
    printf(
        "'%s' vs '%s': %s (hp diff: %d - turn count: %d - heal: %d - weapon: '%s' - helmet: '%s' body_armor: '%s' leg_armor: '%s' boots: "
        "'%s' shield: '%s' ring1: '%s' ring2: '%s' amulet: '%s' utility1: '%s'\n",
        character.Get_Character(), monster, (l_Chararcter_Max_Life > 0) ? "win" : "loose", l_Chararcter_Max_Life - l_Monster_Life,
        context.turn_count, context.should_heal, context.weapon.c_str(), context.helmet.c_str(), context.body_armor.c_str(),
        context.leg_armor.c_str(), context.boots.c_str(), context.shield.c_str(), context.ring1.c_str(), context.ring2.c_str(),
        context.amulet.c_str(), context.utility1.c_str());

    return l_Chararcter_Max_Life > 0;
}

int FightSystem::Calculate_Effective_Damages(const std::array<int, 4>& attack, const std::array<int, 4>& damages,
                                             const std::array<int, 4>& resistance)
{
    const std::array<int, 4> l_Tmp = {
        { static_cast<int>(attack[0] * (1.0f + 0.01f * (damages[0] - resistance[0]))),
         static_cast<int>(attack[1] * (1.0f + 0.01f * (damages[1] - resistance[1]))),
         static_cast<int>(attack[2] * (1.0f + 0.01f * (damages[2] - resistance[2]))),
         static_cast<int>(attack[3] * (1.0f + 0.01f * (damages[3] - resistance[3]))) }
    };
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
