#ifndef _GATHER_SYSTEM_HPP
#define _GATHER_SYSTEM_HPP 1

#include "system.hpp"

class Client;

class GatherSystem: public System
{
public:
    GatherSystem();
    void Initialize(Client& client);

    void Fill_Pipeline(Character& character) override;

    void Gather_Resource(Character& character, const char* resource_code);

private:
    std::vector<nlohmann::json> m_Spots;
    std::map<std::string, MapCoord> m_Resource_Coord;
};

#endif  // _GATHER_SYSTEM_HPP
