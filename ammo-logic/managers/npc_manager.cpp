#include "npc_manager.hpp"

#include "net/client.hpp"

NPCManager NPCManager::singleton;

void NPCManager::Initialize()
{
    std::vector<nlohmann::json> data;

    Client::singleton.Get_NPC_Items(data);

    for (std::size_t ii = 0; ii < data.size(); ii++)
    {
        const std::string code       = data[ii]["code"];
        const std::string npc        = data[ii]["npc"];
        const TradeCurrency currency = data[ii]["currency"] == "gold" ? TradeCurrency::Gold : TradeCurrency::TaskCoin;

        if (data[ii]["buy_price"].is_null() == false)
        {
            m_Buying.emplace(code, NPCItemTrade { npc, currency, data[ii]["buy_price"].get<uint16_t>() });
        }
        if (data[ii]["sell_price"].is_null() == false)
        {
            m_Selling.emplace(code, NPCItemTrade { npc, currency, data[ii]["sell_price"].get<uint16_t>() });
        }
    }
}

const NPCItemTrade* NPCManager::Get_Buyer(const char* item_code) const
{
    auto it = m_Buying.find(item_code);
    if (it != m_Buying.end())
    {
        return &it->second;
    }
    return nullptr;
}

const NPCItemTrade* NPCManager::Get_Seller(const char* item_code) const
{
    auto it = m_Selling.find(item_code);
    if (it != m_Selling.end())
    {
        return &it->second;
    }
    return nullptr;
}

const ItemOrder* NPCManager::Get_Cost(const char* item_code) const
{
    return nullptr;
}

const MapCoord* NPCManager::Get_Coords(const char* npc) const
{
    return nullptr;
}
