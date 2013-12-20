#include "GameApplication.h"

//should really check to see if we are on a windows platform
#include "../Window/Win32Window.h"
#include "../D3D10Renderer/D3D10Renderer.h"
#include "GameObject.h"
#include "Timer.h"

//boost header for program options
//#include <boost/program_options.hpp>
#include <fstream> 
using namespace std;
//namespace po = boost::program_options;

//Constructor
CGameApplication::CGameApplication(void)
{
        //Set to NULL
        m_pWindow=NULL;
        //Set to NULL
        m_pRenderer=NULL;
        //Set the Window name to GP2
        m_GameOptionDesc.gameName=TEXT("GP2");
        //Window Height and Width
        m_GameOptionDesc.width=640;
        m_GameOptionDesc.height=480;
        //Full screen
        m_GameOptionDesc.fullscreen=false;
        //Config options
        m_ConfigFileName=TEXT("game.cfg");
        m_pMainCamera=NULL;
		debug = false;
}

//Desconstructor
CGameApplication::~CGameApplication(void)
{
        clearObjectList();
        //Delete things in reverse order
        if (m_pRenderer)
        {
                delete m_pRenderer;
                m_pRenderer=NULL;
        }
        if (m_pWindow)
        {
                delete m_pWindow;
                m_pWindow=NULL;
        }
}

//Init
//This initialises all subsystems
bool CGameApplication::init()
{
        if(!parseConfigFile())
                return false;
        if (!initWindow())
                return false;
        if (!initGraphics())
                return false;
        if (!initInput())
                return false;
        if (!initGame())
                return false;
        return true;
}

//called to parse the config file
bool CGameApplication::parseConfigFile()
{

        return true;
}

//initInput - Initialises the input
bool CGameApplication::initInput()
{
        return true;
}

//initPhysics - Initialises the physics system
bool CGameApplication::initPhysics()
{
        return true;
}

//initGraphics - initialise the graphics subsystem
bool CGameApplication::initGraphics()
{
        //check our settings first, to see what graphics mode we are in
        m_pRenderer=new D3D10Renderer();
        if (!m_pRenderer->init(m_pWindow->getHandleToWindow(),m_GameOptionDesc.fullscreen))
                return false;

        return true;
}

//initWindow - initialise the window
bool CGameApplication::initWindow()
{
        //Create a Win32 Window
        m_pWindow=new CWin32Window();
        m_pWindow->init(m_GameOptionDesc.gameName,m_GameOptionDesc.width,m_GameOptionDesc.height,m_GameOptionDesc.fullscreen);
        return true;
}



//called to init the game
bool CGameApplication::initGame()
{

        return true;
}

//Called to put the game in a loop(aka game loop)
void CGameApplication::run()
{
        //while the window is not closed
        while(m_pWindow->running())
        {
                //check for all windows messages
                m_pWindow->checkForWindowMessages();
				//Get inputs from window
				inKey = m_pWindow->getInput();
				//update Player position
				currentPos = m_pPlayer->checkPos();
                //update
                update();
                //render
                render();
        }
}

//Render, called to draw one frame of the game
void CGameApplication::render()
{
        if (m_pMainCamera)
                {
                        D3D10Renderer * pD3D10Renderer=static_cast<D3D10Renderer*>(m_pRenderer);
                        pD3D10Renderer->setProjection(m_pMainCamera->getProjection());
                        pD3D10Renderer->setView(m_pMainCamera->getView());
        }
        for(GameObjectIter iter=m_GameObjectList.begin();iter!=m_GameObjectList.end();++iter)
        {
                m_pRenderer->addToRenderQueue((*iter));
        }
		//sets the background colour
        m_pRenderer->clear(0.0f,0.0f,0.5f,1.0f);
        m_pRenderer->render();
        m_pRenderer->present();
}

