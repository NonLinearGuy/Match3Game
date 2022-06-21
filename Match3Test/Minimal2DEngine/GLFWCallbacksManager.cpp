#include"GLFWCallbacksManager.h"


namespace Minimal2DEngine
{


	void GLFWCallbacksManager::InitCallbacks(Application* pApp)
	{
		mApp = pApp;

		glfwSetKeyCallback(mApp->get_window(), key_callback);

		glfwSetFramebufferSizeCallback(mApp->get_window(), window_resize_callback);

		glfwSetMouseButtonCallback(mApp->get_window(), mouse_button_callback);
		glfwSetCursorPosCallback(mApp->get_window(), cursor_pos_callback);

		glfwSetErrorCallback(error_callback);
	}


	void GLFWCallbacksManager::key_callback(
		GLFWwindow* window,
		int key,
		int scancode,
		int action,
		int mods
	)

	{
		if (mApp) mApp->KeyCallback(window, key, scancode, action, mods);
	}


	void GLFWCallbacksManager::error_callback(
		int error,
		const char* desc
	)

	{
		if (mApp) mApp->ErrorCallback(error, desc);
	}



	void GLFWCallbacksManager::window_resize_callback(
		GLFWwindow* window,
		int width,
		int height
	)

	{
		if (mApp) mApp->WindowResizeCallback(window, width, height);
	}



	void GLFWCallbacksManager::mouse_button_callback(
		GLFWwindow* window,
		int key,
		int action,
		int mods
	)

	{
		if (mApp) mApp->MouseButtonCallback(window, key, action, mods);
	}



	void GLFWCallbacksManager::cursor_pos_callback(
		GLFWwindow* window,
		double xPos,
		double yPos
	)
	{
		if (mApp) mApp->CursorPosCallback(window, xPos, yPos);
	}


	Application* GLFWCallbacksManager::mApp = nullptr;
	

}
