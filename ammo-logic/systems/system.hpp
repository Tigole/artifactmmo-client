#ifndef _SYSTEM_HPP
#define _SYSTEM_HPP 1

#include <cstdio>

#include "character/character.hpp"

#define SYSTEM_PRINT(fmt, ...) printf("%s (%s): " fmt "\n", character.Get_Character(), Name(), ##__VA_ARGS__)

class System
{
public:
    System(const char* system_name) : m_System_Name(system_name) {}
    virtual ~System() = default;

    virtual void Fill_Pipeline(Character& pipeline) = 0;

    const char* Name(void) const
    {
        return m_System_Name;
    }

private:
    const char* m_System_Name;
};

#endif  // _SYSTEM_HPP
