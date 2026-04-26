#include "character.hpp"

#include <cstdio>
#include <cstring>

#include "keywords.hpp"
#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"
#include "net/client.hpp"
#include "systems/system.hpp"

Character::Character() {}

void Character::Set_Character(const char* character_name)
{
    m_Character_Name = character_name;
    Client::singleton.mt_Get_Character_Cache(m_Character_Name, m_Character_Cache);
    if (false)
    {
        std::cout << "Set_Character: " << m_Character_Cache.dump(4) << '\n';
    }
    m_Remaining_Timeout = m_Character_Cache["cooldown"].get<int>();
    m_Position.x        = m_Character_Cache["x"].get<int>();
    m_Position.y        = m_Character_Cache["y"].get<int>();
    printf("'%s' init cooldown: %d\n", m_Character_Name, (int)m_Remaining_Timeout);
}

const char* Character::Get_Character(void) const
{
    return m_Character_Name;
}

const CharacterOrder* Character::Get_Current_Order(void) const
{
    if (m_Orders.size())
    {
        if (m_Current_Index > 0)
        {
            return &m_Orders[m_Current_Index - 1];
        }
        return &m_Orders[0];
    }
    return nullptr;
}

void Character::Add_Move(const System* sys, const MapCoord& coords)
{
    m_Orders.push_back(CharacterOrder::CreateMove(sys, coords));
}

void Character::Add_Fight(const System* sys)
{
    m_Orders.push_back(CharacterOrder::CreateFight(sys));
}

void Character::Add_Rest(const System* sys)
{
    m_Orders.push_back(CharacterOrder::CreateRest(sys));
}

void Character::Add_Craft(const System* sys, const ItemOrder& craft)
{
    m_Orders.push_back(CharacterOrder::CreateCraft(sys, craft));
}

void Character::Add_UseItem(const System* sys, const ItemOrder& use)
{
    m_Orders.push_back(CharacterOrder::CreateUseItem(sys, use));
}

void Character::Add_Unequip_Item(const System* sys, const char* slot, int item_quantity)
{
    m_Orders.push_back(CharacterOrder::CreateUnequipItem(sys, slot, item_quantity));
}

void Character::Add_Equip_Item(const System* sys, const char* slot, const char* item_code, int item_quantity)
{
    m_Orders.push_back(CharacterOrder::CreateEquipItem(sys, slot, item_code, item_quantity));
}

void Character::Add_Gathering(const System* sys)
{
    m_Orders.push_back(CharacterOrder::CreateGathering(sys));
}

void Character::Add_Recycle_Item(const System* sys, const ItemOrder& recycle)
{
    m_Orders.push_back(CharacterOrder::CreateRecycling(sys, recycle));
}

void Character::Add_Task_New(const System* sys)
{
    m_Orders.push_back(CharacterOrder::CreateTaskNew(sys));
}

void Character::Add_Task_Trade(const System* sys, const ItemOrder& trade)
{
    m_Orders.push_back(CharacterOrder::CreateTaskTrade(sys, trade));
}

void Character::Add_Task_Complete(const System* sys)
{
    m_Orders.push_back(CharacterOrder::CreateTaskComplete(sys));
}

void Character::Add_Deposit_Item(const System* sys, const ItemOrder& deposit)
{
    m_Orders.push_back(CharacterOrder::CreateDepositItem(sys, deposit));
}

void Character::Add_Withdraw_Item(const System* sys, const ItemOrder& withdraw)
{
    m_Orders.push_back(CharacterOrder::CreateWithdrawItem(sys, withdraw));
}

void Character::Add_Deposit_Gold(const System* sys, int gold_amount)
{
    m_Orders.push_back(CharacterOrder::CreateDepositGold(sys, gold_amount));
}

void Character::Add_Withdraw_Gold(const System* sys, int gold_amount)
{
    m_Orders.push_back(CharacterOrder::CreateWithdrawGold(sys, gold_amount));
}

void Character::Add_Buy_Item(const System* sys, const ItemOrder& buy)
{
    m_Orders.push_back(CharacterOrder::CreateBuyItem(sys, buy));
}

void Character::Add_Buy_Bank_Expasion(const System* sys)
{
    m_Orders.push_back(CharacterOrder::CreateBuyBankExpansion(sys));
}

void Character::Make_Clear_Inventory(const System* sys, const char* keep)
{
    m_Orders.push_back(CharacterOrder::CreateClearInventory(sys, keep == nullptr ? "" : keep));
}

