#ifndef _FIGHT_SYSTEM_HPP
#define _FIGHT_SYSTEM_HPP 1

#include "system.hpp"

class MonsterManager;
class ItemManager;

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
    int turn_count;
    bool should_heal;
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

    bool MayWin(const Character& character, const char* monster, FightContext& context);

    int Calculate_Effective_Damages(const std::array<int, 4>& attack, const std::array<int, 4>& damages,
                                    const std::array<int, 4>& resistance);

    const MapCoord* Get_Monster_Coord(const char* monster);

private:
    std::vector<std::string> m_Monsters;

    void Handle_Equipment(const System* sys, Character& character, const MapCoord& bank_pos, const char* equipment_name,
                          const char* equipmenet_type);

    bool Equip_Healing_Stuff(const System* sys, Character& character, const MapCoord& bank_pos) const;

    struct HealItem
    {
        const char* code;
        int heal;
        int required_level;
        int inventory_target_count;
    };
    std::vector<HealItem> m_Healing_Items;
};

#endif  // _FIGHT_SYSTEM_HPP
