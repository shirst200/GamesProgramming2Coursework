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

        m_pRenderer->clear(0.5f,0.5f,0.5f,0.5f);
        m_pRenderer->render();
        m_pRenderer->present();
}

//Update, called to update the game
void CGameApplication::update()
{
		float dt =  ((float) clock() - lastUpdate)/CLOCKS_PER_SEC;
		totalTime = totalTime - dt;
        for(GameObjectIter iter=m_GameObjectList.begin();iter!=m_GameObjectList.end();iter++)
        {
                (*iter)->update();

        }
	
		lastUpdate = clock();
		m_pPlayer->update(dt);
		m_pLight->update(dt);
		//Player input
		if(inKey=="w")
			attemptDir = 1;
		if(inKey=="s")
			attemptDir = 3;
		if(inKey=="a")
			attemptDir = 4;
		if(inKey=="d")
			attemptDir = 2;
		if(inKey=="f")
			m_pAudio->pauseSound();

		//Check Player for pickups
		if(gridSpot[currentPos-17]==0){
			//pickup[currentPos].~GameObject();
			pickup[currentPos].getTransform().setPosition(0,0,0);
			gridSpot[currentPos-17] = 4;
			score++;
		}

		//Checks grid for collisons
		if(attemptDir == 1)
		{
			if(gridSpot[currentPos-17]!=1){
				m_pPlayer->SetMoveDirection(1);
				collision = false;
			}
			else{
				m_pPlayer->SetMoveDirection(0);
				if(collision == false)
					m_pSoundEffect->playSound(L"Sounds\\thud.wav",false);
				collision = true;
			}
		}
		if(attemptDir == 3)
		{
			if(gridSpot[currentPos+17]!=1){
				m_pPlayer->SetMoveDirection(3);
				collision = false;
			}
			else{
				m_pPlayer->SetMoveDirection(0);
				if(collision == false)
					m_pSoundEffect->playSound(L"Sounds\\thud.wav",false);
				collision = true;
			}
		}
		if(attemptDir == 4)
		{
			if(gridSpot[currentPos-1]!=1){
				m_pPlayer->SetMoveDirection(4);
				collision = false;
			}
			else{
				m_pPlayer->SetMoveDirection(0);
				if(collision == false)
					m_pSoundEffect->playSound(L"Sounds\\thud.wav",false);
				collision = true;
			}
		}
		if(attemptDir == 2)
		{
			if(gridSpot[currentPos+1]!=1){
				m_pPlayer->SetMoveDirection(2);
				collision = false;
			}
			else{
				m_pPlayer->SetMoveDirection(0);
				if(collision == false)
					m_pSoundEffect->playSound(L"Sounds\\thud.wav",false);
				collision = true;
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