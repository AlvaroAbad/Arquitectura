#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>
#pragma warning (disable: 4388)
extern "C" uint8 *stbi_load(char const *, int *, int *, int *, int);
extern "C" void stbi_image_free(void *);

Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;
	int w, h;
	uint8 * buffer = stbi_load(filename.RealPath().ToCString(), &w, &h, NULL, 4);

	// Generamos la textura
	if (buffer) {
		width = static_cast<uint16>(w);
		height = static_cast<uint16>(h);
		uint16 newWidth = pow(2, ceil(Log2(width)));
		uint16 newHeight = pow(2, ceil(Log2(height)));
		if (width == newWidth && height == newHeight) {
			gltex = Renderer::Instance().GenImage(buffer, width, height);
			stbi_image_free(static_cast<void *>(buffer));
		}
		else {
			uint8 * newBuffer = (uint8 *)malloc(newWidth*newHeight * 4);
			memset(newBuffer, 0, newWidth*newHeight * 4);
			uint64 newBuffermargin = 0;
			uint64 bufferMargin = 0;
			for (uint64 h = 0; h < height; h++)
			{
				for (uint64 w = 0; w < width * 4; w++)
				{
					newBuffer[w + newBuffermargin] = buffer[w + bufferMargin];
				}
				newBuffermargin += newWidth * 4;
				bufferMargin += width * 4;
			}
			stbi_image_free(static_cast<void *>(buffer));
			gltex = Renderer::Instance().GenImage(newBuffer, newWidth, newHeight);
			stbi_image_free(static_cast<void *>(newBuffer));
			lastU = static_cast<double>(width) / static_cast<double>(newWidth);
			lastV = static_cast<double>(height) / static_cast<double>(newHeight);
		}

	}
}

	Image::~Image() {
		Renderer::Instance().DeleteImage(gltex);
	}

	void Image::Bind() const {
		Renderer::Instance().BindImage(gltex);
	}
