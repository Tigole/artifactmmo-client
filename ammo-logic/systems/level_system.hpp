#ifndef _LEVEL_SYSTEM_HPP
#define _LEVEL_SYSTEM_HPP 1

#include "keywords.hpp"
#include "system.hpp"

class ItemCraftingManager;
class TrainingManager;

class LevelSystem: public System
{
public:
    LevelSystem(const char* name);

    void Fill_Pipeline(Character& character) override;

protected:
    MapCoord m_Workshop_Coord;
    const char* m_Default_Item_Code;
    const char* m_GT_10_Item_Code;
    const char* m_GT_20_Item_Code;
    const char* m_GT_30_Item_Code;
    const char* m_GT_40_Item_Code;
    bool m_Recycle = true;
};

class GearcraftingLevelSystem: public LevelSystem
{
    GearcraftingLevelSystem();

public:
    static GearcraftingLevelSystem singleton;
};

class WeaponcraftingLevelSystem: public LevelSystem
{
    WeaponcraftingLevelSystem();

public:
    static WeaponcraftingLevelSystem singleton;
};

class JewelrycraftingLevelSystem: public LevelSystem
{
    JewelrycraftingLevelSystem();

public:
    static JewelrycraftingLevelSystem singleton;
};

class CookingLevelSystem: public LevelSystem
{
    CookingLevelSystem();

public:
    static CookingLevelSystem singleton;
};

class AlchemyLevelSystem: public LevelSystem
{
    AlchemyLevelSystem();

public:
    static AlchemyLevelSystem singleton;
};

#endif  // _LEVEL_SYSTEM_HPP
