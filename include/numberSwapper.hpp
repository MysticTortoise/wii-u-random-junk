#pragma once

#include <array>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <span>
#include <memory>


#include <coreinit/memdefaultheap.h>
#include <coreinit/debug.h>
#include <coreinit/cache.h>
#include <sysapp/launch.h>
#include <whb/log_cafe.h>
#include <whb/log.h>
#include <whb/proc.h>


#include <whb/gfx.h>
#include <gx2/draw.h>
#include <gx2r/buffer.h>
#include <gx2/mem.h>
#include <gx2r/draw.h>
#include <gfd.h>

#include <romfs-wiiu.h>

#include "HelperStandard.hpp"

uint16_t inline _swapU16(uint16_t v) {
    return (v>>8) | (v<<8);
}

int16_t inline _swapS16(int16_t v) {
    return (v>>8) | (v<<8);
}

uint32_t inline _swapU32(uint32_t v) {
    return ((v>>24)&0xff) | ((v<<8)&0xff0000) | ((v>>8)&0xff00) | ((v<<24)&0xff000000);
}

int32_t inline _swapS32(int32_t v) {
    return ((v>>24)&0xff) | ((v<<8)&0xff0000) | ((v>>8)&0xff00) | ((v<<24)&0xff000000);
}

uint32_t inline _swapF32(const float v)
{
    return __builtin_bswap32(*(uint32_t*)&v);
}

float ReverseFloat( const float inFloat );

uint32_t FloatToUINTBitcas(const float v);