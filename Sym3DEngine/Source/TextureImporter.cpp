#include "TextureImporter.h"
#include "ResourceTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"

ResourceTexture* TextureImporter::ImportTexture(const char* path)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, nChannels = 0;
	unsigned char* data = stbi_load(path, &width, &height, &nChannels, 4);

	return new ResourceTexture(width, height, nChannels, data);
}
