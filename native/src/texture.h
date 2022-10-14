#pragma once

#include "renderer.h"

class texture
{
private:
	unsigned int rendererID;
	std::string filepath;
	unsigned char* localbuffer;
	int width, height, bpp;

public:
	texture(const std::string& path);
	~texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int get_width() const
	{
		return width;
	}

	inline int get_height() const
	{
		return height;
	}
};

