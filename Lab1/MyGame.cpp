#include "MyGame.h"

bool MyGame::initGame()
{
                CubeVisualComponent *pCube1=new CubeVisualComponent();
        pCube1->create(m_pRenderer);
        
        Material *pMaterial1=new Material();
        pMaterial1->loadEffect("Effects/SpecularTextured_Effect.fx",m_pRenderer);
        pMaterial1->loadDiffuseTexture("Textures/Spotlight.jpg",m_pRenderer);


        DirectionLightComponent * pDirLight=new DirectionLightComponent();


        GameObject * pTestObj2=new GameObject();
        pTestObj2->setName("TestObject2");
        pTestObj2->addComponent(pDirLight);
        pDirLight->setDirection(1.0f,0.0f,0.0f);
        pDirLight->setDiffuse(1.0f,1.0f,1.0f,1.0f);
        pDirLight->setSpecular(1.0f,1.0f,1.0f,1.0f);
		pDirLight->RotateOn();
		setLight(pDirLight);
        
        pTestObj2->getTransform().setPosition(0.0f,1.0f,1.0f);




        m_GameObjectList.push_back(pTestObj2);

	

		CameraComponent *pCameraComp = new CameraComponent();
        pCameraComp->setLook(8.0f,1.5f,9.75f);
        pCameraComp->setFOV(m_GameOptionDesc.width/m_GameOptionDesc.height);
        
		GameObject *pCameraGO = new GameObject();
        pCameraGO->setName("MainCamera");
        pCameraGO->addComponent(pCameraComp);
        setMainCamera(pCameraComp);
		pCameraGO->getTransform().setPosition(8.0f,21.0f,9.0f);

        m_GameObjectList.push_back(pCameraGO);

	

		int gridSpots[height*width] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
										1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
										1,2,1,1,0,1,1,0,1,0,1,1,0,1,1,2,1,
										1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
										1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1,
										1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,1,
										1,1,1,1,0,1,1,4,1,4,1,1,0,1,1,1,1,
										4,4,4,1,0,1,4,4,4,4,4,1,0,1,4,4,4,
										1,1,1,1,0,1,4,1,6,1,4,1,0,1,1,1,1,
										5,4,4,4,0,4,4,1,4,1,4,4,0,4,4,5,4,
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
		pMaterial->loadEffect("Effects/Paralax.fx",m_pRenderer);
		pMaterial->loadDiffuseTexture("Textures/quickTestBrick.png",m_pRenderer);
		pMaterial->loadSpecularTexture("Textures/Normal.png",m_pRenderer);
		pMaterial->loadHeightTexture("Textures/Height.png",m_pRenderer);

		Material *pCupMaterial=new Material();
		pCupMaterial->loadEffect("Effects/SpecularTextured_Effect.fx",m_pRenderer);
		pCupMaterial->loadDiffuseTexture("Textures/coffeeUV.png",m_pRenderer);

		Material *pTeleporterMaterial=new Material();
		pTeleporterMaterial->loadEffect("Effects/SpecularTextured_Effect.fx",m_pRenderer);
		pTeleporterMaterial->loadDiffuseTexture("Textures/portalUV.png",m_pRenderer);

		AudioComponent *gameMusic=new AudioComponent();
		AudioComponent *hitWallNoise=new AudioComponent();
		setMusic(gameMusic);
		setSoundEffect(hitWallNoise);

		ResourceHolder resourceHolder = ResourceHolder();

		for(int i=0;i<(width*height);i++){
			storeGrid(i,gridSpots[i]);
			if(gridSpots[i]==1)
			{	
				GameObject *pCube =new GameObject();
				pCube->setName("Cube");
				VisualComponent* res = resourceHolder.GetMeshVisual("Models/cube.fbx",m_pRenderer);
				pCube->addComponent(res);
				pCube->addComponent(pMaterial);
				VisualComponent *pVisual=static_cast<VisualComponent*>(res);
				if(pVisual)
				pVisual->createVertexLayout(m_pRenderer);
				pCube->getTransform().setPosition(i%width, 1, (height-1)-(i/width)-0.5f);
				m_GameObjectList.push_back(pCube);
			}
			if(gridSpots[i]==0)
			{
				GameObject *pCups =new GameObject();
				//pCups = 
				VisualComponent* res = resourceHolder.GetMeshVisual("Models/coffeeCup.fbx",m_pRenderer);
				pCups->addComponent(res);
				pCups->addComponent(pCupMaterial);
				VisualComponent *pVisual=static_cast<VisualComponent*>(res);
				if(pVisual)
						pVisual->createVertexLayout(m_pRenderer);
				pCups->getTransform().setPosition(i%width, 1, (height-1)-(i/width));
				storePickups(i,pCups);
				m_GameObjectList.push_back(pCups);
			}
			if(gridSpots[i]==5)
			{
				GameObject *pTelporter=new GameObject();
				//pCups = 
				VisualComponent* res = resourceHolder.GetMeshVisual("Models/teleporter.fbx",m_pRenderer);
				pTelporter->addComponent(res);
				pTelporter->addComponent(pTeleporterMaterial);
				VisualComponent *pVisual=static_cast<VisualComponent*>(res);
				if(pVisual)
						pVisual->createVertexLayout(m_pRenderer);
				pTelporter->getTransform().setPosition(i%width, 1, (height-1)-(i/width));
				m_GameObjectList.push_back(pTelporter);
			}
		}

		//Player
		VisualComponent* res = resourceHolder.GetMeshVisual("Models/sphere.fbx",m_pRenderer);
				Material *pPlayerMaterial=new Material();
                pPlayerMaterial->loadEffect("Effects/Texture.fx",m_pRenderer);
                pPlayerMaterial->loadDiffuseTexture("Textures/mat_planet.png",m_pRenderer);
		VisualComponent *pVisual=static_cast<VisualComponent*>(res);
		if(pVisual)
			pVisual->createVertexLayout(m_pRenderer);
					
		Player *pPlayer = new Player(263);
		pPlayer->SetMoveDirection(0);
		setPlayer(pPlayer);

		GameObject *pTestObj=new GameObject();
		pTestObj->setName("Player");
		pTestObj->addComponent(pPlayer);
		pTestObj->addComponent(res);
		pTestObj->addComponent(pPlayerMaterial);

		res->createVertexLayout(m_pRenderer);
		pTestObj->getTransform().setRotation(2.0f,0.0f,0.0f);
		pTestObj->getTransform().setPosition(8.0f, 1.0f, 5.0f);

		m_GameObjectList.push_back(pTestObj);

        return true;
}