#include "sources/tgaimage.h"
#include "sources/draw.h"
#include "sources/model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

const int width  = 800;
const int height = 800;

int main(int argc, char** argv) {
	wavefront::Model::ModelPtr model;

    if (argc == 2) {
        model = wavefront::BuildModelFromObjFile(argv[1]);
    } else {
		// std::cout << "./obj/african_head.obj" << std::endl;
        model = wavefront::BuildModelFromObjFile("/Users/apisareverlan/tinyrenderer/obj/african_head.obj");
    }

	TGAImage image(width, height, TGAImage::RGB);
    DrawLineModel(model, image, white);

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}