#pragma once

#include <string>

class texture
{
private:
	unsigned int renderer_id_;
	std::string filepath_;
	unsigned char* local_buffer_;
	int width_, height_, bpp_;

public:
	texture(const std::string& path);
	~texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int get_width() const
	{
		return width_;
	}

	inline int get_height() const
	{
		return height_;
	}
};

