#include "GameApplication.h"

//should really check to see if we are on a Windows platform
#include "../Window/Win32Window.h"
#include "../D3D10Renderer/D3D10Renderer.h"

//Constructor
CGameApplication::CGameApplication(void)
{
	//Set to NULL
	m_pWindow=NULL;
	//Set the Window name to GP2
	m_GameOptionDesc.gameName=TEXT("GP2");
	//Window Height and Width
	m_GameOptionDesc.width=640;
	m_GameOptionDesc.height=480;
	//Full screen
	m_GameOptionDesc.fullscreen=false;
	//Config options
	m_ConfigFileName=TEXT("game.cfg");
}

//Deconstructor
CGameApplication::~CGameApplication(void)
{
	//Delete things in reverse order
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
	if(!initWindow())
		return false;
	if(!initGraphics())
		return false;
	if(!initInput())
		return false;
	if(!initGame())
		return false;
	return true;
}

//called to parse the config gile
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
	if (!m_pRenderer->init(m_pWindow->getHandleToWindow(), m_GameOptionDesc.fullscreen))
		return false;

	return true;
}

//initWindow - initialise the window
bool CGameApplication::initWindow()
{
	//Create a Win32 Window
	m_pWindow = new CWin32Window();
	m_pWindow->init(m_GameOptionDesc.gameName,m_GameOptionDesc.width,m_GameOptionDesc.height,m_GameOptionDesc.fullscreen);
	return true;
}

//called to init the game elements
bool CGameApplication::initGame()
{
	return true;
}

//Called to put the game in a loop (aka game loop)
void CGameApplication::run()
{
	//while the window is not closed
	while(m_pWindow->running())
	{
		//check for all windows messages
		m_pWindow->checkForWindowMessages();
		//update
		update();
		//render
		render();
	}
}

//Render, called to draw one frame of the game
void CGameApplication::render()
{
	m_pRenderer->clear(0.0f,0.0f,0.0f,1.0f);
	m_pRenderer->render();
	m_pRenderer->present();
}

//Update, called to update the game
void CGameApplication::update()
{
}