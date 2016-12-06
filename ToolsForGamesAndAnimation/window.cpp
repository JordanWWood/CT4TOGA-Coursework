#include "window.h"
#include <iostream>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

Window::Window(int width, int height, int windowTopLeftX, int windowTopLeftY, const std::string& title, HINSTANCE hInstance, int iCmdShow) {
	m_isClosed = false;

	// this bit creates a window class, basically a template for the window we will make later, so we can do more windows the same.
	m_WindowClass.cbClsExtra = 0;											// specifies the amount of extra data that needs to be stored in the window class's class data
	m_WindowClass.cbWndExtra = 0;											// specifies the amount of extra data that needs to be stored with EACH window of the class
	m_WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	    // background fill black
	m_WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);					// arrow cursor       
	m_WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				    // type of icon to use (default app icon)
	m_WindowClass.hInstance = hInstance;									// window instance name (given by the OS when the window is created)   
	m_WindowClass.lpfnWndProc = WndProc;									// window callback function - this is our function below that is called whenever something happens
	m_WindowClass.lpszClassName = TEXT("my window class name");				// our new window class name
	m_WindowClass.lpszMenuName = 0;											// window menu name (0 = default menu?) 
	m_WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;				// redraw if the window is resized horizontally or vertically, allow different context for each window instance

	// Register that class with the Windows OS..
	RegisterClass(&m_WindowClass);

	// create a rect structure to hold the dimensions of our window
	RECT rect;
	SetRect(&rect, windowTopLeftX,				// the top-left corner x-coordinate
		windowTopLeftY,				            // the top-left corner y-coordinate
		windowTopLeftX + width,		            // far right
		windowTopLeftY + height);	            // far left

									// adjust the window, no idea why.
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// call CreateWindow to create the window
	m_Window = CreateWindow(TEXT("my window class name"),		// window class to use - in this case the one we created a minute ago
		TEXT(title.c_str()),		                            // window title
		WS_OVERLAPPEDWINDOW,						            // ??
		windowTopLeftX, windowTopLeftY,			                // x, y
		width, height,				                            // width and height
		NULL, NULL,								                // ??
		hInstance, NULL);							            // ??

	if (m_Window == NULL)
	{
		FatalAppExit(NULL, TEXT("CreateWindow() failed!")); // ch16
	}

	ShowWindow(m_Window, iCmdShow);

	// get a device context from the window
	m_DeviceContext = GetDC(m_Window);

	// we create a pixel format descriptor, to describe our desired pixel format. 
	// we set all of the fields to 0 before we do anything else
	// this is because PIXELFORMATDESCRIPTOR has loads of fields that we won't use
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor = { 0 };

	// now set only the fields of the pfd we care about:
	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);		// size of the pfd in memory
	pixelFormatDescriptor.nVersion = 1;									// always 1

	pixelFormatDescriptor.dwFlags = PFD_SUPPORT_OPENGL |				// OpenGL support - not DirectDraw
		PFD_DOUBLEBUFFER |				                                // double buffering support
		PFD_DRAW_TO_WINDOW;					                            // draw to the app window, not to a bitmap image

	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;					// red, green, blue, alpha for each pixel
	pixelFormatDescriptor.cColorBits = 24;								// 24 bit == 8 bits for red, 8 for green, 8 for blue.
																		// This count of color bits EXCLUDES alpha.

	pixelFormatDescriptor.cDepthBits = 32;								// 32 bits to measure pixel depth.

																		// now we need to choose the closest pixel format to the one we wanted...	
	int chosenPixelFormat = ChoosePixelFormat(m_DeviceContext, &pixelFormatDescriptor);

	// if windows didnt have a suitable format, 0 would have been returned...
	if (chosenPixelFormat == 0)
	{
		FatalAppExit(NULL, TEXT("ChoosePixelFormat() failed!"));
	}

	// if we get this far it means we've got a valid pixel format
	// so now we need to set the device context up with that format...
	int result = SetPixelFormat(m_DeviceContext, chosenPixelFormat, &pixelFormatDescriptor);

	// if it failed...
	if (result == NULL)
	{
		FatalAppExit(NULL, TEXT("SetPixelFormat() failed!"));
	}

	// we now need to set up a render context (for opengl) that is compatible with the device context (from windows)...
	m_RenderContext = wglCreateContext(m_DeviceContext);

	// then we connect the two together
	wglMakeCurrent(m_DeviceContext, m_RenderContext);

	GLenum status = glewInit();

	if (status != GLEW_OK)
		std::cerr << "Glew failed to initialize" << std::endl;

	// opengl display setup
	glMatrixMode(GL_PROJECTION);	// select the projection matrix, i.e. the one that controls the "camera"
	glLoadIdentity();				// reset it
	gluPerspective(45.0, (float)width / (float)height, 0.1, 1000);	// set up fov, and near / far clipping planes
	glViewport(0, 0, width, height);								// make the viewport cover the whole window
	glClearColor(0.5, 0, 0.5, 1.0);												// set the colour used for clearing the screen
	glEnableClientState(GL_VERTEX_ARRAY);										//	turn on the ability to do vertex arrays

}

Window::~Window() {
	wglMakeCurrent(NULL, NULL);

	// delete the rendering context, we no longer need it.
	wglDeleteContext(m_RenderContext);

	// release our window's DC from the window
	ReleaseDC(m_Window, m_DeviceContext);

	m_msg.wParam;
}

bool Window::isClosed() {
	return m_isClosed;
}

void Window::Update() {
	// we need to listen out for OS messages.
	// if there is a windows message to process...
	if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
	{
		// and if the message is a "quit" message...
		if (m_msg.message == WM_QUIT)
		{
			m_isClosed = true;	// we want to quit asap
		}
		// or if it was any other type of message (i.e. one we don't care about), process it as normal...
		else
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear screen
	SwapBuffers(m_DeviceContext);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{

	switch (message)
	{
		// if they exited the window...	
	case WM_DESTROY:
		// post a message "quit" message to the main windows loop
		PostQuitMessage(0);
		return 0;
		break;
	}

	// must do this as a default case (i.e. if no other event was handled)...
	return DefWindowProc(hwnd, message, wparam, lparam);
}

WNDCLASS Window::getWindowClass() {
	return m_WindowClass;
}

HWND Window::getWindow() {
	return m_Window;
}

HDC Window::getDeviceContext() {
	return m_DeviceContext;
}

HGLRC Window::getRenderContext() {
	return m_RenderContext;
}