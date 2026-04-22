#ifndef _GATHER_SYSTEM_HPP
#define _GATHER_SYSTEM_HPP 1

#include "system.hpp"

class Client;

struct GatherOrder
{
    const char* item_code;
    int target_amount;
};

class GatherSystem: public System
{
public:
    GatherSystem(const char* system_name);
    void Initialize(void);

    void Fill_Pipeline(Character& character) override;
    const std::vector<const char*>& Get_Equipements(void) const;

protected:
    std::vector<GatherOrder> m_Resources;
    std::vector<const char*> m_Equipements;

private:
    std::vector<nlohmann::json> m_Spots;
    std::map<std::string, MapCoord> m_Resource_Coord;
};

class WoodcuttingGatheringSystem: public GatherSystem
{
    WoodcuttingGatheringSystem();

public:
    static WoodcuttingGatheringSystem singleton;
};

class MiningGatheringSystem: public GatherSystem
{
    MiningGatheringSystem();

public:
    static MiningGatheringSystem singleton;
};

class AlchemyGatheringSystem: public GatherSystem
{
    AlchemyGatheringSystem();

public:
    static AlchemyGatheringSystem singleton;
};

class FishingGatherSystem: public GatherSystem
{
    FishingGatherSystem();

public:
    static FishingGatherSystem singleton;
};

class MobGatherSystem: public System
{
    MobGatherSystem();

public:
    void Fill_Pipeline(Character& character) override;

    static MobGatherSystem singleton;

private:
    std::vector<GatherOrder> m_Resources;
};

#endif  // _GATHER_SYSTEM_HPP
