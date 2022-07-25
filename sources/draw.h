#ifndef __DRAW_H__
#define __DRAW_H__

#include <cstdint>
#include <algorithm>

#include "model.h"
#include "tgaimage.h"

void DrawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, TGAImage &image, TGAColor color);

void DrawLineModel(wavefront::Model::ModelPtr model, TGAImage& image, TGAColor color);

#endif //__DRAW_H__