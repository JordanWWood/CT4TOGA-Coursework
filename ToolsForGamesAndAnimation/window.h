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

	WNDCLASS getWindowClass();
	HWND getWindow();
	HDC getDeviceContext();
	HGLRC getRenderContext();
protected:
private:
	Window(const Window& other) {}
	bool m_isClosed;

	MSG m_msg;

	WNDCLASS m_WindowClass;
	HWND m_Window;

	HDC m_DeviceContext;
	HGLRC m_RenderContext;
};