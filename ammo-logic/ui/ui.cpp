#include "ui.hpp"

#include <raylib.h>

#define CLAY_IMPLEMENTATION
#include <clay.h>

ArtifactUI::ArtifactUI(std::array<CharacterPipeline, 5>& p) : pipelines(p) {}

void ArtifactUI::Initialize(void)
{
    constexpr const int screenWidth  = 1280;
    constexpr const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "ammo-client");
    SetTargetFPS(60);
}

ArtifactUI::~ArtifactUI()
{
    CloseWindow();
}

void ArtifactUI::Update(float dt)
{
    //
}

Clay_Color GetColor(Color c)
{
    return { (float)c.r, (float)c.g, (float)c.b, (float)c.a };
}

void CharactersList(std::array<CharacterPipeline, 5>& pipelines)
{
    static const std::array<Color, 5> colors = {
        { RED, VIOLET, BLUE, GREEN, ORANGE }
    };
    static std::array<std::string, 5> strings;

    int x = 10;
    int y = 10;
    for (std::size_t ii = 0; ii < pipelines.size(); ii++)
    {
        const CharacterPipeline& p = pipelines[ii];
        strings[ii]                = fmt::format("{} - {:.2}s - {}", p.Get_Character(), p.Get_Remaining_Timeout(), p.Get_Current_Order());

        DrawText(strings[ii].c_str(), x, y, 30, colors[ii]);
        y += 30;
    }
    //}
}

void ArtifactUI::Render(void)
{
    ClearBackground(BLACK);
    BeginDrawing();
    {
        CharactersList(pipelines);
    }
    EndDrawing();
}
