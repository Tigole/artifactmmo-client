#ifndef _MAP_MANAGER_HPP
#define _MAP_MANAGER_HPP 1

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

class Client;
struct MapCoord;

class MapManager
{
    MapManager() = default;

public:
    static MapManager singleton;

    void Initialize(void);

    const MapCoord* Get_Monster_Coord(const char* monster, MapCoord current_pos) const;
    const std::vector<MapCoord>* Get_Spot_Coord(const char* resource) const;

private:
    std::map<std::string, std::vector<MapCoord>> m_Monsters_Coords;
    std::map<std::string, std::vector<MapCoord>> m_Spots_Coords;

#if 0
    const MapCoord* Get(const char* key, MapCoord current_pos, const std::map<std::string, std::vector<MapCoord>>& c) const;
#endif
};

#endif  // _MAP_MANAGER_HPP
