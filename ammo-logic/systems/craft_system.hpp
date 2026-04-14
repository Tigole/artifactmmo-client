#ifndef _CRAFT_SYSTEM_HPP
#define _CRAFT_SYSTEM_HPP 1

#include <map>
#include <string>
#include <vector>

#include "system.hpp"
#include "types.hpp"
#if 0
class ItemManager;

class CraftSystem: public System
{
protected:
    CraftSystem();

public:
    void Initialize(void);

    void Fill_Pipeline(Character& pipeline) override;

private:
    std::vector<std::string> m_Items;
    std::map<std::string, MapCoord> m_Workshop_Coords;
};
#endif

#endif  // _CRAFT_SYSTEM_HPP
