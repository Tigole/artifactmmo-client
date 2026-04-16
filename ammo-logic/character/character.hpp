#ifndef _CHARACTER_HPP
#define _CHARACTER_HPP 1

#include <array>
#include <vector>

#include "types.hpp"

class Client;
class ItemManager;
class InventoryManager;
class System;

enum class CharacterOrderType
{
    Move,
    Fight,
    Rest,
    Craft,
    UseItem,
    UnequipItem,
    EquipItem,
    Gathering,
    Recycling,
    TaskNew,
    TaskTrade,
    TaskComplete,
    DepositItem,
    WithdrawItem,
    DepositGold,
    WithdrawGold,
    BuyItem,

    ClearInventory,
};

struct CharacterOrder
{
    static CharacterOrder CreateMove(const System* sys, const MapCoord& coord)
    {
        return { sys, CharacterOrderType::Move, coord, ItemOrder {}, "" };
    }
    static CharacterOrder CreateFight(const System* sys)
    {
        return { sys, CharacterOrderType::Fight, MapCoord {}, ItemOrder {}, "" };
    }
    static CharacterOrder CreateRest(const System* sys)
    {
        return { sys, CharacterOrderType::Rest, MapCoord {}, ItemOrder {}, "" };
    }
    static CharacterOrder CreateCraft(const System* sys, const ItemOrder& craft)
    {
        return { sys, CharacterOrderType::Craft, MapCoord {}, craft, "" };
    }
    static CharacterOrder CreateUseItem(const System* sys, const ItemOrder& item)
    {
        return { sys, CharacterOrderType::UseItem, MapCoord {}, item, "" };
    }
    static CharacterOrder CreateUnequipItem(const System* sys, const char* slot)
    {
        return { sys, CharacterOrderType::UnequipItem, MapCoord {}, ItemOrder {}, slot };
    }
    static CharacterOrder CreateEquipItem(const System* sys, const char* slot, const char* item_code)
    {
        return {
            sys, CharacterOrderType::EquipItem, MapCoord {},
               ItemOrder { item_code, 1 },
               slot
        };
    }
    static CharacterOrder CreateGathering(const System* sys)
    {
        return CharacterOrder(sys, CharacterOrderType::Gathering, {}, {}, "");
    }
    static CharacterOrder CreateRecycling(const System* sys, const ItemOrder& recycle)
    {
        return CharacterOrder(sys, CharacterOrderType::Recycling, {}, recycle, "");
    }
    static CharacterOrder CreateTaskNew(const System* sys)
    {
        return CharacterOrder(sys, CharacterOrderType::TaskNew, {}, {}, "");
    }
    static CharacterOrder CreateTaskTrade(const System* sys, const ItemOrder& trade)
    {
        return CharacterOrder(sys, CharacterOrderType::TaskTrade, {}, trade, "");
    }
    static CharacterOrder CreateTaskComplete(const System* sys)
    {
        return CharacterOrder(sys, CharacterOrderType::TaskComplete, {}, {}, "");
    }
    static CharacterOrder CreateDepositItem(const System* sys, const ItemOrder& deposit)
    {
        return CharacterOrder(sys, CharacterOrderType::DepositItem, {}, deposit, "");
    }
    static CharacterOrder CreateWithdrawItem(const System* sys, const ItemOrder& withdraw)
    {
        return CharacterOrder(sys, CharacterOrderType::WithdrawItem, {}, withdraw, "");
    }
    static CharacterOrder CreateDepositGold(const System* sys, int gold_amount)
    {
        return CharacterOrder(sys, CharacterOrderType::DepositGold, {}, { "", gold_amount }, "");
    }
    static CharacterOrder CreateWithdrawGold(const System* sys, int gold_amount)
    {
        return CharacterOrder(sys, CharacterOrderType::WithdrawGold, {}, { "", gold_amount }, "");
    }
    static CharacterOrder CreateBuyItem(const System* sys, const ItemOrder& buy)
    {
        return CharacterOrder(sys, CharacterOrderType::BuyItem, {}, buy, "");
    }
    static CharacterOrder CreateClearInventory(const System* sys, const char* keep)
    {
        return CharacterOrder(sys, CharacterOrderType::ClearInventory, {}, {}, keep);
    }
    const System* system;
    CharacterOrderType type;
    MapCoord coord;
    ItemOrder item_order;
    std::string slot;
};

enum class EquipementType
{
    Weapon,
    Helmet,
    Shield,
    BodyArmor,
    Boots,
    Ring1,
    Ring2,
    Amulet,
    Utility1,
    Utility2,
    Bag,
    LegArmor,
    Rune,
    Artifact1,
    Artifact2,
    Artifact3
};