//Update, called to update the game
void CGameApplication::update()
{
		//Delta time, time elapsed since last frame
		float dt =  ((float) clock() - lastUpdate)/CLOCKS_PER_SEC;
		//Total time the program has been running
		totalTime = totalTime - dt;
        for(GameObjectIter iter=m_GameObjectList.begin();iter!=m_GameObjectList.end();iter++)
        {
                (*iter)->update();

        }
		//Stores the time at current frame
		lastUpdate = clock();
		//Update componenets with delta time
		m_pPlayer->update(dt);
		m_pLight->update(dt);
		//Input's for player and debug camera
		if(inKey=="w")
		{
			attemptDir = 1; //Up Player
			debugMove = 1;
		}
		if(inKey=="s")
		{
			attemptDir = 3; //Down Player
			debugMove = 3;
		}
		if(inKey=="a")
		{
			attemptDir = 4; //Left Player
			debugMove = 4;
		}
		if(inKey=="d")
		{
			attemptDir = 2; //Right Player
			debugMove = 2;
		}
		if(inKey=="q")
		{
			debugMove = 5;
		}
		if(inKey=="e")
		{
			debugMove = 6;
		}
		if(inKey=="f")
			//Pause or continue audio
			m_pAudio->pauseSound(); 
		if(inKey=="t")
		{
			if(!debug)
				debug=true;
			else
				debug=false;
		}

		//Check Player for pickups
		if(gridSpot[currentPos]==0 || gridSpot[currentPos]==2 || gridSpot[currentPos]==3){
			//Iterate though gameobjects and delete the cup the player is standing on
			GameObjectIter iter=m_GameObjectList.begin();
			while(iter!=m_GameObjectList.end())
			{
				if(*iter==pickup[currentPos]){
					delete (*iter);
					iter=m_GameObjectList.erase(iter);
                }
                else
                {
					++iter;
                }
			}
			//Set the grid spot to an empty space, denoted by 4
			gridSpot[currentPos] = 4;
			//Increase the score
			if(gridSpot[currentPos]==0)
				score++;
			if(gridSpot[currentPos]==2)
				score+=5;
			if(gridSpot[currentPos]==3)
				score+=50;
		}
		//checks if we are in debug mode
		if(!debug)
		{
			// Returns the camera to its original position after exiting debug mode
			m_pMainCamera->setLook(8.0f,1.5f,9.75f);
			m_pMainCamera->getOwner()->getTransform().setPosition(8.0f,21.0f,9.0f);
			//Checks grid for collisons
			if(attemptDir == 1)
			{
				//Check if there is a wall above
				if(gridSpot[currentPos-17]!=1){
					//Move up, set colliding with walls to false
					m_pPlayer->SetMoveDirection(1);
					collision = false;
				}
				else{
					//If hitting a wall, stop moving
					m_pPlayer->SetMoveDirection(0);
					//If you weren't hitting a wall but are now, play hitting wall sound
					if(collision == false)
						m_pSoundEffect->playSound(L"Sounds\\thud.wav",false);
					//Now hitting a wall
					collision = true;
				}
			}
			if(attemptDir == 3)
			{
				//Check if there is a wall below
				if(gridSpot[currentPos+17]!=1){
					//Move down, set colliding with walls to false
					m_pPlayer->SetMoveDirection(3);
					collision = false;
				}
				else{
					//If hitting a wall, stop moving
					m_pPlayer->SetMoveDirection(0);
					//If you weren't hitting a wall but are now, play hitting wall sound
					if(collision == false)
						m_pSoundEffect->playSound(L"Sounds\\thud.wav",false);
					//Now hitting a wall
					collision = true;
				}
			}
			if(attemptDir == 4)
			{
				//Check if there is a wall left
				if(gridSpot[currentPos-1]!=1){
					//Move left, set colliding with walls to false
					m_pPlayer->SetMoveDirection(4);
					collision = false;
				}
				else{
					//If hitting a wall, stop moving
					m_pPlayer->SetMoveDirection(0);
					//If you weren't hitting a wall but are now, play hitting wall sound
					if(collision == false)
						m_pSoundEffect->playSound(L"Sounds\\thud.wav",false);
					//Now hitting a wall
					collision = true;
				}
			}
			if(attemptDir == 2)
			{
				//Check if there is a wall right
				if(gridSpot[currentPos+1]!=1){
					//Move right, set colliding with walls to false
					m_pPlayer->SetMoveDirection(2);
					collision = false;
				}
				else{
					//If hitting a wall, stop moving
					m_pPlayer->SetMoveDirection(0);
					//If you weren't hitting a wall but are now, play hitting wall sound
					if(collision == false)
						m_pSoundEffect->playSound(L"Sounds\\thud.wav",false);
					//Now hitting a wall
					collision = true;
				}
			}
		}
		else
		{
			//if we are in debug mode we stop the player moving
			attemptDir =0;
			m_pPlayer->SetMoveDirection(0);
			XMFLOAT3 look = m_pMainCamera->getLookAt();
			XMFLOAT3 pos = m_pMainCamera->getOwner()->getTransform().getPosition();
			//movement of the camera,, checks the input
			//Depending on the input the cameras position and the cameras focus are adjusted by 1 in the appropriate direction
			if(debugMove == 1)
			{
				debugMove = 0;
				pos.z = pos.z +1.0f;
				look.z = look.z + 1.0f;
				m_pMainCamera->getOwner()->getTransform().setPosition(pos.x,pos.y,pos.z);
				m_pMainCamera->setLook(look.x,look.y,look.z);
			}
			if(debugMove == 3)
			{
				debugMove = 0;
				pos.z = pos.z -1.0f;
				look.z = look.z -1.0f;
				m_pMainCamera->getOwner()->getTransform().setPosition(pos.x,pos.y,pos.z);
				m_pMainCamera->setLook(look.x,look.y,look.z);
			}
			if(debugMove == 4)
			{
				debugMove = 0;
				pos.x = pos.x -1.0f;
				look.x = look.x -1.0f;
				m_pMainCamera->getOwner()->getTransform().setPosition(pos.x,pos.y,pos.z);
				m_pMainCamera->setLook(look.x,look.y,look.z);
			}
			if(debugMove == 2)
			{
				debugMove = 0;
				pos.x = pos.x +1.0f;
				look.x = look.x +1.0f;
				m_pMainCamera->getOwner()->getTransform().setPosition(pos.x,pos.y,pos.z);
				m_pMainCamera->setLook(look.x,look.y,look.z);
			}
			if(debugMove == 5)
			{
				debugMove = 0;
				pos.y = pos.y +1.0f;
				m_pMainCamera->getOwner()->getTransform().setPosition(pos.x,pos.y,pos.z);
			}
			if(debugMove == 6)
			{
				debugMove = 0;
				pos.y = pos.y -1.0f;
				m_pMainCamera->getOwner()->getTransform().setPosition(pos.x,pos.y,pos.z);
			}
		}
}

void CGameApplication::clearObjectList()
{
        //m_GameObjectList
        GameObjectIter iter=m_GameObjectList.begin();
        while(iter!=m_GameObjectList.end())
        {
                if (*iter)
                {
                        delete (*iter);
                        iter=m_GameObjectList.erase(iter);
                }
                else
                {
                        ++iter;
                }
        }
}