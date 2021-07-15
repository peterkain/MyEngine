#pragma once

namespace engine {

struct WindowInfo
{
public:
    WindowInfo() : major_version{ 0 }, minor_version{ 0 }, samples{ 0 }, resizable{ false } {}
    WindowInfo(int major, int minor, int samples, bool resizable)
        :   major_version {major}
        ,   minor_version {minor}
        ,   samples {samples}
        ,   resizable {resizable}
    {}

public:
    int major_version;
    int minor_version;
    int samples;

    bool resizable;
};

}
