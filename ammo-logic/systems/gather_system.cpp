#include "gather_system.hpp"

#include "net/client.hpp"

GatherSystem::GatherSystem(const char* system_name) : System(system_name) {}

void GatherSystem::Initialize()
{
    Client::singleton.Get_Resource_Spots(m_Spots);
    for (std::size_t ii = 0; ii < m_Spots.size(); ii++)
    {
        auto& drops = m_Spots[ii]["drops"];
        for (auto& d: drops)
        {
            // m_Resource_Coord.push_back(d.get<>(Loot));
        }
    }
}

void GatherSystem::Fill_Pipeline(Character& character)
{
    //
}

void GatherSystem::Gather_Resource(Character& character, const char* resource_code)
{
    //
}

WoodcuttingGatheringSystem WoodcuttingGatheringSystem::singleton;
MiningGatheringSystem MiningGatheringSystem::singleton;
AlchemyGatheringSystem AlchemyGatheringSystem::singleton;
FishingGatherSystem FishingGatherSystem::singleton;
