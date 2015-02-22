#include "RissagaClient/source/utils/math.h"

#include "SDL2/include/SDL_events.h"

namespace Ris
{
	struct State
	{
	public:
		enum StateID
		{
			NoState = 0,	// Internal use. Stands for "nochange" when returned on handleXXX functions.
			Standing,
			Ducking,
			Walking,
			Laying
		};
		StateID ID;
		State(StateID stateID) : ID(stateID)
		{ }
		virtual StateID checkKeyboard(const SDL_KeyboardEvent &key) = 0;
		virtual StateID stateID() const { return ID; }
		virtual void onEnter(const SDL_KeyboardEvent &key) = 0;
		virtual void onExit() = 0;
	};
	struct StateOnGround : public State
	{
		StateOnGround(State::StateID id) : State(id)
		{ }
		virtual void onEnter(const SDL_KeyboardEvent &key)
		{

		}
		virtual void onExit()
		{

		}
	};
	struct StateStand : public StateOnGround
	{
		StateStand() : StateOnGround(State::Standing)
		{ }
		virtual StateID checkKeyboard(const SDL_KeyboardEvent &key)
		{
			if (key.state == SDL_PRESSED)
			{
				switch (key.keysym.sym)
				{
				case SDLK_UP:
				case SDLK_DOWN:
				case SDLK_RIGHT:
				case SDLK_LEFT:
					return State::Walking;
				}
			}
			return State::NoState;
		}
		virtual void onEnter(const SDL_KeyboardEvent &key)
		{

		}
	};
	class AnimedSprite;
	class AliveObjects;
	struct StateWalking : public StateOnGround
	{
		enum Direction
		{
			NoDir = 0,
			North,
			South,
			East,
			West
		};
		Direction direction;
		AliveObjects *obj;
		AnimedSprite *spr;
		void checkKeyboardDown(const SDL_Keycode &key)
		{
			switch (key)
			{
			case SDLK_UP:
				direction |= North;
				break;
			case SDLK_DOWN:
				direction |= South;
				break;
			case SDLK_RIGHT:
				direction |= East;
				break;
			case SDLK_LEFT:
				direction |= West;
				break;
			}
		}
	public:
		StateWalking() : StateOnGround(State::Walking)
		{ }
		virtual void onEnter(const SDL_KeyboardEvent &key)
		{
			// Clear data.
			direction = NoDir;

			checkKeyboardDown(key.keysym.sym);
		}
		virtual State::StateID checkKeyboard(const SDL_KeyboardEvent &key)
		{
			if (key.state == SDL_RELEASED)
			{
				switch (key.keysym.sym)
				{
				case SDLK_UP:
				case SDLK_DOWN:
				case SDLK_RIGHT:
				case SDLK_LEFT:
					return State::Standing;
				}
			}
			else
				checkKeyboardDown(key.keysym.sym);
			return State::NoState;
		}
	};
}
