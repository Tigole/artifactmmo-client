#ifndef _PENDING_ITEMS_SYSTEM_HPP
#define _PENDING_ITEMS_SYSTEM_HPP 1

#include "system.hpp"

class PendingItemsSystem: public System
{
    PendingItemsSystem();

public:
    static PendingItemsSystem singleton;

    void Fill_Pipeline(Character& character) override;

    void OnAchievementChanged(void);

private:
    std::vector<std::string> m_Pending_Items;
};

#endif  // _PENDING_ITEMS_SYSTEM_HPP
