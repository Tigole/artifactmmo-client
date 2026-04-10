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
public:
    FightSystem(MonsterManager& monsters, const ItemManager& items, const InventoryManager& bank);

    void Initialize(void);

    void Fill_Pipeline(Character& character) override;

    void Fight_Against(Character& character, const char* monster, const FightContext& context);

    void Add_Healing(Character& character);

    bool MayWin(const Character& character, const char* monster, FightContext& context);

    int Calculate_Effective_Damages(const std::array<int, 4>& attack, const std::array<int, 4>& damages,
                                    const std::array<int, 4>& resistance);

    const MapCoord* Get_Monster_Coord(const char* monster);

private:
    MonsterManager& m_Monster_Manager;
    const ItemManager& m_Item_Manager;
    const InventoryManager& m_Bank;
    std::vector<std::string> m_Monsters;

    static void Handle_Equipment(Character& character, const MapCoord& bank_pos, const char* equipment_name, const char* equipmenet_type);
};

#endif  // _FIGHT_SYSTEM_HPP