void Character::Update(float elapsed_time)
{
    m_Remaining_Timeout -= elapsed_time;
    if (m_Remaining_Timeout < 0.0f)
    {
        if (m_Current_Index < m_Orders.size())
        {
            const CharacterOrder l_Order = m_Orders[m_Current_Index];
            try
            {
                printf("'%s' order type %d from system '%s'\n", m_Character_Name, static_cast<int>(l_Order.type), l_Order.system->Name());
                switch (l_Order.type)
                {
                case CharacterOrderType::Move:
                    if (Should_Move(l_Order.coord) == true)
                    {
                        m_Remaining_Timeout = Client::singleton.mt_Character_Move(m_Character_Name, l_Order.coord, m_Character_Cache);
                    }
                    break;
                case CharacterOrderType::Fight:
                    m_Remaining_Timeout = Client::singleton.mt_Character_Fight(m_Character_Name, m_Character_Cache);
                    // printf("raw: '%s'\n", m_Character_Cache.dump().c_str());
                    m_Character_Cache = m_Character_Cache[0];
                    // printf("filtered: '%s'\n", m_Character_Cache.dump().c_str());
                    break;
                case CharacterOrderType::Rest:
                    m_Remaining_Timeout = Client::singleton.mt_Character_Rest(m_Character_Name, m_Character_Cache);
                    break;
                case CharacterOrderType::Craft:
                    m_Remaining_Timeout = Client::singleton.mt_Character_Craft(m_Character_Name, l_Order.item_order, m_Character_Cache);
                    break;
                case CharacterOrderType::UseItem:
                    m_Remaining_Timeout = Client::singleton.mt_Character_Use_Item(m_Character_Name, l_Order.item_order, m_Character_Cache);
                    break;
                case CharacterOrderType::UnequipItem:
                    m_Remaining_Timeout = Client::singleton.mt_Character_Unequip_Item(m_Character_Name, l_Order.slot.c_str(),
                                                                                      l_Order.item_order.quantity, m_Character_Cache);
                    break;
                case CharacterOrderType::EquipItem:
                    m_Remaining_Timeout =
                        Client::singleton.mt_Character_Equip_Item(m_Character_Name, l_Order.slot.c_str(), l_Order.item_order.code.c_str(),
                                                                  l_Order.item_order.quantity, m_Character_Cache);
                    break;
                case CharacterOrderType::Gathering:
                    m_Remaining_Timeout = Client::singleton.mt_Character_Gather(m_Character_Name, m_Character_Cache);
                    break;
                case CharacterOrderType::Recycling:
                    m_Remaining_Timeout = Client::singleton.mt_Character_Recycle(m_Character_Name, l_Order.item_order, m_Character_Cache);
                    break;
                case CharacterOrderType::TaskNew:
                    m_Remaining_Timeout = Client::singleton.mt_Character_Task_New(m_Character_Name, m_Character_Cache);
                    break;
                case CharacterOrderType::TaskTrade:
                    m_Remaining_Timeout =
                        Client::singleton.mt_Character_Task_Trade(m_Character_Name, l_Order.item_order, m_Character_Cache);
                    break;
                case CharacterOrderType::TaskComplete:
                    m_Remaining_Timeout = Client::singleton.mt_Character_Task_Complete(m_Character_Name, m_Character_Cache);
                    break;
                case CharacterOrderType::DepositItem:
                    if (Get_Item_Count(l_Order.item_order.code.c_str()) < l_Order.item_order.quantity)
                    {
                        printf("{%s} asked deposit '%s' x%d whereas %d in inventory\n", Get_Character(), l_Order.item_order.code.c_str(),
                               l_Order.item_order.quantity, Get_Item_Count(l_Order.item_order.code.c_str()));
                    }
                    else
                    {
                        m_Remaining_Timeout =
                            Client::singleton.mt_Character_Deposit_Item(m_Character_Name, l_Order.item_order, m_Character_Cache);
                        InventoryManager::singleton.Update_Cache();
                    }
                    break;
                case CharacterOrderType::WithdrawItem:
                    m_Remaining_Timeout =
                        Client::singleton.mt_Character_Withdraw_Item(m_Character_Name, l_Order.item_order, m_Character_Cache);
                    InventoryManager::singleton.Update_Cache();
                    break;
                case CharacterOrderType::DepositGold:
                    m_Remaining_Timeout =
                        Client::singleton.mt_Character_Deposit_Gold(m_Character_Name, l_Order.item_order.quantity, m_Character_Cache);
                    InventoryManager::singleton.Update_Cache();
                    break;
                case CharacterOrderType::WithdrawGold:
                    m_Remaining_Timeout =
                        Client::singleton.mt_Character_Withdraw_Gold(m_Character_Name, l_Order.item_order.quantity, m_Character_Cache);
                    InventoryManager::singleton.Update_Cache();
                    break;
                case CharacterOrderType::BuyItem:
                    m_Remaining_Timeout = Client::singleton.mt_Character_Buy_Item(m_Character_Name, l_Order.item_order, m_Character_Cache);
                    break;
                case CharacterOrderType::BuyBankExpansion:
                    m_Remaining_Timeout = Client::singleton.mt_Character_Buy_Bank_Expansion(m_Character_Name, m_Character_Cache);
                    break;
                case CharacterOrderType::ClearInventory:
                    {
                        const MapCoord bank_coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(Get_Map_Coord());
                        if (Should_Move(bank_coord))
                        {
                            Add_Move(l_Order.system, bank_coord);
                        }

                        {
                            const int slot_count = Get_Inventory_Slot_Count();
                            for (int ii = 0; ii < slot_count; ii++)
                            {
                                const ItemOrder item = Get_Inventory_Item(ii);

                                if ((item.quantity != 0) && (item.code != l_Order.slot))
                                {
                                    Add_Deposit_Item(l_Order.system, item);
                                }
                            }

                            if (Get_Gold_Amount() > 0)
                            {
                                Add_Deposit_Gold(l_Order.system, Get_Gold_Amount());
                            }
                        }
                    }
                    break;
                default: break;
                }
                m_Current_Index++;
                m_Remaining_Timeout += 0.5f;  /// Fix me 499
                printf("'%s' cooldown %d (%d [%d %d] ['%s' %d] '%s')\n", m_Character_Name, (int)m_Remaining_Timeout, l_Order.type,
                       l_Order.coord.x, l_Order.coord.y, l_Order.item_order.code.c_str(), l_Order.item_order.quantity,
                       l_Order.slot.c_str());
            }
            catch (const std::exception& e)
            {
                printf("exception: '%s' (%d [%d %d] ['%s' %d] '%s')\n", m_Character_Name, l_Order.type, l_Order.coord.x, l_Order.coord.y,
                       l_Order.item_order.code.c_str(), l_Order.item_order.quantity, l_Order.slot.c_str());
                printf("%s\n", e.what());
                throw e;
            }

            m_Position.x = m_Character_Cache["x"].get<int>();
            m_Position.y = m_Character_Cache["y"].get<int>();
        }
        else
        {
            m_Current_Index = 0;
            m_Orders.clear();
        }
    }
}

