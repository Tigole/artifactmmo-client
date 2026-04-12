#ifndef _UI_HPP
#define _UI_HPP 1

#include <array>

#include "character/character_pipeline.hpp"

class ArtifactUI
{
public:
    ArtifactUI(std::array<CharacterPipeline, 5>&);
    ~ArtifactUI();

    void Initialize(void);
    void Update(float dt);
    void Render(void);

private:
    std::array<CharacterPipeline, 5>& pipelines;
};

#endif  // _UI_HPP
