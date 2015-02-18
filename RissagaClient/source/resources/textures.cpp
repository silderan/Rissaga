#include "textures.h"

using namespace Ris;

bool Texture::load(const String &fname, SDL_Renderer *renderer)
{
	//The final texture
	SDL_Texture *newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(fname.c_str());
	if (loadedSurface == NULL)
	{
		g_log.logErr("Unable to load image " + fname + " : " + IMG_GetError());
		return false;
	}
	//Create texture from surface pixels
	m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (m_texture == NULL)
		g_log.logErr("Unable to create texture from " + fname + " : " + SDL_GetError());

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return true;
}

TextureShared Textures::getTexture(const String &fname, SDL_Renderer *renderer)
{
	TextureShared f = operator[](fname);
	if (!f.get())
	{
		f = std::make_shared<Texture>();
		if (f->load(fname, renderer))
		{
			operator[](fname) = f;
			return f;
		}
	}
	else
		return f;
	// Error, cannot be loaded :/
	g_log.logErr("Cannot load font file " + fname);
	erase(fname);
	return emptyTexture;
}
