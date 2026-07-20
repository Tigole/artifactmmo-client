#include "map_manager.hpp"

#include "net/client.hpp"

MapManager MapManager::singleton;

void MapManager::Initialize(void)
{
    std::vector<nlohmann::json> maps;
    Client::singleton.Get_Maps(maps);
    for (const auto m: maps)
    {
        if (m["interactions"]["content"].is_null() == false)
        {
            const std::string l_Content_Type = m["interactions"]["content"]["type"];
            const std::string l_Content_Code = m["interactions"]["content"]["code"];
            const std::string layer          = m["layer"].get<std::string>();
            const int x                      = m["x"].get<int>();
            const int y                      = m["y"].get<int>();
            if (l_Content_Type == "monster")
            {
                m_Monsters_Coords[l_Content_Code].emplace_back(layer, x, y);
            }
            if (l_Content_Type == "resource")
            {
                m_Spots_Coords[l_Content_Code].emplace_back(layer, x, y);
            }
        }
    }
}

const MapCoord* MapManager::Get_Monster_Coord(const char* monster, MapCoord current_pos) const
{
    auto it = m_Monsters_Coords.find(monster);
    if (it != m_Monsters_Coords.end())
    {
        std::size_t idx = 0;
        int distance    = current_pos.Get_Distance(it->second[0]);
        for (std::size_t ii = 1; ii < it->second.size(); ii++)
        {
            if (current_pos.Get_Distance(it->second[ii]) < distance)
            {
                idx = ii;
            }
        }
        return &it->second[idx];
    }
    return nullptr;
}

const std::vector<MapCoord>* MapManager::Get_Spot_Coord(const char* resource) const
{
    auto it = m_Spots_Coords.find(resource);
    if (it != m_Spots_Coords.end())
    {
        return &it->second;
    }
    return nullptr;
}

#if 0
const MapCoord* MapManager::Get(const char* key, MapCoord current_pos, const std::map<std::string, std::vector<MapCoord>>& c) const
{
    auto it = c.find(key);
    if (it != c.end())
    {
        std::size_t idx = 0;
        int distance    = current_pos.Get_Distance(it->second[0]);
        for (std::size_t ii = 1; ii < it->second.size(); ii++)
        {
            if (current_pos.Get_Distance(it->second[ii]) < distance)
            {
                idx = ii;
            }
        }
        return &it->second[idx];
    }
    return nullptr;
}
#endif
