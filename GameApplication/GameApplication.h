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

        void setMainCamera(CameraComponent *pMainCamera)
        {
                m_pMainCamera=pMainCamera;
        }

		void storeGrid(int gPos, int spotVal){
			gridSpot[gPos] = spotVal;
		}

		void storePickups(int gPos, GameObject* cup){
			pickup[gPos] = cup;
		}

		 void setPlayer(Player *pPlayer)
        {
                m_pPlayer=pPlayer;
				currentPos = m_pPlayer->checkPos();
				score = 0;
        }

		void setMusic(AudioComponent *pMusic)
		{
			m_pAudio = pMusic;
			m_pAudio->playSound(L"Sounds\\Kiss From A Rose.wav",true);
		}

		void setSoundEffect(AudioComponent *pSound)
		{
			m_pSoundEffect = pSound;
		}

		void setLight(DirectionLightComponent *light)
		{
			m_pLight = light;
		}

private:
        bool parseConfigFile();
        bool initInput();
        
        bool initGraphics();
        bool initPhysics();

        bool initWindow();
		Player *m_pPlayer;
		AudioComponent *m_pAudio;
		AudioComponent *m_pSoundEffect;
		string inKey;
		int currentPos;
		int attemptDir;
		int gridSpot[357];
		GameObject* pickup[357];
		float lastUpdate;
		bool collision;
		DirectionLightComponent *m_pLight;
		int totalTime;
		int score;

protected:
        typedef vector<GameObject*> GameObjectList;
        typedef vector<GameObject*>::iterator GameObjectIter;
        IWindow * m_pWindow;
        IRenderer * m_pRenderer;
        GameOptionsDesc m_GameOptionDesc;
        wstring m_ConfigFileName;
        GameObjectList m_GameObjectList;
		
        CameraComponent *m_pMainCamera;
};