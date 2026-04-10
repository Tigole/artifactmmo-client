#ifndef _NPC_MANAGER_HPP
#define _NPC_MANAGER_HPP 1

#include "types.hpp"

class Client;

enum class TradeCurrency : uint16_t
{
    Gold,
    TaskCoin
};

struct NPCItemTrade
{
    std::string npc;
    TradeCurrency currency;
    uint16_t amount;
};

class NPCManager
{
public:
    void Initialize(Client& client);

    const NPCItemTrade* Get_Buyer(const char* item_code) const;
    const NPCItemTrade* Get_Seller(const char* item_code) const;
    const ItemOrder* Get_Cost(const char* item_code) const;

    const MapCoord* Get_Coords(const char* npc) const;

private:
    std::map<std::string, std::string> m_Items;
    std::map<std::string, NPCItemTrade> m_Selling;
    std::map<std::string, NPCItemTrade> m_Buying;
};

#endif  // _NPC_MANAGER_HPP
