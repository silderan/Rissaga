
#include "utils/math.h"
#include "utils/point.h"
#include "utils/rect.h"
#include "utils/size.h"
#include "utils/color.h"

#include "common/string.h"
#include "common/logging.h"

#include "resources/fonts.h"
#include "resources/textures.h"

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

	enum BlendMode
	{
		BlendNone = SDL_BLENDMODE_NONE,
		BlendBlend = SDL_BLENDMODE_BLEND,
		BlendAdd = SDL_BLENDMODE_ADD,
		BlendMod = SDL_BLENDMODE_MOD
	};

	class Renderer
	{
		SDL_Renderer *renderer;
	public:
		Renderer(SDL_Renderer *r) : renderer(r)
		{ }
		Renderer(Renderer &r) : renderer(r.renderer)
		{ }

		inline void setSDLRenderer(SDL_Renderer *r) { renderer = r; }
		inline const SDL_Renderer *getSDLRenderer() const { return renderer; }
		inline SDL_Renderer *getSDLRenderer() { return renderer; }
	};
	typedef std::shared_ptr<Renderer> RendererShared;

	class Entity
	{
		Rect m_rect;
		RendererShared m_renderer;

	public:
		template <typename T>
		inline float moveX(const T &i) { return m_rect.origin().adjustX(i); }
		template <typename T>
		inline float moveY(const T &i) { return m_rect.origin().adjustY(i); }
		template <typename T>
		inline Point2D &move(const T &x, const T &y) { return m_rect.origin.set(x, y); }
		inline Point2D &move(const Point2D &p) { return m_rect.origin() += p; }

		template <typename T>
		inline float moveToX(const T &x) { return m_rect.origin().setX(x); }
		template <typename T>
		inline float moveToY(const T &y) { return m_rect.origin().setY(y); }
		template <typename T>
		inline Point2D &moveTo(const T &x, const T &y) { return m_rect.origin().set(x, y); }
		inline Point2D &moveTo(const Point2D &p) { return m_rect.origin() = p; }

		template <typename T>
		inline float resizeX(const T &x) { return m_rect.size().adjustWidth(x); }
		template <typename T>
		inline float resizeY(const T &y) { return m_rect.size().adjustHeight(y); }
		template <typename T>
		inline Size &resize(const T &x, const T &y) { return m_rect.size().adjust(x, y); }
		inline Size &resize(const Size &s) { return m_rect.size().adjust(s); }

		template <typename T>
		inline float resizeToX(const T &x) { return m_rect.size().setWidth(x); }
		template <typename T>
		inline float resizeToY(const T &y) { return m_rect.size().setHeight(y); }
		template <typename T>
		inline Size &resizeTo(const T &x, const T &y) { return m_rect.size().set(x, y); }
		inline Size &resizeTo(const Size &s) { return m_rect.size().set(s); }

		const Rect &rect()const { return m_rect; }
		Rect &rect() { return m_rect; }
		Entity()
		{ }
		Entity(RendererShared r) : m_renderer(r)
		{ }
		virtual ~Entity()
		{ }

		inline const SDL_Renderer *getSDLRenderer() const { return m_renderer->getSDLRenderer(); }
		inline SDL_Renderer *getSDLRenderer() { return m_renderer->getSDLRenderer(); }

		inline const RendererShared getRenderer() const { return m_renderer; }
		inline RendererShared getRenderer() { return m_renderer; }

		virtual void render(CameraShared c) = 0;
	};
	typedef std::shared_ptr<Entity> EntityShared;

	class Rectangle : public Entity
	{
		Color m_clr;
		SDL_Texture *m_texture;
		bool m_filled;

	public:
		Rectangle(RendererShared r, const Color &c) : Entity(r), m_clr(c), m_filled(false)
		{ }
		bool filled() const { return m_filled; }
		void setFilled(bool f) { m_filled = true; }

		virtual void render(CameraShared cam)
		{
			SDL_SetRenderDrawColor(getSDLRenderer(), m_clr.getSDLColor().r, m_clr.getSDLColor().g, m_clr.getSDLColor().b, m_clr.getSDLColor().a);
			if (m_filled)
				SDL_RenderFillRect(getSDLRenderer(), &rect().getSDLRect());
			else
				SDL_RenderDrawRect(getSDLRenderer(), &rect().getSDLRect());
		}
	};
	typedef std::shared_ptr<Rectangle> RectangleShared;

	class Text : public Entity
	{
		FontShared m_font;
		String m_text;
		Color m_clr;
		SDL_Texture *m_texture;

	public:
		Text() : m_texture(nullptr)
		{ }
		Text(RendererShared r, const Color &c = ColorWhite) : Entity(r), m_clr(c), m_texture(nullptr), m_font(g_Fonts.getFont("resources/Cella.ttf", 12))
		{ }
		void render(CameraShared cam)
		{
			if (m_texture)
			{
				SDL_Rect r = { 200, 200, 100, 100 };
				SDL_RenderCopy(getSDLRenderer(), m_texture, NULL, &r);
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
				m_texture = SDL_CreateTextureFromSurface(getSDLRenderer(), textSurface);
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

	class Sprite : public Entity
	{
		TextureShared m_texture;

	public:
		bool loadTexture(const String &fname)
		{
			m_texture = g_Textures.getTexture(fname, getSDLRenderer());
			if (!m_texture.get())
				return false;
			return true;
		}
		Sprite(RendererShared r) : Entity(r)
		{

		}
		void render(CameraShared cam)
		{
			SDL_RenderCopy(getSDLRenderer(), m_texture->getSDLTexture(), NULL, NULL);
		}
	};
	typedef std::shared_ptr<Sprite> SpriteShared;

	class StaticSprite : public Sprite
	{
	public:

	};
	typedef std::shared_ptr<StaticSprite> StaticSpriteShared;

	class AnimedSprite : public Sprite
	{
	public:

	};
	typedef std::shared_ptr<AnimedSprite> AnimedSpriteShared;

	class MainWindow
	{
		SDL_Window *window;
		RendererShared m_renderer;
		std::list<EntityShared> entities;

	public:
		MainWindow() : window(nullptr)
		{
		}
		SDL_Window *getWindow()const { return window; }
		RendererShared getRenderer() const { return m_renderer; }

		bool initWindow(const String &winName, int width, int height)
		{
			if (SDL_Init(SDL_INIT_VIDEO) < 0)
			{
				g_log.logErr(String("SDL could not initialize: ") + SDL_GetError());
				return false;
			}
			window = SDL_CreateWindow(winName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				g_log.logErr(String("Window could not be created: ") + SDL_GetError());
				return false;
			}
			SDL_Renderer *r = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (r == nullptr)
			{
				g_log.logErr(String("Cannot create renderer: ") + SDL_GetError());
				return false;
			}
			m_renderer = std::make_shared<Renderer>(r);
			if (SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND) != 0)
			{
				g_log.logErr(String("Cannot render on blend mode: ") + SDL_GetError());
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
	CameraShared cam = std::make_shared<Camera>();
	RectangleShared r = std::make_shared<Rectangle>(mainWin.getRenderer(), Color(1.0f, 1.0f, 1.0f, 0.5f));
	r->moveTo(10, 10);
	r->resizeTo(100, 100);
	TextShared t = std::make_shared<Text>(mainWin.getRenderer(), Color(1.0f, 1.0f, 1.0f, 0.5f));
	t->setText("HOLA");
	SpriteShared sprite = std::make_shared<Sprite>(mainWin.getRenderer());
	sprite->loadTexture("resources/Hero.png");
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
		SDL_SetRenderDrawColor(mainWin.getRenderer()->getSDLRenderer(), 0, 0, 0, 0x0);
		SDL_RenderClear(mainWin.getRenderer()->getSDLRenderer());
		r->render(cam);
		if (hora != time(0))
		{
			hora = time(0);
			t->setText( "fps: " + String(frames) +".");
			frames = 0;
		}
		frames++;
		sprite->render(cam);
//		r->resize(0.01, 0.01);

		t->render(cam);
		//Update screen
		SDL_RenderPresent(mainWin.getRenderer()->getSDLRenderer());
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
