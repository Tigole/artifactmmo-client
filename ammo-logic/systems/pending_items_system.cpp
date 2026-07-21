#include "pending_items_system.hpp"

#include "net/client.hpp"

PendingItemsSystem::PendingItemsSystem() : System("PendingItemsSystem"), m_Pending_Items() {}

void PendingItemsSystem::Fill_Pipeline(Character& character)
{
    for (const auto& i: m_Pending_Items)
    {
        character.Add_Claim_Pending_Item(this, i.c_str());
    }
    m_Pending_Items.clear();
}

void PendingItemsSystem::OnAchievementChanged(void)
{
    if (m_Pending_Items.size() > 0)
    {
        Client::singleton.Get_Pending_Items(m_Pending_Items);
    }
}

PendingItemsSystem PendingItemsSystem::singleton;
