// Copyright (c) 2010-present Bifrost Entertainment AS and Tommy Nguyen
// Distributed under the MIT License.
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include "Memory/TempBuffer.h"

#include <array>

namespace rainbow
{
    auto get_temp_buffer(size_t size) -> void*
    {
        constexpr size_t kTempBufferSize = 8192;

        if (size > kTempBufferSize)
            return nullptr;

        static std::array<uint8_t, kTempBufferSize> buffer;
        return buffer.data();
    }
}
