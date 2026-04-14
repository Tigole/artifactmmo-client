#ifndef _LEVEL_SYSTEM_HPP
#define _LEVEL_SYSTEM_HPP 1

#include "system.hpp"

class ItemCraftingManager;
class TrainingManager;

class LevelSystem: public System
{
public:
    LevelSystem(const char* skill);

    void Fill_Pipeline(Character& character) override;

private:
    const char* m_Skill;

    void Make_Train(Character& character, const char* skill_name, int skill_level) const;
};

class GearcraftingLevelSystem: public LevelSystem
{
    GearcraftingLevelSystem() : LevelSystem("gearcrafting") {}

public:
    static GearcraftingLevelSystem singleton;
};

class WeaponcraftingLevelSystem: public LevelSystem
{
    WeaponcraftingLevelSystem() : LevelSystem("weaponcrafting") {}

public:
    static WeaponcraftingLevelSystem singleton;
};

class JewelrycraftingLevelSystem: public LevelSystem
{
    JewelrycraftingLevelSystem() : LevelSystem("jewelrycrafting") {}

public:
    static JewelrycraftingLevelSystem singleton;
};

class CookingLevelSystem: public LevelSystem
{
    CookingLevelSystem() : LevelSystem("cooking") {}

public:
    static CookingLevelSystem singleton;
};

class AlchemyLevelSystem: public LevelSystem
{
    AlchemyLevelSystem() : LevelSystem("alchemy") {}

public:
    static AlchemyLevelSystem singleton;
};

#endif  // _LEVEL_SYSTEM_HPP