float Character::Get_Remaining_Timeout(void) const
{
    return m_Remaining_Timeout;
}

bool Character::Is_Empty(void) const
{
    return m_Orders.empty() && (m_Remaining_Timeout < 0.0f);
}

int Character::Get_Life_Current(void) const
{
    return m_Character_Cache["hp"].get<int>();
}

int Character::Get_Life_Max(void) const
{
    return m_Character_Cache["max_hp"].get<int>();
}

std::array<int, 4> Character::Get_Attack(void) const
{
    return {
        { m_Character_Cache["attack_fire"].get<int>(), m_Character_Cache["attack_water"].get<int>(),
         m_Character_Cache["attack_earth"].get<int>(), m_Character_Cache["attack_air"].get<int>() }
    };
}

std::array<int, 4> Character::Get_Damage(void) const
{
    const int dmg = m_Character_Cache["dmg"].get<int>();
    return {
        { m_Character_Cache["dmg_fire"].get<int>() + dmg, m_Character_Cache["dmg_water"].get<int>() + dmg,
         m_Character_Cache["dmg_earth"].get<int>() + dmg, m_Character_Cache["dmg_air"].get<int>() + dmg }
    };
}

std::array<int, 4> Character::Get_Resistance(void) const
{
    return {
        { m_Character_Cache["res_fire"].get<int>(), m_Character_Cache["res_water"].get<int>(), m_Character_Cache["res_earth"].get<int>(),
         m_Character_Cache["res_air"].get<int>() }
    };
}

int Character::Get_Item_Count(const char* object_code) const
{
    for (auto it = m_Character_Cache["inventory"].begin(); it != m_Character_Cache["inventory"].end(); it++)
    {
        if ((*it)["code"].get<std::string>() == object_code)
        {
            return (*it)["quantity"].get<int>();
        }
    }
    return 0;
}

std::string Character::Get_Equiped_Weapon(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::weapon_slot];
}

