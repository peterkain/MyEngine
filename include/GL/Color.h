#pragma once

#include <GL/glew.h>
#include "Types.h"

namespace engine { namespace Color {

    struct RGBA
    {
        u8 r, g, b, a;
    };

    struct GL
    {
        GLclampf r, g, b, a;
    };

    inline RGBA gl_to_rgba(const GL& c)
    {
        return RGBA{ static_cast<u8>(c.r * 255.f), static_cast<u8>(c.g * 255.f),
            static_cast<u8>(c.b * 255.f), static_cast<u8>(c.a * 255.f) };
    }

    inline GL rgba_to_gl(const RGBA& c)
    {
        return GL{ c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f };
    }

} }
