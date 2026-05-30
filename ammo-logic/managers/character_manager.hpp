#ifndef _CHARACTER_MANAGER_HPP
#define _CHARACTER_MANAGER_HPP 1

class CharacterManager
{
    CharacterManager() = default;

public:
    static CharacterManager singleton;

    int GetMinCombatLevel(void);
    int GetItemCount(const char* item_code);

private:
};

#endif  // _CHARACTER_MANAGER_HPP
