#include <array>
#include <iostream>
#include <thread>

#include "logic_application.hpp"
#include "ui.hpp"

int main(int argc, char** argv)
{
    auto clk = std::chrono::high_resolution_clock::now();
    LogicApplication logic_application;
    std::thread logic_thread([&logic_application, argc, argv]() { logic_application.Run(argc, argv); });

    printf("sleep for logic init\n");
    while (logic_application.Is_Initialized() == false)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    ArtifactUI l_UI(logic_application.Get_Pipelines());

    l_UI.Initialize();
    for (;;)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        const float elapsed_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - clk).count() * 0.001f;
        clk = std::chrono::high_resolution_clock::now();

        l_UI.Update(elapsed_time);
        l_UI.Render();
    }

    return 0;
}
