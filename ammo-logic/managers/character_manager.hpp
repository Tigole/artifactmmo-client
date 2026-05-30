#ifndef _CHARACTER_MANAGER_HPP
#define _CHARACTER_MANAGER_HPP 1

class CharacterManager
{
    CharacterManager() = default;

public:
    static CharacterManager singleton;

    int GetMinCombatLevel(void);

private:
};

#endif  // _CHARACTER_MANAGER_HPP
