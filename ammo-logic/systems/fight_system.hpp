#ifndef _FIGHT_SYSTEM_HPP
#define _FIGHT_SYSTEM_HPP 1

#include "system.hpp"

class MonsterManager;
class ItemManager;
class FightSystem;

struct FightContext
{
    std::string weapon;
    std::string helmet;
    std::string body_armor;
    std::string leg_armor;
    std::string boots;
    std::string ring1;
    std::string ring2;
    std::string shield;
    std::string amulet;
    std::string utility1;
    std::string utility2;
    std::string artifact1;
    std::string artifact2;
    std::string artifact3;
    int utility1_quantity = 0;
    int utility2_quantity = 0;

    int monster_level = 0;
    int turn_count    = 0;
    bool should_heal;
    bool may_use_consumables;
};

class FightConfig
{
private:
    friend FightSystem;
    bool may_use_potion;
    bool may_use_consumables;

    FightConfig(bool potion, bool consumables);

public:
    static FightConfig DefaultConfig(void);
    static FightConfig MonsterTaskConfig(void);
    static FightConfig GatherResourcesConfig(void);
};

class FightSystem: public System
{
    FightSystem();

public:
    static FightSystem singleton;

    void Initialize(void);

    void Fill_Pipeline(Character& character) override;

    void Fight_Against(const System* sys, Character& character, const char* monster, const FightContext& context);

    void Add_Healing(const System* sys, Character& character);

    bool MayWin(const Character& character, const char* monster, FightConfig config, FightContext& context);

    int Calculate_Effective_Damages(const std::array<int, 4>& attack, const std::array<int, 4>& damages,
                                    const std::array<int, 4>& resistance, int critical_strike);

private:
    std::vector<std::string> m_Monsters;

    void Handle_Equipment(const System* sys, Character& character, const MapCoord& bank_pos, const char* equipment_name,
                          int equipement_count, const char* equipmenet_type);

    bool Equip_Healing_Stuff(const System* sys, Character& character, const MapCoord& bank_pos) const;

    struct HealItem
    {
        const char* code;
        int heal;
        int required_level;
        int inventory_target_count;
    };
    std::vector<HealItem> m_Healing_Items;
    std::vector<HealItem> m_Healing_Potions;
};

#endif  // _FIGHT_SYSTEM_HPP