std::string Character::Get_Equiped_Helmet(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::helmet_slot];
}

std::string Character::Get_Equiped_Body_Armor(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::body_armor_slot];
}

std::string Character::Get_Equiped_Leg_Armor(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::leg_armor_slot];
}

std::string Character::Get_Equiped_Boots(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::boots_slot];
}

std::string Character::Get_Equiped_Shield(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::shield_slot];
}

std::string Character::Get_Equiped_Amulet(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::amulet_slot];
}

std::string Character::Get_Equiped_Ring1(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::ring1_slot];
}

std::string Character::Get_Equiped_Ring2(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::ring2_slot];
}

std::string Character::Get_Equiped_Utility1(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::utility1_slot];
}

int Character::Get_Equiped_Utility1_Quantity(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::utility1_slot_quantity];
}

std::string Character::Get_Equiped_Artifact1(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::artifact1_slot];
}

std::string Character::Get_Equiped_Artifact2(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::artifact2_slot];
}

std::string Character::Get_Equiped_Artifact3(void) const
{
    return m_Character_Cache[Keywords::EquipementSlot::artifact3_slot];
}

bool Character::Is_Item_Equiped(const char* item_code) const
{
    constexpr const std::array<const char*, 10> l_Slots = {
        { Keywords::EquipementSlot::weapon_slot, Keywords::EquipementSlot::rune_slot, Keywords::EquipementSlot::shield_slot,
         Keywords::EquipementSlot::helmet_slot, Keywords::EquipementSlot::body_armor_slot, Keywords::EquipementSlot::leg_armor_slot,
         Keywords::EquipementSlot::boots_slot, Keywords::EquipementSlot::ring1_slot, Keywords::EquipementSlot::ring2_slot,
         Keywords::EquipementSlot::amulet_slot }
        /// Some are missing
    };
    for (std::size_t ii = 0; ii < l_Slots.size(); ii++)
    {
        if (m_Character_Cache[l_Slots[ii]] == item_code)
        {
            return true;
        }
    }
    return false;
}

std::string Character::Get_Equiped_Item(EquipementType type) const
{
    switch (type)
    {
    case EquipementType::Weapon:   return Get_Equiped_Weapon();
    case EquipementType::Helmet:   return Get_Equiped_Helmet();
    case EquipementType::Boots:    return Get_Equiped_Boots();
    case EquipementType::Shield:   return Get_Equiped_Shield();
    case EquipementType::Ring1:    return Get_Equiped_Ring1();
    case EquipementType::Ring2:    return Get_Equiped_Ring2();
    case EquipementType::Utility1: return Get_Equiped_Utility1();
    }
    return "";
}

std::string Character::Get_Equiped_Item(const char* type) const
{
    std::string slot = fmt::format("{}_slot", type);
    return m_Character_Cache[slot];
}

int Character::Get_Inventory_Slot_Count(void) const
{
    return m_Character_Cache["inventory"].size();
}

int Character::Get_Inventory_Remaining_Slot_Count(void) const
{
    int l_Empty_Slot_Count = 0;
    for (int ii = 0; ii < Get_Inventory_Slot_Count(); ii++)
    {
        l_Empty_Slot_Count += Get_Inventory_Item(ii).quantity == 0;
    }
    return l_Empty_Slot_Count;
}

int Character::Get_Inventory_Remaining_Space(void) const
{
    int l_Remaining_Space = m_Character_Cache["inventory_max_items"].get<int>();
    for (int ii = 0; ii < Get_Inventory_Slot_Count(); ii++)
    {
        l_Remaining_Space -= Get_Inventory_Item(ii).quantity;
    }
    return l_Remaining_Space;
}

ItemOrder Character::Get_Inventory_Item(int slot) const
{
    if (slot < Get_Inventory_Slot_Count())
    {
        return ItemOrder { m_Character_Cache["inventory"][slot]["code"].get<std::string>(),
                           m_Character_Cache["inventory"][slot]["quantity"].get<int>() };
    }
    return ItemOrder { "", 0 };
}

