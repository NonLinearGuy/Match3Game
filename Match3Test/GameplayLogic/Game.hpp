#ifndef INC_GRID_CONTROLLER_H
#define INC_GRID_CONTROLLER_H

    //
    //  GridController.hpp
    //  Match3Test
    //
    //  Created by Ankit Singh Kushwah on 01/05/22.
    //


//Parent class
#include<Minimal2DEngine/Application.h>

//C++ headers
#include<vector>
#include<list>


//Third party headers
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"Globals.hpp"
#include"Camera.hpp"

namespace Minimal2DEngine{
    class SpriteRenderer;
    class TextRenderer;
    class Timer;
}

class GridController;
class IState;


//states
//class IState;
class MouseInputState;

class Game : public Minimal2DEngine::Application
{
	bool keys[1024];
    
    glm::mat4 mGameProjection;
    Camera *mCamera;
    
    //Renderers which will be shared with other system
    std::shared_ptr<Minimal2DEngine::SpriteRenderer> mSpriteRenderer;
    std::shared_ptr<Minimal2DEngine::TextRenderer> mTextRenderer;
  
    //Gameplay Logic
    std::shared_ptr<GridController> mGridController;
    std::shared_ptr<IState> mCurrentState;
    
    //Mouse Inputs
    glm::vec2 mLastCursorPos;
	
    //Methods
    
    void LoadAssets();
    void SetupRenderers();
    void InitGameplay();
    

public:
	
	Game(const std::string& name,int windowWidth,int windowHeight,bool fullScreen);
    void destroy();
	void reset();
    
	~Game();


	void KeyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) override;
    void WindowResizeCallback(GLFWwindow* window,int width,int height) override;
    void MouseButtonCallback(GLFWwindow* window,int key,int action,int mods) override;
    void CursorPosCallback(GLFWwindow* window,double xPos,double yPos)override;

	void Loop() override;
	
	void DoMovements();
	void Tick();
	void Render();
};


#endif
