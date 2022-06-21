#ifndef INC_SHADY_ENGINE_APPLICATION_MANAGER_H
#define INC_SHADY_ENGINE_APPLICATION_MANAGER_H



//C++ headers
#include<memory>

//engine headers
#include"application.h"



namespace shady_engine
{


	class app_manager
	{


		static application* mApp;


		static void key_callback(
			GLFWwindow* window,
			int key,
			int scancode,
			int action,
			int mods
		);


		static void error_callback(
			int error,
			const char* desc
		);



		static void window_resize_callback(
			GLFWwindow* window,
			int width,
			int height
		);



		static void mouse_button_callback(
			GLFWwindow* window,
			int key,
			int action,
			int mods
		);



		static void cursor_pos_callback(
			GLFWwindow* window,
			double xPos,
			double yPos
		);

	public:


		static void start_app(application* pApp);

	};

} //End of namespace


#endif