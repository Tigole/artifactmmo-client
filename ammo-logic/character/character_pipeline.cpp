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

std::string CharacterPipeline::Get_Current_Order(void) const
{
    const CharacterOrder* order = m_Character.Get_Current_Order();
    std::string str             = "???";
    if (order != nullptr)
    {
        const ItemOrder& item    = order->item_order;
        const MapCoord map_coord = m_Character.Get_Map_Coord();
        const char* system_name  = order->system->Name();
        switch (order->type)
        {
        case CharacterOrderType::Move:        str = fmt::format("{} - Move - [{} {}]", system_name, order->coord.x, order->coord.y); break;
        case CharacterOrderType::Fight:       str = fmt::format("{} - Fight", system_name); break;
        case CharacterOrderType::Rest:        str = fmt::format("{} - Rest", system_name); break;
        case CharacterOrderType::Craft:       str = fmt::format("{} - Craft - {} x{}", system_name, item.code, item.quantity); break;
        case CharacterOrderType::UseItem:     str = fmt::format("{} - UseItem - {} x{}", system_name, item.code, item.quantity); break;
        case CharacterOrderType::UnequipItem: str = fmt::format("{} - UnequipItem - {}", system_name, order->slot); break;
        case CharacterOrderType::EquipItem:   str = fmt::format("{} - EquipItem - {} {}", system_name, order->slot, item.code); break;
        case CharacterOrderType::Gathering:
            str = fmt::format("{} - Gathering - {} - [{} {}]", system_name, ResourceManager::singleton.Get_Spot_Name(map_coord),
                              map_coord.x, map_coord.y);
            break;
        case CharacterOrderType::Recycling:    str = fmt::format("{} - Recycling - {} x{}", system_name, item.code, item.quantity); break;
        case CharacterOrderType::TaskNew:      str = fmt::format("{} - TaskNew", system_name); break;
        case CharacterOrderType::TaskTrade:    str = fmt::format("{} - TaskTrade - {} x{}", system_name, item.code, item.quantity); break;
        case CharacterOrderType::TaskComplete: str = fmt::format("{} - TaskComplete", system_name); break;
        case CharacterOrderType::DepositItem:  str = fmt::format("{} - DepositItem - {} x{}", system_name, item.code, item.quantity); break;
        case CharacterOrderType::WithdrawItem:
            str = fmt::format("{} - WithdrawItem - {} x{}", system_name, item.code, item.quantity);
            break;
        case CharacterOrderType::DepositGold:    str = fmt::format("{} - DepositGold - {}", system_name, item.quantity); break;
        case CharacterOrderType::WithdrawGold:   str = fmt::format("{} - WithdrawGold - {}", system_name, item.quantity); break;
        case CharacterOrderType::BuyItem:        str = fmt::format("{} - BuyItem - {} x{}", system_name, item.code, item.quantity); break;
        case CharacterOrderType::ClearInventory: str = fmt::format("Clear inventory"); break;
        }
    }
    return str;
}

float CharacterPipeline::Get_Remaining_Timeout(void) const
{
    return m_Character.Get_Remaining_Timeout();
}
