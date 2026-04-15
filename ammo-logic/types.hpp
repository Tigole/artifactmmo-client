#ifndef _TYPES_HPP
#define _TYPES_HPP 1

#include <fmt/format.h>

#include <cmath>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

struct MapContent
{
    std::string type;
    std::string code;
};

struct MapCoord
{
    int x, y;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MapCoord, x, y);

    int Get_Distance(MapCoord other) const
    {
        return abs(other.x - x) + abs(other.y - y);
    }
};

/*struct Map
{
    std::string name;
    std::string skin;
    std::unique_ptr<MapContent> content;
    int x;
    int y;
};*/

struct ItemOrder
{
    std::string code;
    int quantity;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ItemOrder, code, quantity);
};

struct EquipOrder
{
    std::string code;
    std::string slot;
    int quantity = 1;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(EquipOrder, code, slot, quantity);
};

struct UnequipOrder
{
    std::string slot;
    int quantity = 1;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UnequipOrder, slot, quantity);
};

struct Recipe
{
    std::string skill_name;
    int skill_level;
    std::string target_item;
    std::vector<ItemOrder> required_items;
};

struct GatheringRequirement
{
    std::string skill_name;
    int skill_level;
};

struct Loot
{
    std::string code;
    int rate;
    int min_quantity;
    int max_quantity;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Loot, code, rate, min_quantity, max_quantity);
};

#endif  // _TYPES_HPP
