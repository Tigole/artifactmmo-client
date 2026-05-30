#include "character_pipeline.hpp"

#include "managers/resource_manager.hpp"
#include "systems/system.hpp"

CharacterPipeline::CharacterPipeline() : m_Character(), m_Systems(), m_Current_Order("???") {}

void CharacterPipeline::Set_Character(const char* character_name)
{
    m_Character.Set_Character(character_name);
}

const char* CharacterPipeline::Get_Character(void) const
{
    return m_Character.Get_Character();
}

void CharacterPipeline::Add_System(System* system)
{
    m_Systems.push_back(system);
}

void CharacterPipeline::Update(float elapsed_time)
{
    for (std::size_t jj = 0; jj < m_Systems.size() && (m_Character.Is_Empty() == true); jj++)
    {
        m_Systems[jj]->Fill_Pipeline(m_Character);
        if (m_Character.Is_Empty() == false)
        {
            printf("\t'%s' commanded by '%s'\n", m_Character.Get_Character(), m_Systems[jj]->Name());
        }
    }
    m_Character.Update(elapsed_time);
}

const std::string& CharacterPipeline::Get_Current_Order(void) const
{
    const CharacterOrder* order = m_Character.Get_Current_Order();
    if (order != nullptr)
    {
        const ItemOrder& item          = order->item_order;
        const MapCoord map_coord       = m_Character.Get_Map_Coord();
        const char* system_name        = order->system->Name();
        const std::string& globalOrder = m_Character.Get_Global_Order();
        switch (order->type)
        {
        case CharacterOrderType::Move:
            m_Current_Order = fmt::format("{} - {} - Move - [{} {}]", system_name, globalOrder, order->coord.x, order->coord.y);
            break;
        case CharacterOrderType::Fight: m_Current_Order = fmt::format("{} - {} - Fight", system_name, globalOrder); break;
        case CharacterOrderType::Rest:  m_Current_Order = fmt::format("{} - {} - Rest", system_name, globalOrder); break;
        case CharacterOrderType::Craft:
            m_Current_Order = fmt::format("{} - {} - Craft - {} x{}", system_name, globalOrder, item.code, item.quantity);
            break;
        case CharacterOrderType::UseItem:
            m_Current_Order = fmt::format("{} - {} - UseItem - {} x{}", system_name, globalOrder, item.code, item.quantity);
            break;
        case CharacterOrderType::UnequipItem:
            m_Current_Order = fmt::format("{} - {} - UnequipItem - {}", system_name, globalOrder, order->slot);
            break;
        case CharacterOrderType::EquipItem:
            m_Current_Order = fmt::format("{} - {} - EquipItem - {} {}", system_name, globalOrder, order->slot, item.code);
            break;
        case CharacterOrderType::Gathering:
            m_Current_Order = fmt::format("{} - Gathering - {} - {} - [{} {}]", system_name, globalOrder,
                                          ResourceManager::singleton.Get_Spot_Name(map_coord), map_coord.x, map_coord.y);
            break;
        case CharacterOrderType::Recycling:
            m_Current_Order = fmt::format("{} - {} - Recycling - {} x{}", system_name, globalOrder, item.code, item.quantity);
            break;
        case CharacterOrderType::TaskNew: m_Current_Order = fmt::format("{} - {} - TaskNew", system_name, globalOrder); break;
        case CharacterOrderType::TaskTrade:
            m_Current_Order = fmt::format("{} - {} - TaskTrade - {} x{}", system_name, globalOrder, item.code, item.quantity);
            break;
        case CharacterOrderType::TaskComplete: m_Current_Order = fmt::format("{} - {} - TaskComplete", system_name, globalOrder); break;
        case CharacterOrderType::DepositItem:
            m_Current_Order = fmt::format("{} - {} - DepositItem - {} x{}", system_name, globalOrder, item.code, item.quantity);
            break;
        case CharacterOrderType::WithdrawItem:
            m_Current_Order = fmt::format("{} - {} - WithdrawItem - {} x{}", system_name, globalOrder, item.code, item.quantity);
            break;
        case CharacterOrderType::DepositGold:
            m_Current_Order = fmt::format("{} - {} - DepositGold - {}", system_name, globalOrder, item.quantity);
            break;
        case CharacterOrderType::WithdrawGold:
            m_Current_Order = fmt::format("{} - {} - WithdrawGold - {}", system_name, globalOrder, item.quantity);
            break;
        case CharacterOrderType::BuyItem:
            m_Current_Order = fmt::format("{} - {} - BuyItem - {} x{}", system_name, globalOrder, item.code, item.quantity);
            break;
        case CharacterOrderType::ClearInventory: m_Current_Order = fmt::format("{} - Clear inventory", globalOrder); break;
        }
    }
    return m_Current_Order;
}

float CharacterPipeline::Get_Remaining_Timeout(void) const
{
    return m_Character.Get_Remaining_Timeout();
}

const Character& CharacterPipeline::Get_Character_Obj(void) const
{
    return m_Character;
}
