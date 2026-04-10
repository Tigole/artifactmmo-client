#ifndef _INVENTORY_MANAGER_HPP
#define _INVENTORY_MANAGER_HPP 1

#include <vector>

#include "types.hpp"

class Client;
class ItemManager;
class Character;
struct InventoryWeapons;
struct InventoryArmorPart;

class InventoryManager
{
public:
    InventoryManager(Client& client, ItemManager& item_manager);

    void Deposit_Resources(Character& character, const char* keep) const;

    int Get_Bank_Item_Count(const char* item_code);

    int Get_Gold_Amount(void);

    MapCoord Get_Bank_Nearest_Coord(Character& character) const;

    void Get_Fight_Items(int level, std::vector<InventoryWeapons>& weapons, std::vector<InventoryArmorPart>& helmets,
                         std::vector<InventoryArmorPart>& body_armors, std::vector<InventoryArmorPart>& leg_armors,
                         std::vector<InventoryArmorPart>& boots, std::vector<InventoryArmorPart>& shields,
                         std::vector<InventoryArmorPart>& rings1, std::vector<InventoryArmorPart>& rings2,
                         std::vector<InventoryArmorPart>& amulets) const;

    void Update_Cache(void);

private:
    Client& m_Client;
    ItemManager& m_Item_Manager;
    MapCoord m_Bank_Coord_1 = { 4, 1 };
    MapCoord m_Bank_Coord_2 = { 7, 13 };
    std::map<std::string, int> m_Bank_Content;
    std::vector<const char*> m_Resources_To_Deposit;
    int m_Gold_Amount = 0;
};

#endif  // _INVENTORY_MANAGER_HPP
