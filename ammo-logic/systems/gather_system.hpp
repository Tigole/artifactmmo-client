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

protected:
    std::vector<GatherOrder> m_Resources;
    std::vector<const char*> m_Equipements;

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

        m_Equipements.push_back("voidstone_axe");
        m_Equipements.push_back("adamantite_axe");
        m_Equipements.push_back("mithril_axe");
        m_Equipements.push_back("gold_axe");
        m_Equipements.push_back("steel_axe");
        m_Equipements.push_back("iron_axe");
        m_Equipements.push_back("copper_axe");
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

        m_Equipements.push_back("voidstone_pickaxe");
        m_Equipements.push_back("adamantite_pickaxe");
        m_Equipements.push_back("mithril_pickaxe");
        m_Equipements.push_back("gold_pickaxe");
        m_Equipements.push_back("steel_pickaxe");
        m_Equipements.push_back("iron_pickaxe");
        m_Equipements.push_back("copper_pickaxe");
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

        m_Equipements.push_back("voidstone_gloves");
        m_Equipements.push_back("adamantite_gloves");
        m_Equipements.push_back("mithril_gloves");
        m_Equipements.push_back("golden_gloves");
        m_Equipements.push_back("steel_gloves");
        m_Equipements.push_back("leather_gloves");
        m_Equipements.push_back("apprentice_gloves");
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

        m_Equipements.push_back("voidstone_fishing_rod");
        m_Equipements.push_back("adamantite_fishing_rod");
        m_Equipements.push_back("mithril_fishing_rod");
        m_Equipements.push_back("gold_fishing_rod");
        m_Equipements.push_back("steel_fishing_rod");
        m_Equipements.push_back("spruce_fishing_rod");
        m_Equipements.push_back("fishing_net");
    }

public:
    static FishingGatherSystem singleton;
};

#endif  // _GATHER_SYSTEM_HPP
