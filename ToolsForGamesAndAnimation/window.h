#pragma once
#define DISPLAY_H


#include <windows.h>
#include <string>
#include <GL/GLU.h>
#include <GL/GL.h>


#undef main

class Window {
public:
	Window(int width, int height, int windowTopLeftX, int windowTopLeftY, const std::string& title, HINSTANCE hInstance, int iCmdShow);

	void Update();
	bool isClosed();

	virtual ~Window();
protected:
private:
	Window(const Window& other) {}

	/*SDL_Window* m_window;

	SDL_GLContext m_glContext;*/
	bool m_isClosed;

	// -----------------------------
	// Windows
	// -----------------------------

	MSG m_msg;

	WNDCLASS m_winWindowClass;
	HWND m_winWindow;

	HDC m_DeviceContext;
	HGLRC m_RenderContext;
};