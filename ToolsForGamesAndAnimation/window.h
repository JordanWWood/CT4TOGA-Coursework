#pragma once
#define DISPLAY_H

#include <string>
#include <Windows.h>
#include <GL/glew.h>

class Window {
public:
	Window(int width, int height, int windowTopLeftX, int windowTopLeftY, const std::string& title, HINSTANCE hInstance, int iCmdShow);

	void Update();
	bool isClosed();
	void Clear(float r, float g, float b, float a);

	virtual ~Window();

	// Getters
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