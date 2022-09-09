#include <SDL.h>
#include "Input.h"

//======================================================================================================
Input* Input::Instance()
{
	static Input* inputObject = new Input();
	return inputObject;
}
//======================================================================================================
char Input::GetKey() const
{
	return key;
}
//======================================================================================================
int Input::GetMouseWheel() const
{
	return mouseWheel;
}
//======================================================================================================
const SDL_Point& Input::GetMouseMotion() const
{
	return mouseMotion;
}
//======================================================================================================
const SDL_Point& Input::GetMousePosition() const
{
	return mousePosition;
}
//======================================================================================================
void Input::SetCursorState(bool isCursorEnabled, bool isCursorVisible)
{
	SDL_ShowCursor(static_cast<int>(isCursorVisible));
	SDL_SetRelativeMouseMode(static_cast<SDL_bool>(isCursorEnabled));
}
//======================================================================================================
bool Input::IsWindowClosed() const
{
	return isWindowClosed;
}
//======================================================================================================
bool Input::IsKeyPressed() const
{
	return isKeyPressed;
}
//======================================================================================================
bool Input::IsKeyPressed(int keyCode) const
{
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
	return keyStates[keyCode];
}
//======================================================================================================
bool Input::IsModifierPressed(int modifier_1, int modifier_2) const
{
	return modifier == (modifier_1 | modifier_2);
}
//======================================================================================================
bool Input::IsMouseClicked() const
{
	return isMouseClicked;
}
//======================================================================================================
bool Input::IsMouseClicked(int mouseButton_1, int mouseButton_2) const
{
	return mouseButton == (mouseButton_1 | mouseButton_2);
}
//======================================================================================================
void Input::Update()
{
	SDL_Event events;

	mouseWheel = 0;
	mouseMotion.x = 0;
	mouseMotion.y = 0;
	isWindowClosed = false;

	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_QUIT:
		{
			isWindowClosed = true;
			break;
		}

		case SDL_KEYUP:
		{
			isKeyPressed = false;
			key = SDLK_UNKNOWN;
			modifier = events.key.keysym.mod;
			break;
		}

		case SDL_KEYDOWN:
		{
			isKeyPressed = true;
			key = events.key.keysym.sym;
			modifier |= events.key.keysym.mod;
			break;
		}

		case SDL_MOUSEMOTION:
		{
			mousePosition.x = events.motion.x;
			mousePosition.y = events.motion.y;

			mouseMotion.x = events.motion.xrel;
			mouseMotion.y = events.motion.yrel;
			break;
		}

		case SDL_MOUSEWHEEL:
		{
			mouseWheel = events.wheel.y;
			break;
		}

		case SDL_MOUSEBUTTONUP:
		{
			isMouseClicked = false;
			mousePosition.x = events.motion.x;
			mousePosition.y = events.motion.y;

			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT: { mouseButton ^= HM_MOUSE_LEFT; break;   }
			case SDL_BUTTON_MIDDLE: { mouseButton ^= HM_MOUSE_MIDDLE; break; }
			case SDL_BUTTON_RIGHT: { mouseButton ^= HM_MOUSE_RIGHT; break;  }
			}

			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			isMouseClicked = true;
			mousePosition.x = events.motion.x;
			mousePosition.y = events.motion.y;

			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT: { mouseButton |= HM_MOUSE_LEFT; break;   }
			case SDL_BUTTON_MIDDLE: { mouseButton |= HM_MOUSE_MIDDLE; break; }
			case SDL_BUTTON_RIGHT: { mouseButton |= HM_MOUSE_RIGHT; break;  }
			}

			break;
		}

		}
	}
}