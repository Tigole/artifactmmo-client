#include <array>
#include <iostream>

#include "logic_application.hpp"

int main(int argc, char** argv)
{
    LogicApplication& logic_application = LogicApplication::singleton;

    while (true)
    {
        try
        {
            logic_application.Run(argc, argv);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}
