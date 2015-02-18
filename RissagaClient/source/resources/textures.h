#pragma once

#include <unordered_map>
#include <memory>

#include "common/string.h"
#include "common/logging.h"
#include "SDL2/include/SDL_image.h"

namespace Ris
{
	class Texture
	{
		SDL_Texture *m_texture;

	public:
		SDL_Texture *getSDLTexture() const { return m_texture; }
		Texture() : m_texture(nullptr)
		{ }
		~Texture()
		{
			SDL_DestroyTexture(m_texture);
		}
		bool load(const String &fname, SDL_Renderer *renderer);
	};
	typedef std::shared_ptr<Texture> TextureShared;

	// ToDo: Must be singleton!
	class Textures : std::unordered_map<std::string, TextureShared>
	{

	public:
		Textures(int imgFlags = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP))
		{
			if (!IMG_Init(imgFlags) != imgFlags )
				g_log.logErr("Cannot initialize image libraries: " + String(IMG_GetError()));
		}
		~Textures()
		{
			clear();
			IMG_Quit();
		}

		// Gets texture from filename.
		TextureShared getTexture(const String &fname, SDL_Renderer *renderer);
	};
	static Textures g_Textures;
}