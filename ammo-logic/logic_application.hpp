#ifndef _LOGIC_APPLICATION_HPP
#define _LOGIC_APPLICATION_HPP 1

#include <array>
#include <character/character_pipeline.hpp>

class LogicApplication
{
public:
    void Run(int argc, char** argv);

    const std::array<CharacterPipeline, 5>& Get_Pipelines(void) const;
    bool Is_Initialized(void) const;

private:
    std::array<CharacterPipeline, 5> m_Pipeline;
    bool m_Initialized = false;
};

#endif  // _LOGIC_APPLICATION_HPP
