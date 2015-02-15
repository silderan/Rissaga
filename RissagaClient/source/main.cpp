
#include "Utils/Math.h"
#include "Utils/Point.h"
#include "Utils/Rect.h"
#include "Utils/Size.h"
#include "Utils/color.h"

#include "../../common/String.h"
#include "../../common/logging.h"

#include "resources/fonts.h"

#include <list>
#include <time.h>

#define GAME_NAME "Rissaga"

namespace Ris
{
	class Camera : public Rect
	{
	public:
	};
	typedef std::shared_ptr<Camera> CameraShared;

	class Entity
	{
		Rect m_rect;

	public:
		const Rect &rect()const { return m_rect; }
		Rect &rect() { return m_rect; }
		Entity()
		{ }
		Entity(const Rect &r) : m_rect(r)
		{ }
		virtual ~Entity()
		{ }
	};
	typedef std::shared_ptr<Entity> EntityShared;

	class Rectangle : public Entity
	{
		Color m_clr;
		SDL_Texture *m_texture;
		SDL_Renderer *m_renderer;

	public:
		Rectangle()
		{ }
		Rectangle(const Rect &r, const Color &c) : Entity(r), m_clr(c)
		{ }
		void render(SDL_Renderer* renderer, CameraShared cam)
		{
			SDL_SetRenderDrawColor(renderer, m_clr.getSDLColor().r, m_clr.getSDLColor().g, m_clr.getSDLColor().b, m_clr.getSDLColor().a);
			SDL_RenderFillRect(renderer, &rect().getSDLRect());
		}
		void render(SDL_Renderer* renderer)
		{
			render(renderer, CameraShared());
		}
	};
	typedef std::shared_ptr<Rectangle> RectangleShared;

	class Text : public Entity
	{
		FontShared m_font;
		String m_text;
		Color m_clr;
		SDL_Texture *m_texture;
		SDL_Renderer *m_renderer;

	public:
		Text() : m_texture(nullptr)
		{ }
		Text(SDL_Renderer *r, const Color &c = ColorWhite) : m_clr(c), m_texture(nullptr), m_renderer(r), m_font(g_Fonts.getFont("Cella.ttf", 12))
		{ }
		void render()
		{
			if (m_texture)
			{
				SDL_Rect r = { 200, 200, 100, 100 };
				SDL_RenderCopy(m_renderer, m_texture, NULL, &r);
			}
		}
		bool setText(const String &text)
		{
			m_text = text;
			if (m_texture)
			{
				SDL_DestroyTexture(m_texture);
				m_texture = nullptr;
			}
			//Render text surface
			SDL_Surface* textSurface = TTF_RenderText_Solid(m_font->getTTFFont(), m_text.c_str(), m_clr.getSDLColor());
			if (textSurface == NULL)
			{
				g_log.logErr("Unable to render text surface: " + String(TTF_GetError()));
			}
			else
			{
				//Create texture from surface pixels
				m_texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
				if (m_texture == nullptr)
				{
					g_log.logErr("Unable to create texture from rendered text: " + String(SDL_GetError()));
				}
///				else
//				{
					//Get image dimensions
//					mWidth = textSurface->w;
//					mHeight = textSurface->h;
//				}

				//Get rid of old surface
				SDL_FreeSurface(textSurface);
			}

			//Return success
			return m_texture != NULL;
		}
	};
	typedef std::shared_ptr<Text> TextShared;

	class MainWindow
	{
		SDL_Window *window;
		SDL_Renderer* renderer;
		std::list<EntityShared> entities;

	public:
		MainWindow() : window(nullptr), renderer(nullptr)
		{
		}
		SDL_Window *getWindow()const { return window; }
		SDL_Renderer *getRenderer() const { return renderer; }
		bool initWindow(const String &winName, int width, int height)
		{
			if (SDL_Init(SDL_INIT_VIDEO) < 0)
			{
				g_log.logErr(std::string("SDL could not initialize: ") + SDL_GetError());
				return false;
			}
			window = SDL_CreateWindow(winName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				g_log.logErr(std::string("Window could not be created: ") + SDL_GetError());
				return false;
			}
			if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == nullptr)
			{
				g_log.logErr(std::string("Cannot create renderer: ") + SDL_GetError());
				return false;
			}
			return true;
		}
	};
}

using namespace Ris;


int main(int argc, char *argv[])
{
	//The window we'll be rendering to
	MainWindow mainWin;
	if (!mainWin.initWindow(GAME_NAME, 800, 600))
		return EXIT_FAILURE;
	RectangleShared r = std::make_shared<Rectangle>(Rect(100, 100, 100, 100), Color(ColorWhite));
	TextShared t = std::make_shared<Text>(mainWin.getRenderer());
	t->setText("HOLA");
	//Event handler
	SDL_Event e;
	bool quit = false;
	int frames = 0;
	time_t hora = time(0);
	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		SDL_SetRenderDrawColor(mainWin.getRenderer(), 0, 0, 0, 0x0);
		SDL_RenderClear(mainWin.getRenderer());
		r->render(mainWin.getRenderer());
		if (hora != time(0))
		{
			hora = time(0);
			t->setText( "fps: " + String(frames) +".");
			frames = 0;
		}
		frames++;
		t->render();
		//Update screen
		SDL_RenderPresent(mainWin.getRenderer());
	}
	return EXIT_SUCCESS;
	/*	Pointf2D punto(-1.0f, 0.0f);
	float rad = punto.getRadians();
	float deg = punto.getDegrees();
	float deg1 = punto.getDegrees180();
	float deg3 = punto.getDegrees360();
	Pointf2D l = punto.limitX(1.2f, 1.3f);
	Pointf2D c = punto.limit(2, 5);
	Pointf2D r; r.fromDegrees(45);
	deg = r.getDegrees();
	r.rotateDegrees(-10);
	deg = r.getDegrees();
	return (int)deg;

	Font f;
	std::string ss("a");
	const char *cc = "a";
	String scc(cc);
	String ms = "a";
	String cs = ss + String("");
	String cn(123);
	String s = ss;
	String a = 123;
	String fn(f.familyName());
	s.fromNumber(10);
	s.fromNumber(11.0f);
	return s.length();

	Rect r(9, 9, 3, 4);
	Sizei i(10, 10);
	Rect rr(Pointi2D(10,10), i);
	if (rr.intersects(r))
		r = rr.intersect(r);
	return r.x;
	*/
}
