#include "ui.hpp"

#include <raylib.h>

#define CLAY_IMPLEMENTATION
#include <clay.h>

ArtifactUI::ArtifactUI(const std::array<CharacterPipeline, 5>& p) : pipelines(p) {}

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

void CharactersList(const std::array<CharacterPipeline, 5>& pipelines)
{
    static const std::array<Color, 5> colors = {
        { VIOLET, BLUE, GREEN, ORANGE, RED }
    };
    static std::array<std::string, 5> strings;
    constexpr const int font_size = 30;

    int x = 10;
    int y = 10;
    for (std::size_t ii = 0; ii < pipelines.size(); ii++)
    {
        const CharacterPipeline& p = pipelines[ii];
        strings[ii]                = fmt::format("{} - {:.2}s - {}", p.Get_Character(), p.Get_Remaining_Timeout(), p.Get_Current_Order());

        DrawText(strings[ii].c_str(), x, y, font_size, colors[ii]);
        y += font_size;
    }
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
