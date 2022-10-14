#include "texture.h"

#include "vendor/stb_image/stb_image.h"

texture::texture(const std::string& path) :
rendererID(0), filepath(path), localbuffer(nullptr), width(0), height(0), bpp(0)
{
	//Flips the image vertically because OpenGL draws from bottom to top
	//while normal texture coordinates are from top to bottom
	stbi_set_flip_vertically_on_load(true);

	//Desired channels 4 because RGBA (?)
	localbuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	//generate 1 texture and assign it to the current renderer
	GLCall(glGenTextures(1, &rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));

	//First Param  - Target [in our case 2D Texture]
	//Second Param - Parameter name to change [in this case texture minification filter]
	//Third Param  - Simple minification filter and not as brutal as nearest pixel [GL_NEAREST] 
	//Minification filter: how the texture will be scaled down when it needs to be drawn smaller than actual size
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//Horizontal Wrap -> Clamp [not extend area] | other option is TILING
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	//Second Param - 0 because not a multilevel texture
	//Third Param  - RGBA -> How we want openGL to deal with our data
	//Sixth Param  - Border -> 0 means no border
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localbuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (localbuffer)
		stbi_image_free(localbuffer);
}

texture::~texture()
{
	//Params: Number of texture to cleanup, renderer id whose texture are bound to
	GLCall(glDeleteTextures(1, &rendererID));
}

void texture::bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void texture::unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
