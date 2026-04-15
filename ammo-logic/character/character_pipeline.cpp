#include "character_pipeline.hpp"

#include "managers/resource_manager.hpp"
#include "systems/system.hpp"

CharacterPipeline::CharacterPipeline() : m_Character(), m_Systems() {}

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
    m_Character.Update(elapsed_time);
    for (std::size_t jj = 0; jj < m_Systems.size() && (m_Character.Is_Empty() == true); jj++)
    {
        m_Systems[jj]->Fill_Pipeline(m_Character);
        if (m_Character.Is_Empty() == false)
        {
            printf("\t'%s' commanded by '%s'\n", m_Character.Get_Character(), m_Systems[jj]->Name());
        }
    }
}

std::string CharacterPipeline::Get_Current_Order(void) const
{
    const CharacterOrder* order = m_Character.Get_Current_Order();
    std::string str             = "???";
    if (order != nullptr)
    {
        const ItemOrder& item    = order->item_order;
        const MapCoord map_coord = m_Character.Get_Map_Coord();
        switch (order->type)
        {
        case CharacterOrderType::Move:        str = fmt::format("{} - Move - [{} {}]", order->system, order->coord.x, order->coord.y); break;
        case CharacterOrderType::Fight:       str = fmt::format("{} - Fight - {}", order->system, "???"); break;
        case CharacterOrderType::Rest:        str = fmt::format("{} - Rest", order->system); break;
        case CharacterOrderType::Craft:       str = fmt::format("{} - Craft - {} x{}", order->system, item.code, item.quantity); break;
        case CharacterOrderType::UseItem:     str = fmt::format("{} - UseItem - {} x{}", order->system, item.code, item.quantity); break;
        case CharacterOrderType::UnequipItem: str = fmt::format("{} - UnequipItem - {}", order->system, order->slot); break;
        case CharacterOrderType::EquipItem:   str = fmt::format("{} - EquipItem - {} {}", order->system, order->slot, item.code); break;
        case CharacterOrderType::Gathering:
            str = fmt::format("{} - Gathering - {} - [{} {}]", order->system, ResourceManager::singleton.Get_Spot_Name(map_coord),
                              map_coord.x, map_coord.y);
            break;
        case CharacterOrderType::Recycling:    str = fmt::format("{} - Recycling - {} x{}", order->system, item.code, item.quantity); break;
        case CharacterOrderType::TaskNew:      str = fmt::format("{} - TaskNew - {}", order->system, "???"); break;
        case CharacterOrderType::TaskTrade:    str = fmt::format("{} - TaskTrade - {}", order->system, "???"); break;
        case CharacterOrderType::TaskComplete: str = fmt::format("{} - TaskComplete - {}", order->system, "???"); break;
        case CharacterOrderType::DepositItem:
            str = fmt::format("{} - DepositItem - {} x{}", order->system, item.code, item.quantity);
            break;
        case CharacterOrderType::WithdrawItem:
            str = fmt::format("{} - WithdrawItem - {} x{}", order->system, item.code, item.quantity);
            break;
        case CharacterOrderType::DepositGold:  str = fmt::format("{} - DepositGold - {}", order->system, "???"); break;
        case CharacterOrderType::WithdrawGold: str = fmt::format("{} - WithdrawGold - {}", order->system, "???"); break;
        case CharacterOrderType::BuyItem:      str = fmt::format("{} - BuyItem - {}", order->system, "???"); break;
        }
    }
    return str;
}

float CharacterPipeline::Get_Remaining_Timeout(void) const
{
    return m_Character.Get_Remaining_Timeout();
}
