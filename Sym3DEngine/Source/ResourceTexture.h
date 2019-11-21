#pragma once

#include "Resource.h"
#include "Globals.h"

class ResourceTexture : public Resource
{
public:
	ResourceTexture(int width, int height, int nChannels, unsigned char* data) : width(width), height(height), nChannels(nChannels), data(data) {}

	void LoadOnMemory();

	inline uint getID() const { return textureID; }

private:

	//Texture
	int width, height, nChannels = 0;
	unsigned char* data = nullptr;

	//OpenGL Data
	uint textureID = 0u;
};