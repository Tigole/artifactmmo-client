#ifndef _LEVEL_SYSTEM_HPP
#define _LEVEL_SYSTEM_HPP 1

#include "keywords.hpp"
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
    GearcraftingLevelSystem() : LevelSystem(Keywords::Skills::gearcrafting) {}

public:
    static GearcraftingLevelSystem singleton;
};

class WeaponcraftingLevelSystem: public System
{
    WeaponcraftingLevelSystem() : System("WeaponcraftingLevelSystem") {}

    void Fill_Pipeline(Character& character) override;

public:
    static WeaponcraftingLevelSystem singleton;
};

class JewelrycraftingLevelSystem: public LevelSystem
{
    JewelrycraftingLevelSystem() : LevelSystem(Keywords::Skills::jewelrycrafting) {}

public:
    static JewelrycraftingLevelSystem singleton;
};

class CookingLevelSystem: public LevelSystem
{
    CookingLevelSystem() : LevelSystem(Keywords::Skills::cooking) {}

public:
    static CookingLevelSystem singleton;
};

class AlchemyLevelSystem: public LevelSystem
{
    AlchemyLevelSystem() : LevelSystem(Keywords::Skills::alchemy) {}

public:
    static AlchemyLevelSystem singleton;
};

#endif  // _LEVEL_SYSTEM_HPP