struct InventoryWeapons
{
    std::string code;
    std::array<int, 4> attacks;
    std::array<int, 4> damages;
    int level;
};

struct InventoryArmorPart
{
    std::string code;
    std::array<int, 4> resistances;
    std::array<int, 4> damages;
    int hp;
    int level;
};

class Character
{
public:
    Character();

    void Set_Character(const char* character_name);
    const char* Get_Character(void) const;
    const CharacterOrder* Get_Current_Order(void) const;

    void Add_Move(const System* sys, const MapCoord& coords);
    void Add_Fight(const System* sys);
    void Add_Rest(const System* sys);
    void Add_Craft(const System* sys, const ItemOrder& craft);
    void Add_UseItem(const System* sys, const ItemOrder& use);
    void Add_Unequip_Item(const System* sys, const char* slot);
    void Add_Equip_Item(const System* sys, const char* slot, const char* item_code);
    void Add_Gathering(const System* sys);
    void Add_Recycle_Item(const System* sys, const ItemOrder& recycle);
    void Add_Task_New(const System* sys);
    void Add_Task_Trade(const System* sys, const ItemOrder& trade);
    void Add_Task_Complete(const System* sys);
    void Add_Deposit_Item(const System* sys, const ItemOrder& deposit);
    void Add_Withdraw_Item(const System* sys, const ItemOrder& withdraw);
    void Add_Deposit_Gold(const System* sys, int gold_amount);
    void Add_Withdraw_Gold(const System* sys, int gold_amount);
    void Add_Buy_Item(const System* sys, const ItemOrder& buy);
    void Make_Clear_Inventory(const System* sys, const char* keep);

    void Update(float elapsed_time);
    float Get_Remaining_Timeout(void) const;
    bool Is_Empty(void) const;

    int Get_Life_Current(void) const;
    int Get_Life_Max(void) const;
    std::array<int, 4> Get_Attack(void) const;
    std::array<int, 4> Get_Damage(void) const;
    std::array<int, 4> Get_Resistance(void) const;

    int Get_Item_Count(const char* object_code) const;
    std::string Get_Equiped_Weapon(void) const;
    std::string Get_Equiped_Helmet(void) const;
    std::string Get_Equiped_Body_Armor(void) const;
    std::string Get_Equiped_Leg_Armor(void) const;
    std::string Get_Equiped_Boots(void) const;
    std::string Get_Equiped_Shield(void) const;
    std::string Get_Equiped_Amulet(void) const;
    std::string Get_Equiped_Ring1(void) const;
    std::string Get_Equiped_Ring2(void) const;
    std::string Get_Equiped_Utility1(void) const;
    bool Is_Item_Equiped(const char* item_code) const;
    std::string Get_Equiped_Item(EquipementType type) const;
    std::string Get_Equiped_Item(const char* type) const;

    int Get_Inventory_Slot_Count(void) const;
    int Get_Inventory_Remaining_Slot_Count(void) const;
    int Get_Inventory_Remaining_Space(void) const;
    ItemOrder Get_Inventory_Item(int slot) const;
    void Get_Fight_Items(const ItemManager& item_manager, int level, std::vector<InventoryWeapons>& weapons,
                         std::vector<InventoryArmorPart>& helmets, std::vector<InventoryArmorPart>& body_armors,
                         std::vector<InventoryArmorPart>& leg_armors, std::vector<InventoryArmorPart>& boots,
                         std::vector<InventoryArmorPart>& shields, std::vector<InventoryArmorPart>& rings1,
                         std::vector<InventoryArmorPart>& rings2, std::vector<InventoryArmorPart>& amulets) const;
    bool Is_Inventory_Slot_Resource(const ItemManager& item_manager, int slot) const;
    bool Is_Inventory_Empty(void) const;

    int Get_Gold_Amount(void) const;

    int Get_Skill_Level(const char* skill_name) const;

    bool Is_Task_Item(void) const;
    bool Is_Task_Monster() const;
    int Get_Task_Remaining(void) const;
    std::string Get_Task(void) const;

    bool Should_Move(const MapCoord& target) const;
    MapCoord Get_Map_Coord(void) const;

private:
    std::vector<CharacterOrder> m_Orders = {};
    const char* m_Character_Name         = nullptr;
    float m_Remaining_Timeout            = 0.0f;
    std::size_t m_Current_Index          = 0;
    MapCoord m_Position;

    nlohmann::json m_Character_Cache;

    void Get_Inventory_Armor(const ItemManager& item_manager, int level, const char* armor_type,
                             std::vector<InventoryArmorPart>& armors) const;
};

#endif  // _CHARACTER_HPP
