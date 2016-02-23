#include "..\include\collisionpixeldata.h"
#include "..\include\stb_image_write.h"

extern "C" uint8 *stbi_load(char const *, int *, int *, int *, int);
extern "C" void stbi_image_free(void *);

CollisionPixelData::CollisionPixelData(const String & filename)
{
	width = 0;
	height = 0;
	data = NULL;
	int w, h;
	uint32 * buffer = reinterpret_cast<uint32 *>(stbi_load(filename.RealPath().ToCString(), &w, &h, NULL, 4));
	if (buffer) {
		width = static_cast<uint16>(w);
		height = static_cast<uint16>(h);
		data = static_cast<bool *>(malloc(w*h*sizeof(bool)));
		for (uint32 i = 0; i < w*h; i++)
		{
			if (i == 4032) {
				printf("STOP");
			}
				data[i] =buffer[i] & 0xFF000000;
		}
		stbi_image_free(buffer);
	}
}

CollisionPixelData::~CollisionPixelData()
{
	free(data);
}

bool CollisionPixelData::GetData(uint32 x, uint32 y) const
{
	return data[y*width + x];
}
