#ifndef _CHARACTER_HPP
#define _CHARACTER_HPP 1

#include <array>
#include <vector>

#include "types.hpp"

class Client;
class ItemManager;
class InventoryManager;

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
};

struct CharacterOrder
{
    static CharacterOrder CreateMove(const MapCoord& coord)
    {
        return { CharacterOrderType::Move, coord, ItemOrder {}, "" };
    }
    static CharacterOrder CreateFight(void)
    {
        return { CharacterOrderType::Fight, MapCoord {}, ItemOrder {}, "" };
    }
    static CharacterOrder CreateRest(void)
    {
        return { CharacterOrderType::Rest, MapCoord {}, ItemOrder {}, "" };
    }
    static CharacterOrder CreateCraft(const ItemOrder& craft)
    {
        return { CharacterOrderType::Craft, MapCoord {}, craft, "" };
    }
    static CharacterOrder CreateUseItem(const ItemOrder& item)
    {
        return { CharacterOrderType::UseItem, MapCoord {}, item, "" };
    }
    static CharacterOrder CreateUnequipItem(const char* slot)
    {
        return { CharacterOrderType::UnequipItem, MapCoord {}, ItemOrder {}, slot };
    }
    static CharacterOrder CreateEquipItem(const char* slot, const char* item_code)
    {
        return {
            CharacterOrderType::EquipItem, MapCoord {},
              ItemOrder { item_code, 1 },
              slot
        };
    }
    static CharacterOrder CreateGathering(void)
    {
        return CharacterOrder(CharacterOrderType::Gathering, {}, {}, "");
    }
    static CharacterOrder CreateRecycling(const ItemOrder& recycle)
    {
        return CharacterOrder(CharacterOrderType::Recycling, {}, recycle, "");
    }
    static CharacterOrder CreateTaskNew(void)
    {
        return CharacterOrder(CharacterOrderType::TaskNew, {}, {}, "");
    }
    static CharacterOrder CreateTaskTrade(const ItemOrder& trade)
    {
        return CharacterOrder(CharacterOrderType::TaskTrade, {}, trade, "");
    }
    static CharacterOrder CreateTaskComplete(void)
    {
        return CharacterOrder(CharacterOrderType::TaskComplete, {}, {}, "");
    }
    static CharacterOrder CreateDepositItem(const ItemOrder& deposit)
    {
        return CharacterOrder(CharacterOrderType::DepositItem, {}, deposit, "");
    }
    static CharacterOrder CreateWithdrawItem(const ItemOrder& withdraw)
    {
        return CharacterOrder(CharacterOrderType::WithdrawItem, {}, withdraw, "");
    }
    static CharacterOrder CreateDepositGold(int gold_amount)
    {
        return CharacterOrder(CharacterOrderType::DepositGold, {}, { "", gold_amount }, "");
    }
    static CharacterOrder CreateWithdrawGold(int gold_amount)
    {
        return CharacterOrder(CharacterOrderType::WithdrawGold, {}, { "", gold_amount }, "");
    }
    static CharacterOrder CreateBuyItem(const ItemOrder& buy)
    {
        return CharacterOrder(CharacterOrderType::BuyItem, {}, buy, "");
    }
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
    Character(Client& c, InventoryManager& bank);

    void Set_Character(const char* character_name);
    const char* Get_Character(void) const;

    void Add_Move(const MapCoord& coords);
    void Add_Fight(void);
    void Add_Rest(void);
    void Add_Craft(const ItemOrder& craft);
    void Add_UseItem(const ItemOrder& use);
    void Add_Unequip_Item(const char* slot);
    void Add_Equip_Item(const char* slot, const char* item_code);
    void Add_Gathering(void);
    void Add_Recycle_Item(const ItemOrder& recycle);
    void Add_Task_New(void);
    void Add_Task_Trade(const ItemOrder& trade);
    void Add_Task_Complete(void);
    void Add_Deposit_Item(const ItemOrder& deposit);
    void Add_Withdraw_Item(const ItemOrder& withdraw);
    void Add_Deposit_Gold(int gold_amount);
    void Add_Withdraw_Gold(int gold_amount);
    void Add_Buy_Item(const ItemOrder& buy);

    void Update(float elapsed_time);
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

    int Get_Gold_Amount(void) const;

    int Get_Skill_Level(const char* skill_name) const;

    bool Is_Task_Item(void) const;
    bool Is_Task_Monster() const;
    int Get_Task_Remaining(void) const;
    std::string Get_Task(void) const;

    bool Should_Move(const MapCoord& target) const;
    int Get_Distance(const MapCoord& target) const;

private:
    std::vector<CharacterOrder> m_Orders = {};
    const char* m_Character_Name         = nullptr;
    Client& m_Client;
    InventoryManager& m_Bank;
    float m_Remaining_Timeout   = 0.0f;
    std::size_t m_Current_Index = 0;
    MapCoord m_Position;

    nlohmann::json m_Character_Cache;

    void Get_Inventory_Armor(const ItemManager& item_manager, int level, const char* armor_type,
                             std::vector<InventoryArmorPart>& armors) const;
};

#endif  // _CHARACTER_HPP