void Character::Get_Fight_Items(const ItemManager& item_manager, int level, std::vector<InventoryWeapons>& weapons,
                                std::vector<InventoryArmorPart>& helmets, std::vector<InventoryArmorPart>& body_armors,
                                std::vector<InventoryArmorPart>& leg_armors, std::vector<InventoryArmorPart>& boots,
                                std::vector<InventoryArmorPart>& shields, std::vector<InventoryArmorPart>& rings,
                                std::vector<InventoryArmorPart>& amulets) const
{
    const auto& inventory = m_Character_Cache["inventory"];

    for (auto slot = inventory.begin(); slot != inventory.end(); slot++)
    {
        std::string code = (*slot)["code"];
        if ((item_manager.Is_Weapon(code.c_str()) == true) && (item_manager.Get_Item_Level(code.c_str()) <= level))
        {
            weapons.emplace_back(code, item_manager.Get_Weapon_Attack(code.c_str()),
                                 std::array<int, 4> {
                                     { 0, 0, 0, 0 }
            },
                                 item_manager.Get_Item_Level(code.c_str()));
        }
    }

    Get_Inventory_Armor(item_manager, level, "helmet", helmets);
    Get_Inventory_Armor(item_manager, level, "body_armor", body_armors);
    Get_Inventory_Armor(item_manager, level, "leg_armor", leg_armors);
    Get_Inventory_Armor(item_manager, level, "shield", shields);
    Get_Inventory_Armor(item_manager, level, "ring", rings);
    Get_Inventory_Armor(item_manager, level, "amulet", amulets);
}

void Character::Get_Inventory_Armor(const ItemManager& item_manager, int level, const char* armor_type,
                                    std::vector<InventoryArmorPart>& armors) const
{
    const auto& inventory = m_Character_Cache["inventory"];

    for (auto i: inventory)
    {
        const std::string code = i["code"];
        if ((item_manager.Is_Type(code.c_str(), armor_type) == true) && (item_manager.Get_Item_Level(code.c_str()) <= level))
        {
            armors.emplace_back(code, item_manager.Get_Armor_Resistance(code.c_str()), item_manager.Get_Armor_Damage(code.c_str()),
                                item_manager.Get_Armor_Hp(code.c_str()), item_manager.Get_Item_Level(code.c_str()));
        }
    }
}

bool Character::Is_Inventory_Slot_Resource(const ItemManager& item_manager, int slot) const
{
    return item_manager.Is_Type(m_Character_Cache["inventory"][slot]["code"].get<std::string>().c_str(), "resource");
}

bool Character::Is_Inventory_Empty(void) const
{
    return Get_Inventory_Remaining_Slot_Count() == Get_Inventory_Slot_Count();
}

int Character::Get_Gold_Amount(void) const
{
    return m_Character_Cache["gold"].get<int>();
}

int Character::Get_Skill_Level(const char* skill_name) const
{
    if (strcmp(skill_name, Keywords::Skills::mining) == 0)
    {
        return m_Character_Cache["mining_level"].get<int>();
    }
    if (strcmp(skill_name, Keywords::Skills::woodcutting) == 0)
    {
        return m_Character_Cache["woodcutting_level"].get<int>();
    }
    if (strcmp(skill_name, Keywords::Skills::fishing) == 0)
    {
        return m_Character_Cache["fishing_level"].get<int>();
    }
    if (strcmp(skill_name, Keywords::Skills::alchemy) == 0)
    {
        return m_Character_Cache["alchemy_level"].get<int>();
    }
    if (strcmp(skill_name, Keywords::Skills::weaponcrafting) == 0)
    {
        return m_Character_Cache["weaponcrafting_level"].get<int>();
    }
    if (strcmp(skill_name, Keywords::Skills::gearcrafting) == 0)
    {
        return m_Character_Cache["gearcrafting_level"].get<int>();
    }
    if (strcmp(skill_name, Keywords::Skills::jewelrycrafting) == 0)
    {
        return m_Character_Cache["jewelrycrafting_level"].get<int>();
    }
    if (strcmp(skill_name, Keywords::Skills::cooking) == 0)
    {
        return m_Character_Cache["cooking_level"].get<int>();
    }
    if (strcmp(skill_name, Keywords::Skills::combat) == 0)
    {
        return m_Character_Cache["level"].get<int>();
    }
    return 0;
}

bool Character::Is_Task_Item(void) const
{
    return m_Character_Cache["task_type"] == "items";
}

bool Character::Is_Task_Monster() const
{
    return m_Character_Cache["task_type"] == "monsters";
}

int Character::Get_Task_Remaining(void) const
{
    return m_Character_Cache["task_total"].get<int>() - m_Character_Cache["task_progress"].get<int>();
}

std::string Character::Get_Task(void) const
{
    return m_Character_Cache["task"];
}

bool Character::Should_Move(const MapCoord& target) const
{
    return (m_Position.x != target.x) || (m_Position.y != target.y);
}

MapCoord Character::Get_Map_Coord(void) const
{
    return m_Position;
}
