#include "texture.h"

#include "renderer.h"
#include "vendor/stb_image/stb_image.h"

texture::texture(const std::string& path) :
renderer_id_(0), filepath_(path), local_buffer_(nullptr), width_(0), height_(0), bpp_(0)
{
	//Flips the image vertically because OpenGL draws from bottom to top
	//while normal texture coordinates are from top to bottom
	stbi_set_flip_vertically_on_load(1);

	//Desired channels 4 because RGBA
	local_buffer_ = stbi_load(path.c_str(), &width_, &height_, &bpp_, 4);

	//generate 1 texture and assign it to the current renderer
	GLCall(glGenTextures(1, &renderer_id_));
	GLCall(glBindTexture(GL_TEXTURE_2D, renderer_id_));

	//First Param  - Target [in our case 2D Texture]
	//Second Param - Parameter name to change [in this case texture minification filter]
	//Third Param  - Simple minification filter and not as brutal as nearest pixel [GL_NEAREST] 
	//Minification filter: how the texture will be scaled down when it needs to be drawn smaller than actual size
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//Horizontal Wrap -> Clamp [not extend area] | other option is TILING | S & T  like X & Y for textures
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	//Second Param: level - 0 because not a multilevel texture
	//Third Param: internal format  - RGBA -> How we want openGL to deal with our data
	//Sixth Param: - Border -> 0 means no border
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer_));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (local_buffer_)
		stbi_image_free(local_buffer_);
}

texture::~texture()
{
	//Params: Number of texture to cleanup, renderer id whose texture are bound to
	GLCall(glDeleteTextures(1, &renderer_id_));
}

void texture::bind(const unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, renderer_id_));
}

void texture::unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
