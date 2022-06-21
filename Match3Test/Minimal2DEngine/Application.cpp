#include"Application.h"

#include<iostream>

//shady_engine headers
#include"Debugger.h"
#include"Logger.h"
#include "Timer.h"

namespace Minimal2DEngine
{


	Application::Application(
		const std::string& pName,
		int pWindowWidth,
		int pWindowHeight,
		bool pFullScreen
	)
		:

		mWindowWidth(pWindowWidth),
		mWindowHeight(pWindowHeight)
	{

            // glfw: initialize and configure
                // ------------------------------
                glfwInit();
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            #ifdef __APPLE__
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif

                // glfw window creation
                // --------------------
                GLFWwindow* window = glfwCreateWindow(mWindowWidth, mWindowHeight, "Match 3 Demo", NULL, NULL);
                if (window == NULL)
                {
                    std::cout << "Failed to create GLFW window" << std::endl;
                    glfwTerminate();
                    return;
                }
                glfwMakeContextCurrent(window);
                glfwSetFramebufferSizeCallback(window, nullptr);
        
        this->mWindow = window;

                // glad: load all OpenGL function pointers
                // ---------------------------------------
                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                {
                    std::cout << "Failed to initialize GLAD" << std::endl;
                    return ;
                }
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        mTimer = new Timer();
	}



	Application::~Application()
	{
        glfwDestroyWindow(mWindow);
		glfwTerminate();
	}


	void Application::Start()
	{
        std::cout<<"staring loop"<<std::endl;
		this->GLFWLoop();
	}


	void Application::GLFWLoop()
	{

		while (!glfwWindowShouldClose(mWindow))
		{
			glfwPollEvents();
			//calling custom loop
            mTimer->Update();
            
			this->Loop();

			glfwSwapBuffers(mWindow);

		}
	}



	//Callbacks
	void Application::KeyCallback(
		GLFWwindow* pWindow,
		int pKey,
		int pScancode,
		int pAction,
		int pMods
	) {}



	void Application::ErrorCallback(
		int pError,
		const char* pDesc
	) {}



	void Application::WindowResizeCallback(
		GLFWwindow* pWindow,
		int pWidth,
		int pHeight
	) {}



	void Application::MouseButtonCallback(
		GLFWwindow* pWindow,
		int pKey,
		int pAction,
		int pMods
	) {}



	void Application::CursorPosCallback(
		GLFWwindow* pWindow,
		double pX,
		double pY
	) {}



}
