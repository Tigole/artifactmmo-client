#include "resource_manager.hpp"

#include "character/character.hpp"
#include "map_manager.hpp"
#include "net/client.hpp"

ResourceManager ResourceManager::singleton;

void ResourceManager::Initialize(void)
{
    std::vector<nlohmann::json> spots;

    Client::singleton.Get_Resource_Spots(spots);
    for (const auto& s: spots)
    {
        std::string spot_code          = s["code"];
        const MapCoord* resource_coord = MapManager::singleton.Get_Spot_Coord(spot_code.c_str());
        int level                      = s["level"];
        if (resource_coord != nullptr)
        {
            for (auto& d: s["drops"])
            {
                std::string resource_code = d["code"];
                m_Spots[resource_code].push_back({ *resource_coord, d["rate"].get<int>(), level });
            }
        }
    }
}

const MapCoord* ResourceManager::Get_Resource_Coord(const Character& character, const char* resource) const
{
    auto it = m_Spots.find(resource);
    if (it != m_Spots.end())
    {
        std::size_t index = 0;
        int distance      = std::numeric_limits<int>::max();
        for (std::size_t ii = 0; ii < it->second.size(); ii++)
        {
            if (character.Get_Distance(it->second[ii].coord) < distance)
            {
                distance = character.Get_Distance(it->second[ii].coord);
                index    = ii;
            }
        }

        return &it->second[index].coord;
    }
    return nullptr;
}

const char* ResourceManager::Get_Spot_Name(MapCoord coord) const
{
    return "";
}

int ResourceManager::Get_Required_Inventory_Space(MapCoord coord) const
{
    return 10;
}
