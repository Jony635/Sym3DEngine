#pragma once

#include "Importer.h"

class ResourceTexture;

class TextureImporter : public Importer
{
public:
	static ResourceTexture* ImportTexture(const char* path);
};