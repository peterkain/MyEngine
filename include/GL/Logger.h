#pragma once

#include <iostream>
#include <string>
#include <array>

#include "GL/Engine.h"
#include "Types.h"

#ifdef _ENGINE_WINDOWS
#include <Windows.h>
#undef near
#undef far
#undef APIENTRY
#endif

using namespace std::string_literals;

namespace engine { namespace Logger {

	enum class Level
	{
		Info = 0,
		Debug,
		Warn,
		Error
	};

#if defined _ENGINE_LINUX || defined _ENGINE_APPLE
    constexpr char* CONSOLE_RESET{ "\033[0;0;0m" };

    const std::array<std::string, 4> prefixes{
        "\033[34;1;1m" + "[INFO] ", "\033[32;1;1m" + "[DEBUG] ", "\033[33;1;1m" + "[WARNING] ", "\033[31;1;1m" + "[ERROR] "
    };
#elif defined _ENGINE_WINDOWS
    const HANDLE hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };

    constexpr std::array<u8, 5> colors{
    // Blue  Green  Yellow  Red  Reset
        3,    2,     6,      12,  7
    };

    const std::array<std::string, 4> prefixes{
        "[INFO] ", "[DEBUG] ", "[WARNING] ", "[ERROR] "
    };
#else
#error "Unsupported Operating System!"
#endif

    inline void flush()
    {
        std::flush(std::cout);
    }

    template <typename T>
    void log(T msg, Level level = Level::Info)
    {
#if defined _ENGINE_LINUX || defined _ENGINE_APPLE
        std::cout << prefixes[static_cast<u8>(level)];
        std::cout << msg << CONSOLE_RESET << '\n';
#elif defined _ENGINE_WINDOWS
        SetConsoleTextAttribute(hConsole, colors[static_cast<u8>(level)]);
        std::cout << prefixes[static_cast<u8>(level)];
        std::cout << msg << '\n';
        SetConsoleTextAttribute(hConsole, colors[4]);
#endif

        if(level == Level::Error)
        {
            flush();
            Engine::terminate();
            std::cin.get();
            std::exit(-1);
        }
    }

}
}
