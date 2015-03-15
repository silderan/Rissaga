
#include "utils/math.h"
#include "utils/point.h"
#include "utils/rect.h"
#include "utils/size.h"
#include "utils/color.h"

#include "common/state_machine.h"
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
		inline void move(const T &x, const T &y) { moveX(x); moveY(y); }
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

		inline const SDL_Rect *getSDLRect() { return &m_rect.getSDLRect(); }

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
				SDL_RenderFillRect(getSDLRenderer(), getSDLRect());
			else
				SDL_RenderDrawRect(getSDLRenderer(), getSDLRect());
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
				SDL_RenderCopy(getSDLRenderer(), m_texture, NULL, getSDLRect());
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
		Rect m_sourceRect;

	public:
		inline Rect &sourceRect() { return m_sourceRect; }
		inline const Rect &sourceRect() const { return m_sourceRect; }
		inline Rect &destRect() { return Entity::rect(); }
		inline const Rect &destRect() const { Entity::rect(); }

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
			SDL_RenderCopy(getSDLRenderer(), m_texture->getSDLTexture(), &sourceRect().getSDLRect(), &destRect().getSDLRect());
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
		enum MoveFlags
		{
			MoveEast  = 0x0,
			MoveWest  = 0x1,
			MoveNorth = 0x2,
			MoveSouth = 0x4,
			MoveUp    = 0x8,
			MoveDown  = 0x10
		};
	private:
		MoveFlags moving;
	public:
		inline void setMoveFlag(MoveFlags f) { moving |= f; }
		inline void resetMoveFlag(MoveFlags f) { moving |= f; }

		float subAnimation;
		Point2D interSpeed;
		AnimedSprite(RendererShared &r) : Sprite(r), subAnimation(0)
		{}
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
		inline SDL_Window *getWindow() const { return window; }
		inline RendererShared &getRenderer() { return m_renderer; }

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
	class GameObj
	{
		Point2D m_position;
		String m_name;

	public:
		Point2D &position() { return m_position; }
		const Point2D &position() const { return m_position; }
		String &name() { return m_name; }
		const String &name() const { return m_name; }
	};

	class AliveObj : public GameObj
	{
		int m_health;
		int m_mana;

		// Valid States;
		struct MovementStates
		{
			StateStand stateStanding;
			StateWalking stateWalking;
		}movementStates;

		State *moveState;
		inline void newMovementState(State *state, const SDL_KeyboardEvent &key)
		{
			moveState->onExit();
			moveState = state;
			moveState->onEnter(key);
		}
	public:
		AliveObj() : moveState(&movementStates.stateStanding)
		{ }
		void checkKeyboard(const SDL_KeyboardEvent &key)
		{
			switch (moveState->checkKeyboard(key))
			{
			case State::NoState:
				break;
			case State::Walking:
				newMovementState(&movementStates.stateWalking, key);
				break;
			case State::Standing:
				newMovementState(&movementStates.stateStanding, key);
				break;
			}
		}
	};
}

using namespace Ris;

#define TICKS_PER_SECOND(t) (1000/t)

const int tickInterval = TICKS_PER_SECOND(20);
const int frameInterval = TICKS_PER_SECOND(60);
const float interInterval = ceil((float)tickInterval / (float)frameInterval);

int main(int argc, char *argv[])
{
	argc = argc;
	argv = argv;
	//The window we'll be rendering to
	MainWindow mainWin;
	if (!mainWin.initWindow(GAME_NAME, 800, 600))
		return EXIT_FAILURE;
	CameraShared cam = std::make_shared<Camera>();
	RectangleShared r = std::make_shared<Rectangle>(mainWin.getRenderer(), Color(1.0f, 1.0f, 1.0f, 0.5f));
	r->moveTo(10, 10);
	r->resizeTo(100, 100);
	TextShared fpsText = std::make_shared<Text>(mainWin.getRenderer(), Color(1.0f, 1.0f, 1.0f, 0.5f));
	fpsText->setText("FPS: Calc...");
	fpsText->moveTo(0, 0);
	fpsText->resizeTo(100, 20);
	TextShared tickText = std::make_shared<Text>(mainWin.getRenderer(), Color(1.0f, 1.0f, 1.0f, 0.5f));
	tickText->setText("Ticks: Calc...");
	tickText->moveTo(0, 21);
	tickText->resizeTo(100, 20);
	AnimedSpriteShared sprite = std::make_shared<AnimedSprite>(mainWin.getRenderer());
	sprite->loadTexture("resources/Hero.png");
	sprite->resize(32, 32);
	sprite->sourceRect().set(0, 0, 32, 32);
	AliveObj alive1;
	alive1.position() = sprite->rect().origin();
	AnimedSpriteShared sprite2 = std::make_shared<AnimedSprite>(mainWin.getRenderer());
	sprite2->loadTexture("resources/Hero.png");
	sprite2->destRect().set(32, 0, 32, 32);
	sprite2->sourceRect().set(0, 0, 32, 32);
	//Event handler
	SDL_Event e;
	bool quit = false;
	//While application is running
	int curTime;
	int counterTimer = SDL_GetTicks();
	int nextTick = counterTimer;
	int nextFrame = counterTimer;
	int frames = 0;
	int ticks = 0;
	while (!quit)
	{
		curTime = SDL_GetTicks();
		if (nextTick < curTime)
		{
			int delta = curTime - nextTick;
				// Tick skip!!!! :((
			while (nextTick < curTime)
				nextTick += tickInterval;
#ifdef _DEBUG
			if (sprite->subAnimation)
				g_log.logWar("At new logic tick, sprite has "+String(sprite->subAnimation) +"animations not done");
#endif
			while (SDL_PollEvent(&e) != 0)
			{
				switch (e.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					alive1.checkKeyboard(e.key);
					break;
				}
			}
			ticks++;
		}

		if (nextFrame < curTime)
		{
			frames++;
			// Frame skip...
			while (nextFrame < curTime)
				nextFrame += frameInterval;
			if (counterTimer < curTime)
			{
				counterTimer += 1000;
				fpsText->setText("FPS: " + String(frames) + ".");
				tickText->setText("Ticks: " + String(ticks) + ".");
				frames = 0;
				ticks = 0;
			}
			if (sprite->subAnimation)
			{
				if (sprite->subAnimation)
				{
					if (sprite->rect().origin() != alive1.position())
						sprite->rect().origin() += sprite->interSpeed;
				}
				else
					sprite->rect().origin() = alive1.position();
				sprite->subAnimation--;
			}
			SDL_SetRenderDrawColor(mainWin.getRenderer()->getSDLRenderer(), 0, 0, 0, 0x0);
			SDL_RenderClear(mainWin.getRenderer()->getSDLRenderer());
			r->render(cam);
			sprite->render(cam);
			sprite2->render(cam);
			//		r->resize(0.01, 0.01);
			fpsText->render(cam);
			tickText->render(cam);
			//Update screen
			SDL_RenderPresent(mainWin.getRenderer()->getSDLRenderer());
		}
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
