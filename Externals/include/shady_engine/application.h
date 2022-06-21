#ifndef INC_SHADY_ENGINE_APPLICATION_H
#define INC_SHADY_ENGINE_APPLICATION_H


//C++ headers
#include<string>


//third party headers
#include<glad/glad.h>
#include<GLFW/glfw3.h>




namespace shady_engine
{


	class application
	{

	protected:

		GLFWwindow *mWindow;
		float mWindowWidth;
		float mWindowHeight;

	public:


		application(
			const std::string& pName,
			int pWindowWidth,
			int pWindowHeight,
			bool pFullScreen
		);

		virtual ~application();

		void start();


		//Callbacks
		virtual void key_callback(
			GLFWwindow* pWindow, 
			int pKey, 
			int pScancode, 
			int pAction, 
			int pMods
		);

		virtual void error_callback(
			int pError, 
			const char* pDesc
		);

		virtual void window_resize_callback(
			GLFWwindow* pWindow, 
			int pWidth, 
			int pHeight
		);

		virtual void mouse_button_callback(
			GLFWwindow* pWindow, 
			int pKey, 
			int pAction, 
			int pMods
		);

		virtual void cursor_pos_callback(
			GLFWwindow* pWindow,
			double pX, 
			double pY
		);

		virtual void loop() = 0;

		void glfw_loop();

		inline GLFWwindow* get_window() const
		{
			return mWindow;
		}


	};

}



#endif
