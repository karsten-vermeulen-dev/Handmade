#pragma once
#include <Windows.h>
#include <string>
#include <SDL.h>

class Screen
{

public:

	static Screen* Instance();

	HWND GetWindowHandle();
	SDL_Window* GetWindow();
	SDL_Point GetResolution();
	SDL_Renderer* GetRenderer();

	void SetMousePosition(int x, int y);
	void SetClearColor(Uint8 r, Uint8 g, Uint8 b);

	bool Initialize(const std::string& windowTitle,
		int width = 1024,
		int height = 768,
		bool fullscreen = false);

	void Clear();
	void Present();
	void Shutdown();

private:

	Screen() {}
	Screen(const Screen&);
	Screen& operator=(const Screen&);

	int width{ 0 };
	int height{ 0 };

	HWND windowHandle{ nullptr };
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

};