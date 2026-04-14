#ifndef _RESOURCE_MANAGER_HPP
#define _RESOURCE_MANAGER_HPP 1

#include "types.hpp"

class Client;
class MapManager;
class Character;

class ResourceManager
{
    ResourceManager() = default;

public:
    static ResourceManager singleton;

    void Initialize(void);

    const MapCoord* Get_Resource_Coord(const Character& character, const char* resource) const;

private:
    struct Data
    {
        MapCoord coord;
        int rate;
        int level;
    };
    std::map<std::string, std::vector<Data>> m_Spots;
};

#endif  // _RESOURCE_MANAGER_HPP
