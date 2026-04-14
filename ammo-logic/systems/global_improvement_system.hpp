#ifndef _GLOBAL_IMPROVEMENT_SYSTEM_HPP
#define _GLOBAL_IMPROVEMENT_SYSTEM_HPP 1

#include "system.hpp"

class GlobalImprovementSystem: public System
{
    GlobalImprovementSystem();

public:
    static GlobalImprovementSystem singleton;

    void Fill_Pipeline(Character& pipeline) override;

private:
    std::vector<MapCoord> m_Positions;
};

#endif  // _GLOBAL_IMPROVEMENT_SYSTEM_HPP
