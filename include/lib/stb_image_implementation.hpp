#pragma once

// used in cpp file
// 分开，是因为定义了STB_IMAGE_IMPLEMENTATION后，会在编译时生成stb_image的实现，在多个header中include回到指duplicate
// symbols
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>