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

    void Gather_Resource(Character& character, const char* resource_code);

protected:
    std::vector<GatherOrder> m_Resources;

private:
    std::vector<nlohmann::json> m_Spots;
    std::map<std::string, MapCoord> m_Resource_Coord;
};

class WoodcuttingGatheringSystem: public GatherSystem
{
    WoodcuttingGatheringSystem() : GatherSystem("WoodcuttingGatheringSystem")
    {
        m_Resources.push_back({ "ash_wood", 500 });
        m_Resources.push_back({ "spruce_wood", 500 });
        m_Resources.push_back({ "birch_wood", 500 });
        m_Resources.push_back({ "hardwood_wood", 500 });
        m_Resources.push_back({ "dead_wood", 500 });
        m_Resources.push_back({ "magic_wood", 500 });
        m_Resources.push_back({ "maple_wood", 500 });
        m_Resources.push_back({ "palm_wood", 500 });
    }

public:
    static WoodcuttingGatheringSystem singleton;
};

class MiningGatheringSystem: public GatherSystem
{
    MiningGatheringSystem() : GatherSystem("MiningGatheringSystem")
    {
        m_Resources.push_back({ "copper_ore", 500 });
        m_Resources.push_back({ "iron_ore", 500 });
        m_Resources.push_back({ "coal", 500 });
        m_Resources.push_back({ "gold_ore", 500 });
        m_Resources.push_back({ "strange_ore", 500 });
        m_Resources.push_back({ "mithril_ore", 500 });
        m_Resources.push_back({ "adamantine_ore", 500 });
    }

public:
    static MiningGatheringSystem singleton;
};

class AlchemyGatheringSystem: public GatherSystem
{
    AlchemyGatheringSystem() : GatherSystem("AlchemyGatheringSystem")
    {
        m_Resources.push_back({ "sunflower", 500 });
        m_Resources.push_back({ "nettle_leaf", 500 });
        m_Resources.push_back({ "glowstem_leaf", 500 });
        m_Resources.push_back({ "torch_cactus_flower", 500 });
    }

public:
    static AlchemyGatheringSystem singleton;
};

class FishingGatherSystem: public GatherSystem
{
    FishingGatherSystem() : GatherSystem("FishingGatherSystem")
    {
        m_Resources.push_back({ "gudgeon", 500 });
        m_Resources.push_back({ "shrimp", 500 });
        m_Resources.push_back({ "trout", 500 });
        m_Resources.push_back({ "bass", 500 });
        m_Resources.push_back({ "salmon", 500 });
        m_Resources.push_back({ "swordfish", 500 });
    }

public:
    static FishingGatherSystem singleton;
};

#endif  // _GATHER_SYSTEM_HPP
