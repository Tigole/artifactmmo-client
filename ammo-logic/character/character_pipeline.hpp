#ifndef _CHARACTER_PIPELINE_HPP
#define _CHARACTER_PIPELINE_HPP 1

#include <vector>

#include "character.hpp"

class System;

class CharacterPipeline
{
public:
    CharacterPipeline();

    void Set_Character(const char* character_name);
    const char* Get_Character(void) const;
    void Add_System(System* system);

    void Update(float elapsed_time);

    std::string Get_Current_Order(void) const;
    float Get_Remaining_Timeout(void) const;

private:
    Character m_Character;
    std::vector<System*> m_Systems;
};

#endif  // _CHARACTER_PIPELINE_HPP
