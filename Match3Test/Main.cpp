#include<Minimal2DEngine/GLFWCallbacksManager.h>
#include<Minimal2DEngine/logger.h>
#include<memory>
#include"Game.hpp"
#include"Globals.hpp"

#include<iostream>


using namespace Minimal2DEngine;


int main()
{

    logger::getInstance()->init("Match 3");
    
    std::cout<<"starting game"<<std::endl;
    try {
        std::unique_ptr<Application> app =
            std::make_unique<Game>("Match 3", Globals::WIDTH , Globals::HEIGHT,true);
        std::cout<<"starting app"<<std::endl;
        GLFWCallbacksManager::InitCallbacks(app.get());
        std::cout<<"starting game"<<std::endl;
        app->Start();
    }
    catch (std::runtime_error& e) {
        logger::getInstance()->log(e.what());
    }
    return 0;
}
