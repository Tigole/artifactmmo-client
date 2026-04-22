#ifndef _LEVEL_SYSTEM_HPP
#define _LEVEL_SYSTEM_HPP 1

#include "keywords.hpp"
#include "system.hpp"

class ItemCraftingManager;
class TrainingManager;

class LevelCraftSystem: public System
{
public:
    LevelCraftSystem(const char* name);

    void Fill_Pipeline(Character& character) override;

protected:
    MapCoord m_Workshop_Coord;
    const char* m_Skill_Name;
    const char* m_Default_Item_Code;
    const char* m_GT_10_Item_Code;
    const char* m_GT_20_Item_Code;
    const char* m_GT_30_Item_Code;
    const char* m_GT_40_Item_Code;
    bool m_Recycle = true;
};

class GearcraftingLevelSystem: public LevelCraftSystem
{
    GearcraftingLevelSystem();

public:
    static GearcraftingLevelSystem singleton;
};

class WeaponcraftingLevelSystem: public LevelCraftSystem
{
    WeaponcraftingLevelSystem();

public:
    static WeaponcraftingLevelSystem singleton;
};

class JewelrycraftingLevelSystem: public LevelCraftSystem
{
    JewelrycraftingLevelSystem();

public:
    static JewelrycraftingLevelSystem singleton;
};

class CookingLevelSystem: public LevelCraftSystem
{
    CookingLevelSystem();

public:
    static CookingLevelSystem singleton;
};

class AlchemyCraftLevelSystem: public LevelCraftSystem
{
    AlchemyCraftLevelSystem();

public:
    static AlchemyCraftLevelSystem singleton;
};

class LevelGatherSystem: public System
{
public:
    LevelGatherSystem(const char* name);

    void Fill_Pipeline(Character& character) override;

protected:
    const char* m_Skill_Name;
    const std::vector<const char*>* m_Equipements;
    MapCoord m_Default_Spot_Coord;
    MapCoord m_GT_10_Spot_Coord;
    MapCoord m_GT_20_Spot_Coord;
    MapCoord m_GT_30_Spot_Coord;
    MapCoord m_GT_40_Spot_Coord;
};

class MiningLevelSystem: public LevelGatherSystem
{
    MiningLevelSystem();

public:
    static MiningLevelSystem singleton;
};

class WoodcuttingLevelSystem: public LevelGatherSystem
{
    WoodcuttingLevelSystem();

public:
    static WoodcuttingLevelSystem singleton;
};

class FishingLevelSystem: public LevelGatherSystem
{
    FishingLevelSystem();

public:
    static FishingLevelSystem singleton;
};

class AlchemyGatherLevelSystem: public LevelGatherSystem
{
    AlchemyGatherLevelSystem();

public:
    static AlchemyGatherLevelSystem singleton;
};

#endif  // _LEVEL_SYSTEM_HPP
