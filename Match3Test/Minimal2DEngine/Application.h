#ifndef INC_SHADY_ENGINE_APPLICATION_H
#define INC_SHADY_ENGINE_APPLICATION_H


//C++ headers
#include<string>


//third party headers
#include<glad/glad.h>
#include<GLFW/glfw3.h>






namespace Minimal2DEngine
{

    class Timer;

	class Application
	{

	protected:

		GLFWwindow *mWindow;
		float mWindowWidth;
		float mWindowHeight;
        Timer* mTimer;

	public:


		Application(
			const std::string& pName,
			int pWindowWidth,
			int pWindowHeight,
			bool pFullScreen
		);

		virtual ~Application();

		void Start();


		//Callbacks
		virtual void KeyCallback(
			GLFWwindow* pWindow, 
			int pKey, 
			int pScancode, 
			int pAction, 
			int pMods
		);

		virtual void ErrorCallback(
			int pError, 
			const char* pDesc
		);

		virtual void WindowResizeCallback(
			GLFWwindow* pWindow, 
			int pWidth, 
			int pHeight
		);

		virtual void MouseButtonCallback(
			GLFWwindow* pWindow, 
			int pKey, 
			int pAction, 
			int pMods
		);

		virtual void CursorPosCallback(
			GLFWwindow* pWindow,
			double pX, 
			double pY
		);

		virtual void Loop() = 0;

		void GLFWLoop();

		inline GLFWwindow* get_window() const
		{
			return mWindow;
		}


	};

}



#endif
