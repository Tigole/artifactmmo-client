#ifndef _CRAFT_SYSTEM_HPP
#define _CRAFT_SYSTEM_HPP 1

#include <map>
#include <string>
#include <vector>

#include "system.hpp"
#include "types.hpp"

class ItemManager;

class CraftSystem: public System
{
public:
    CraftSystem(ItemManager& item_manager);

    void Initialize(void);

    void Fill_Pipeline(Character& pipeline) override;

private:
    ItemManager& m_Item_Manager;
    std::vector<std::string> m_Items;
    std::map<std::string, MapCoord> m_Workshop_Coords;
};

#endif  // _CRAFT_SYSTEM_HPP
