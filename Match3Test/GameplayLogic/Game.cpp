//Declaration header
#include"Game.hpp"

//C++ headers
#include<iostream>


//Engine headers
#include<Minimal2DEngine/AssetManager.h>
#include <Minimal2DEngine/SpriteRenderer.h>
#include <Minimal2DEngine/TextRenderer.h>
#include <Minimal2DEngine/Timer.h>
#include<Minimal2DEngine/Timer.h>
#include<Minimal2DEngine/random.h>



#include "GridController.hpp"
#include "GameStates/MouseInputState.hpp"
#include "GameStates/FillEmptySlotsState.hpp"
#include "GameEntitiesRenderer.hpp"

#include "../SoundController.h"


//Exposing namespaces
using namespace Minimal2DEngine;
using namespace std;


void Game::LoadAssets(){
    AssetManager::GetInstance()->load_texture("font texture", "Resources/bitmap fonts/Consolas.png", GL_RGBA);
    AssetManager::GetInstance()->load_texture("bg", "Resources/sprites/bg.png", GL_RGBA);
    AssetManager::GetInstance()->load_texture("selection", "Resources/sprites/selected.png", GL_RGBA);
    AssetManager::GetInstance()->load_texture("slot", "Resources/sprites/gem_bg.png", GL_RGBA);
    AssetManager::GetInstance()->load_texture("block", "Resources/sprites/stone.png", GL_RGBA);
    AssetManager::GetInstance()->load_texture("gem1", "Resources/sprites/3.png", GL_RGBA);
    AssetManager::GetInstance()->load_texture("gem2", "Resources/sprites/5.png", GL_RGBA);
    AssetManager::GetInstance()->load_texture("gem3", "Resources/sprites/7.png", GL_RGBA);
    AssetManager::GetInstance()->load_texture("gem4", "Resources/sprites/14.png", GL_RGBA);
    AssetManager::GetInstance()->load_texture("gem5", "Resources/sprites/17.png", GL_RGBA);
    AssetManager::GetInstance()->load_texture("burst", "Resources/sprites/burst_sprite_sheet.png", GL_RGBA);
    AssetManager::GetInstance()->load_texture("hint", "Resources/sprites/hint_bg.png", GL_RGBA);
    
    //Forcefully creating instances of NSSound
    SoundController::GetInstance()->GetInstance();
    
}

void Game::SetupRenderers(){
    mSpriteRenderer = std::make_shared<SpriteRenderer>(mGameProjection,mCamera->getView());
    mTextRenderer = std::make_shared<TextRenderer>(mGameProjection,mCamera->getView(),
        AssetManager::GetInstance()->GetTexture("font texture"),
        "Resources/Bitmap Fonts/Consolas.fnt"
        );
}

void Game::InitGameplay(){
    mGridController = std::make_shared<GridController>(mSpriteRenderer,mTextRenderer);
    auto fillEmptySlotsState = std::make_shared<FillEmptySlotsState>(mGridController);
    mCurrentState = fillEmptySlotsState;
    mCurrentState->Execute();
}

//Constructor
Game::Game(const std::string& name,int windowWidth,int windowHeight,bool fullScreen):
	Application(name,windowWidth,windowHeight,fullScreen)
{

    mGameProjection = glm::ortho(0.0f, float(Globals::WIDTH), float(Globals::HEIGHT), 0.0f);
    mCamera = new Camera(glm::vec2(0,0));
    
    LoadAssets();
    SetupRenderers();
    InitGameplay();

}

void Game::destroy()
{
    printf("Game instance destroyed!");
}

void Game::reset()
{

	
}

void Game::KeyCallback(GLFWwindow* window,int key,int scancode,int action,int mods)
{

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	if (action == GLFW_RELEASE)
		keys[key] = false;
    
    //Uncomment this line to have control to switch state by pressing N key for debugging
    if(key == GLFW_KEY_N && action == GLFW_PRESS){
//        if(mCurrentState->IsDone()){
//            mCurrentState = mCurrentState->GetNextState();
//            mCurrentState->Execute();
//        }
    }
    

}

void Game::DoMovements()
{

}

void Game::WindowResizeCallback(
	GLFWwindow* window,
	int width,
	int height
)
{
	//glViewport(0, 0, width, height);
}



void Game::MouseButtonCallback(
	GLFWwindow* window,
	int key,
	int action,
	int mods
)

{
    if(mCurrentState->GetState() != EGameState::MOUSE_INPUT_STATE) return;
    auto mouseInputState = std::static_pointer_cast<MouseInputState>(mCurrentState);
    if(key == GLFW_MOUSE_BUTTON_LEFT){
        if(action == GLFW_PRESS)
            mouseInputState->onMouseDown(mLastCursorPos);
        else
            mouseInputState->onMouseUp(mLastCursorPos);
    }
    
}



void Game::CursorPosCallback(
	GLFWwindow* window,
	double xPos,
	double yPos
)

{
    mLastCursorPos.x = xPos;
    mLastCursorPos.y = yPos;
}



Game::~Game()
{

}



void Game::Loop()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	DoMovements();
	Tick();
	Render();
}

void Game::Tick()
{
    float dt = mTimer->GetDeltaTime();
    mGridController->Update(dt);
    mCurrentState->Update(dt);
    if(mCurrentState->IsDone()){
        mCurrentState = mCurrentState->GetNextState();
        mCurrentState->Execute();
    }
}

void Game::Render()
{
    auto bg = AssetManager::GetInstance()->GetTexture("bg");
    mSpriteRenderer->DrawImage( bg, glm::vec2(0,0), glm::vec2(1024,768), 0);
    mGridController->Render();
    const char* str = "FPS = %d";
    mTextRenderer->Text(glm::vec2(Globals::WIDTH/2,13), 20, glm::vec3(1.0,0.4,1.0), str,mTimer->GetFPS(),mCurrentState->GetState());
   
}
