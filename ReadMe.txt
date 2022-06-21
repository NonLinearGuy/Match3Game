

#INTRODUCTION

This game made on top of my custom C++ OpenGL game engine. I took my old 2D engine code and removed all the things which I didn't need and used it for this project. 
In the process I renamed it as "Minimal2DEngine". 

OLD 2D GAME ENGINE REPO WHICH I RE-USED : https://github.com/NonLinearGuy/Shady-Snake/tree/master/src/Shady%20Snake/Shady%20Snake/shadyengine

LINK TO PRIVATE GAMEPLAY VIDEO : https://1drv.ms/v/s!Agaw851qJHw4uyPFEOvwqS7HTBik?e=Nxyk9f



# TOOLS I USED FOR THIS PROJECT

- XCode Version 13.1 

- I am working on Apple Silicon

- Earlier my engine was using Irrklang library Sound Library But that library do not have dylib files for Mac OS. I wrote tiny objective C class which uses NSound class to play Sound effects.

- SOIL image library for texture loading. I am using its source code directly as its static library was corrupted.



#FEATURES I WAS ABLE TO FINISH BASED ON REQUIREMENTS

1. Rendering 8x8 grid with single draw call using hardware instancing. It made it easier to achieve good frame rate.

2. Swapping gems by dragging and selecting with mouse. Gems will move back to their original position if there's no match.

3. Resolving matches in grid and removing gems.

4. Re-filling empty slots



#EXTRA GAMEPLAY FEATURES I ADDED (WHICH WERE NOT REQUIRED FOR THE TEST)

1. Blockers can be added in the grid and gems will avoid blockers and fill empty slots in grid when re-filling takes place. this adds extra challenge when looking for matches and fun to the game.

2. Hint system is added which will show player the potential match after 5 seconds. The time can be changed.



# DIRECTORY AND CODE STRUCTURE.

There are four directories you will see when you will open this project in XCode. 

- Resources : It contains assets for the game such as shaders for text & sprite rendering,sounds, textures and font files. 

- Externals : This contains third party header files and libraries. SOIL, GLAD (opengl extensions manager) and GLFW.

- Match3Test : This folder contains all the game specific source code. You will find following sub folders here, 

				1. GameplayLogic : As the name suggests, this folder alone should be enough to review the test. Here are the key classes : 

				        A. Game.cpp => Loads assets, setup renderers and projection-view matrix of the game. It also manages the game states. I will explain the game states below. This class receives input and other events from Application.h which is part of game engine.

				        B. GridController.cpp => This is central system of our game. It sets up instancing renderer which renders the grid fast. It also has methods for game states to show/hide visible elements. 

				        C. GameStates folder => I broke down design requirements of the game as states. Everything in the game happens sequentially. I added an interface called IState which other states will implement. Following are other states which Implements IState, 

				                    - FillEmptySlotsState : Determines which slots are empty and needs to be refilled. It also manages spawning new gems if requirements comes.
				                    - MatchResolutionState : Checks if there are matching pairs of 3 in the grid and removes them with burst effect
				                    - MouseInputState.cpp : This is responsible for dragging and selection of gems and swapping them.
				                    - HintState : This is managed by MouseInputState.cpp. It waits for 5 seconds and show potential matches to the player.

				            This states are extendable. I can add more steps to the game. I can extend IState to run child states. Ideally it should be called Tasks not states. You will see I am managing HintState within MouseInputState. Which are basically two tasks are running together. State machines can have only one state at a time If I am not wrong. 



                2. Minimal2DEngine : This is my custom opengl engine which I used. It has classes to load textures and shaders. It also responsible for rendering
                and providing input and other events to the Game.cpp. 

                3. ExtendableHelperClasses : This contains parent classes which Gem and Burst effect will inherit from. Classes are GameEntity and SpriteSheetEntity.




 #OBJECT POOLING

 - I added a class called EntityPool. Which creates a pool of Gems and Burst effects. 
   This helps to significantly minimise memory allocations during updates and gameplay.



# C++ HIGHLIGHTS

- I used Lambdas expressions, constexpr and for range loops.
- I heavily used shared_pointer and I don't regret it.
- I tried my best to maintain constantness in classes 



#TO-DO

- Re-name IState class as ITask and improve it such that multiple tasks can run simulatneously

- I would like to make this cross platform for windows, mac os and linux.

- Hide engine code and implementation so that user can focus on gameplay logic 



#FREE ASSETS I USED

- I used royality free asset pack for match 3. Here's the link, https://free-game-assets.itch.io/free-match-3-game-assets. I didn't use the gem which was provided with 
the test

