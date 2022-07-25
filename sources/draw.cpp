#include "draw.h"

#include "model.h"

void DrawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, TGAImage& image, TGAColor color) {
    int32_t delta_x = std::abs(x0 - x1),
            delta_y = std::abs(y0 - y1);

    bool steep = false;
    if (delta_x < delta_y) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        std::swap(delta_x, delta_y);
        steep = true;
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    // double not because it's double type, but becsuse it's double times delta_error :)
    int32_t double_delta_error = 2 * delta_y,
            y = y0,
            double_error = 0,
            dir_y = y1 > y0 ? 1 : -1;

    if (steep) {
        for (int32_t x = x0; x <= x1; ++x) {
            image.set(y, x, color);
            double_error += double_delta_error;

            if (double_error >= delta_x) {
                y += dir_y;
                double_error -= 2 * delta_x;
            }
        }
    } else {
        for (int32_t x = x0; x <= x1; ++x) {
            image.set(x, y, color);
            double_error += double_delta_error;

            if (double_error >= delta_x) {
                y += dir_y;
                double_error -= 2 * delta_x;
            }
        }
    }
}

void DrawLineModel(wavefront::Model::ModelPtr model, TGAImage& image, TGAColor color) {
    for (int64_t i = 0; i < model->GetNumFaces(); i++) {
        std::vector<int64_t> face = model->GetFaceByIndex(i);

        for (int j = 0; j < 3; j++) {
            geometry::Vector3f v0 = model->GetVertexByIndex(face[j]);
            geometry::Vector3f v1 = model->GetVertexByIndex(face[(j + 1) % 3]);

            int x0 = (v0.x + 1.) * image.get_width() / 2.;
            int y0 = (v0.y + 1.) * image.get_height() / 2.;
            int x1 = (v1.x + 1.) * image.get_width() / 2.;
            int y1 = (v1.y + 1.) * image.get_height() / 2.;

            DrawLine(x0, y0, x1, y1, image, color);
        }
    }
}
