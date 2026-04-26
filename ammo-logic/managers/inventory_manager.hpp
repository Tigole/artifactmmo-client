#ifndef _INVENTORY_MANAGER_HPP
#define _INVENTORY_MANAGER_HPP 1

#include <vector>

#include "types.hpp"

class Client;
class ItemManager;
class Character;
class System;
struct InventoryWeapons;
struct InventoryArmorPart;

class InventoryManager
{
    InventoryManager() = default;

public:
    static InventoryManager singleton;

    void Initialize(void);

    int Get_Bank_Item_Count(const char* item_code) const;
    int Get_Bank_Remaining_Slot_Count(void) const;
    int Get_Bank_Expansion_Cost(void) const;

    int Get_Gold_Amount(void) const;

    MapCoord Get_Bank_Nearest_Coord(Character& character) const;
    MapCoord Get_Bank_Nearest_Coord(MapCoord coord) const;

    void Get_Fight_Items(int level, std::vector<InventoryWeapons>& weapons, std::vector<InventoryArmorPart>& helmets,
                         std::vector<InventoryArmorPart>& body_armors, std::vector<InventoryArmorPart>& leg_armors,
                         std::vector<InventoryArmorPart>& boots, std::vector<InventoryArmorPart>& shields,
                         std::vector<InventoryArmorPart>& rings, std::vector<InventoryArmorPart>& amulets) const;

    void Update_Cache(void);

private:
    MapCoord m_Bank_Coord_1 = { 4, 1 };
    MapCoord m_Bank_Coord_2 = { 7, 13 };
    std::map<std::string, int> m_Bank_Content;
    int m_Gold_Amount = 0;

    int m_Max_Slot_Count      = 0;
    int m_Next_Expansion_Cost = 0;
};

#endif  // _INVENTORY_MANAGER_HPP
