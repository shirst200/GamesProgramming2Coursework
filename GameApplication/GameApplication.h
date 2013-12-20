//header guard, so this file is only compiled once
#pragma once

#include <string>
#include <vector>

#include "Components.h"
#include "GameObject.h"
using namespace std;

//Forward decleration of our Window Interface
class IWindow;
class IRenderer;

//Structure for holding GameOptions, this will be loaded from config files
struct GameOptionsDesc
{
        wstring gameName;
        int width;
        int height;
        bool fullscreen;
};

//we have this here so we don't need to prefix all
//standard library types with std::
using namespace std;

//Our Game Application class
class CGameApplication
{
public:
        CGameApplication(void);
        //virtual deconstructor, so this class can be overriden
        virtual ~CGameApplication(void);
        //virtual function, can be overriden
        virtual bool init();
        void run();
        //virtual function, can be overriden
        virtual void render();
        //virtual function, can be overriden
        virtual void update();

        virtual bool initGame();

        void clearObjectList();
		//Stores the main camera
        void setMainCamera(CameraComponent *pMainCamera)
        {
                m_pMainCamera=pMainCamera;
        }
		//Array of grid positions
		void storeGrid(int gPos, int spotVal){
			gridSpot[gPos] = spotVal;
		}
		//Array of pickup objects
		void storePickups(int gPos, GameObject* cup){
			pickup[gPos] = cup;
		}
		//Stores the player, sets its position and sets the score to 0
		 void setPlayer(Player *pPlayer)
        {
                m_pPlayer=pPlayer;
				currentPos = m_pPlayer->checkPos();
				score = 0;
        }
		//Stores the sound effect component for player
		void setSoundEffect(AudioComponent *pSound)
		{
			m_pSoundEffect = pSound;
		}
		//Stores the main light component
		void setLight(DirectionLightComponent *light)
		{
			m_pLight = light;
		}
		void setMusic(AudioComponent *pMusic)
		{
			   m_pAudio = pMusic;
			   m_pAudio->playSound(L"Sounds\\Kiss From A Rose.wav", true);
			   

		  }

private:
        bool parseConfigFile();
        bool initInput();
        
        bool initGraphics();
        bool initPhysics();

        bool initWindow();
		//Player component
		Player *m_pPlayer;
		AudioComponent *m_pAudio;
		AudioComponent *m_pSoundEffect;
		//stores the input key from window
		string inKey;
		//Player position
		int currentPos;
		//Direction that corresponds to input
		int attemptDir;
		//Holds all the grid positions for collisions
		int gridSpot[357];
		//Holds all the pickup objects
		GameObject* pickup[357];
		//Time of last update
		float lastUpdate;
		//Collision with wall
		bool collision;
		//Directional light component
		DirectionLightComponent *m_pLight;
		//Total time elapsed
		int totalTime;
		//Score from pickups
		int score;
		int debugMove;
protected:
        typedef vector<GameObject*> GameObjectList;
        typedef vector<GameObject*>::iterator GameObjectIter;
        IWindow * m_pWindow;
        IRenderer * m_pRenderer;
        GameOptionsDesc m_GameOptionDesc;
        wstring m_ConfigFileName;
        GameObjectList m_GameObjectList;
		bool debug;
        CameraComponent *m_pMainCamera;
};