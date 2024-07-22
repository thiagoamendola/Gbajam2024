/*
 * Copyright (c) 2020-2024 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef FR_SCENE_H
#define FR_SCENE_H

#include "bn_optional.h"
#include "scene_type.h"

// enum class scene_type;

namespace fr
{
    class scene
    {

    public:
        virtual ~scene() = default;

        [[nodiscard]] virtual bn::optional<scene_type> update() = 0;

    protected:
        scene() = default;
    };

}

#endif
