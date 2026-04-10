#include "map_manager.hpp"

#include "net/client.hpp"

MapManager::MapManager(Client& client) : m_Client(client) {}

void MapManager::Initialize(void)
{
    std::vector<nlohmann::json> maps;
    m_Client.Get_Maps(maps);
    for (const auto m: maps)
    {
        if (m["interactions"]["content"].is_null() == false)
        {
            const std::string l_Content_Type = m["interactions"]["content"]["type"];
            const std::string l_Content_Code = m["interactions"]["content"]["code"];
            if (l_Content_Type == "monster")
            {
                m_Monsters_Coords[l_Content_Code].push_back(MapCoord { m["x"].get<int>(), m["y"].get<int>() });
            }
            if (l_Content_Type == "resource")
            {
                m_Spots_Coords[l_Content_Code].push_back(MapCoord { m["x"].get<int>(), m["y"].get<int>() });
            }
        }
    }
}

const MapCoord* MapManager::Get_Monster_Coord(const char* monster) const
{
    return Get(monster, m_Monsters_Coords);
}

const MapCoord* MapManager::Get_Spot_Coord(const char* resource) const
{
    return Get(resource, m_Spots_Coords);
}

const MapCoord* MapManager::Get(const char* key, const std::map<std::string, std::vector<MapCoord>>& c) const
{
    auto it = c.find(key);
    if (it != c.end())
    {
        return &it->second.front();
    }
    return nullptr;
}
