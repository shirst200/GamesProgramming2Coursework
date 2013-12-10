#include "MyGame.h"

bool MyGame::initGame()
{
	/* CubeVisualComponent *pCube1=new CubeVisualComponent();
        pCube1->create(m_pRenderer);
        
        Material *pMaterial1=new Material();
        pMaterial->loadEffect("Effects/Specular.fx",m_pRenderer);

        DirectionLightComponent * pDirLight=new DirectionLightComponent();

        GameObject * pTestObj2=new GameObject();
        pTestObj2->setName("TestObject2");
        pTestObj2->addComponent(pCube1);
        pTestObj2->addComponent(pMaterial1);
        pTestObj2->addComponent(pDirLight);


        pCube->createVertexLayout(m_pRenderer);
        
        pTestObj2->getTransform().setPosition(0.0f,1.0f,1.0f);


        m_GameObjectList.push_back(pTestObj2);*/
	

		CameraComponent *pCameraComp = new CameraComponent();
        pCameraComp->setLook(8.0f,1.5f,9.0f);
        pCameraComp->setFOV(m_GameOptionDesc.width/m_GameOptionDesc.height);
        
		GameObject *pCameraGO = new GameObject();
        pCameraGO->setName("MainCamera");
        pCameraGO->addComponent(pCameraComp);
        setMainCamera(pCameraComp);
		pCameraGO->getTransform().setPosition(8.0f,25.0f,8.0f);

        m_GameObjectList.push_back(pCameraGO);

	

		byte gridSpots[height*width] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
										1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
										1,2,1,1,0,1,1,0,1,0,1,1,0,1,1,2,1,
										1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
										1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1,
										1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,1,
										1,1,1,1,0,1,1,4,1,4,1,1,0,1,1,1,1,
										4,4,4,1,0,1,4,4,4,4,4,1,0,1,4,4,4,
										1,1,1,1,0,1,4,1,5,1,4,1,0,1,1,1,1,
										4,4,4,4,0,4,4,1,4,1,4,4,0,4,4,4,4,
										1,1,1,1,0,1,4,1,1,1,4,1,0,1,1,1,1,
										4,4,4,1,0,1,4,4,3,4,4,1,0,1,4,4,4,
										1,1,1,1,0,1,4,1,1,1,4,1,0,1,1,1,1,
										1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
										1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,
										1,2,0,1,0,0,0,0,4,0,0,0,0,1,0,2,1,
										1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,
										1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,1,
										1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,
										1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
										1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

		Material *pMaterial=new Material();
		pMaterial->loadEffect("Effects/Texture.fx",m_pRenderer);
		pMaterial->loadDiffuseTexture("Textures/quickTestBrick.png",m_pRenderer);


		AudioComponent *gameMusic=new AudioComponent();
		gameMusic->playSound(L"Sounds\\Kiss From A Rose.wav",true);

		

		for(int i=0;i<(width*height);i++){
			if(gridSpots[i]==1)
			{
				CubeVisualComponent *pCube=new CubeVisualComponent();
				pCube->create(m_pRenderer);
				GameObject *pTestObj=new GameObject();
				pTestObj->setName("TestObject");
				pTestObj->addComponent(pCube);
				pTestObj->addComponent(pMaterial);

				pCube->createVertexLayout(m_pRenderer);
        
				pTestObj->getTransform().setPosition(i%width, 1, (height-1)-(i/width));
				
				m_GameObjectList.push_back(pTestObj);
			}
		}
		//Game Controller
		GameController *controller = new GameController();
		//controller->spawnMap();
		setController(controller);

		GameObject *pController=new GameObject();
		pController->setName("GameController");
		pController->addComponent(controller);
		pController->getTransform().setPosition(-20, 20, -20);

		m_GameObjectList.push_back(pController);

		//Player
		CubeVisualComponent *pCube=new CubeVisualComponent();
		pCube->create(m_pRenderer);
		Player *pPlayer = new Player(93);
		pPlayer->SetMoveDirection(1);
		pPlayer->setController(pController);
		setPlayer(pPlayer);
		Material *pPlayerMaterial=new Material();
		pPlayerMaterial->loadEffect("Effects/Texture.fx",m_pRenderer);

		GameObject *pTestObj=new GameObject();
		pTestObj->setName("Player");
		pTestObj->addComponent(pPlayer);
		pTestObj->addComponent(pCube);
		pTestObj->addComponent(pPlayerMaterial);

		pCube->createVertexLayout(m_pRenderer);
        
		pTestObj->getTransform().setPosition(8, 1, 5);

		m_GameObjectList.push_back(pTestObj);

        return true;
}