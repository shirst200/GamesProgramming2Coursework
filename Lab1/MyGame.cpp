#include "MyGame.h"

bool MyGame::initGame()
{
        CubeVisualComponent *pCube1=new CubeVisualComponent();
        pCube1->create(m_pRenderer);
        
        Material *pMaterial1=new Material();
        pMaterial1->loadEffect("Effects/SpecularTextured_Effect.fx",m_pRenderer);
        pMaterial1->loadDiffuseTexture("Textures/Spotlight.jpg",m_pRenderer);

		//Creates the dirctional light component
        DirectionLightComponent * pDirLight=new DirectionLightComponent();

		
        GameObject * pTestObj2=new GameObject();
        pTestObj2->setName("TestObject2");
        pTestObj2->addComponent(pDirLight);
		//sets the direction and colour of the directional light
        pDirLight->setDirection(1.0f,0.0f,0.0f);
        pDirLight->setDiffuse(1.0f,1.0f,1.0f,1.0f);
        pDirLight->setSpecular(1.0f,1.0f,1.0f,1.0f);
		//tells the light to rotate
		pDirLight->RotateOn();
		//sets this light as the main light
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
	
		//Grid used for collisions and build map
		//0 - Cup			3 - Cherry
		//1 - Wall			4 - Empty spot
		//2 - Whiskey		5 - Teleporter
	
		int gridSpots[height*width] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
										1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
										1,2,1,1,0,1,1,0,1,0,1,1,0,1,1,2,1,
										1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
										1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1,
										1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,1,
										1,1,1,1,0,1,1,4,1,4,1,1,0,1,1,1,1,
										4,4,4,1,0,1,4,4,4,4,4,1,0,1,4,4,4,
										1,1,1,1,0,1,4,1,4,1,4,1,0,1,1,1,1,
										4,5,4,4,0,4,4,1,4,1,4,4,0,4,4,5,4,
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

		//Creates the material for the walls before the walls to save on memory
		Material *pMaterial=new Material();
		pMaterial->loadEffect("Effects/Paralax.fx",m_pRenderer);
		pMaterial->loadDiffuseTexture("Textures/quickTestBrick.png",m_pRenderer);
		pMaterial->loadSpecularTexture("Textures/Normal.png",m_pRenderer);
		pMaterial->loadHeightTexture("Textures/Height.png",m_pRenderer);

		//Creates the material for the cups before the cups to save on memory
		Material *pCupMaterial=new Material();
		pCupMaterial->loadEffect("Effects/SpecularTextured_Effect.fx",m_pRenderer);
		pCupMaterial->loadDiffuseTexture("Textures/coffeeUV.png",m_pRenderer);

		//Creates the material for the bottle before the bottles to save on memory
		Material *pBottleMat=new Material();
		pBottleMat->loadEffect("Effects/SpecularTextured_Effect.fx",m_pRenderer);
		pBottleMat->loadDiffuseTexture("Textures/bottleUv.png",m_pRenderer);

		//Creates the material for the teleporter before the teleporter to save on memory
		Material *pTeleporterMaterial=new Material();
		pTeleporterMaterial->loadEffect("Effects/SpecularTextured_Effect.fx",m_pRenderer);
		pTeleporterMaterial->loadDiffuseTexture("Textures/portalUV.png",m_pRenderer);

		AudioComponent *gameMusic=new AudioComponent();
		AudioComponent *hitWallNoise=new AudioComponent();
		setMusic(gameMusic);
		setSoundEffect(hitWallNoise);

		ResourceHolder resourceHolder = ResourceHolder();

		//Map maker
		for(int i=0;i<(width*height);i++){
			//Sends grid values to the Gameapp
			storeGrid(i,gridSpots[i]);
			if(gridSpots[i]==1)
			{	
				//Creates a new gameObject and calls it cube
				GameObject *pCube =new GameObject();
				pCube->setName("Cube");
				//gets the mesh as a visual components and adds it to the gameObject
				VisualComponent* res = resourceHolder.GetMeshVisual("Models/wall.fbx",m_pRenderer);
				pCube->addComponent(res);
				//adds predefined pMaterial
				pCube->addComponent(pMaterial);
				VisualComponent *pVisual=static_cast<VisualComponent*>(res);
				if(pVisual)
				pVisual->createVertexLayout(m_pRenderer);
				//sets the position of object reletive to the position of the loop
				pCube->getTransform().setPosition(i%width, 1, (height-1)-(i/width));
				m_GameObjectList.push_back(pCube);
			}
			if(gridSpots[i]==0)
			{
				//Creates a new gameobject
				GameObject *pCups =new GameObject();
				//gets the mesh as a visual component and adds it to the gameobject
				VisualComponent* res = resourceHolder.GetMeshVisual("Models/coffeeCup.fbx",m_pRenderer);
				pCups->addComponent(res);
				//adds predefined pCupMaterial
				pCups->addComponent(pCupMaterial);
				VisualComponent *pVisual=static_cast<VisualComponent*>(res);
				if(pVisual)
						pVisual->createVertexLayout(m_pRenderer);
				//sets the position of object reletive to the position of the loop
				pCups->getTransform().setPosition(i%width, 1, (height-1)-(i/width));
				//Store this object in the pickup array of GameApp
				storePickups(i,pCups);
				m_GameObjectList.push_back(pCups);
			}
			if(gridSpots[i]==2)
			{
				//Creates a new gameobject
				GameObject *pBottle =new GameObject();
				//gets the mesh as a visual component and adds it to the gameobject
				VisualComponent* res = resourceHolder.GetMeshVisual("Models/bottle.fbx",m_pRenderer);
				pBottle->addComponent(res);
				//adds predefined pBottleMat
				pBottle->addComponent(pBottleMat);
				VisualComponent *pVisual=static_cast<VisualComponent*>(res);
				if(pVisual)
						pVisual->createVertexLayout(m_pRenderer);
				//sets the position of object reletive to the position of the loop
				pBottle->getTransform().setPosition(i%width, 1, (height-1)-(i/width));
				//Store this object in the pickup array of GameApp
				storePickups(i,pBottle);
				m_GameObjectList.push_back(pBottle);
			}
			if(gridSpots[i]==5)
			{
				//creates a new GameObject
				GameObject *pTelporter=new GameObject();
				//retreves the mesh and sets stores it in res, adds res to pTeleporter
				VisualComponent* res = resourceHolder.GetMeshVisual("Models/teleporter.fbx",m_pRenderer);
				pTelporter->addComponent(res);
				//adds predefined pTeleporterMaterial
				pTelporter->addComponent(pTeleporterMaterial);
				VisualComponent *pVisual=static_cast<VisualComponent*>(res);
				if(pVisual)
						pVisual->createVertexLayout(m_pRenderer);
				//sets the position of object reletive to the position of the loop
				pTelporter->getTransform().setPosition(i%width, 1, (height-1)-(i/width));
				m_GameObjectList.push_back(pTelporter);
			}
		}
		//Creates the player
		//Creates a visual component for player
		VisualComponent* res = resourceHolder.GetMeshVisual("Models/sphere.fbx",m_pRenderer);
		//creates a material for player
		Material *pPlayerMaterial=new Material();
        pPlayerMaterial->loadEffect("Effects/SpecularTextured_Effect.fx",m_pRenderer);
        pPlayerMaterial->loadDiffuseTexture("Textures/mat_planet.png",m_pRenderer);
		VisualComponent *pVisual=static_cast<VisualComponent*>(res);
		if(pVisual)
			pVisual->createVertexLayout(m_pRenderer);
					
		//creates the player component
		Player *pPlayer = new Player(263);
		//Set the player not moving to begin with
		pPlayer->SetMoveDirection(0);
		//Store the player componenent in GameApp
		setPlayer(pPlayer);

		//creates player game object and adds the visual, player and material components
		GameObject *pTestObj=new GameObject();
		pTestObj->setName("Player");
		pTestObj->addComponent(pPlayer);
		pTestObj->addComponent(res);
		pTestObj->addComponent(pPlayerMaterial);

		res->createVertexLayout(m_pRenderer);
		//sets the position and rotation of the player
		pTestObj->getTransform().setRotation(2.0f,0.0f,0.0f);
		pTestObj->getTransform().setPosition(8.0f, 1.0f, 5.0f);

		m_GameObjectList.push_back(pTestObj);

        return true;
}