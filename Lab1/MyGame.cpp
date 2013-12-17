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
        pDirLight->setDirection(0.0f,0.0f,0.0f);
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
		pMaterial->loadEffect("Effects/SpecularTextured_Effect.fx",m_pRenderer);
		pMaterial->loadDiffuseTexture("Textures/quickTestBrick.png",m_pRenderer);

		Material *pCupMaterial=new Material();
		pCupMaterial->loadEffect("Effects/SpecularTextured_Effect.fx",m_pRenderer);
		pCupMaterial->loadDiffuseTexture("Textures/coffeeCup.jpeg",m_pRenderer);


		AudioComponent *gameMusic=new AudioComponent();
		AudioComponent *hitWallNoise=new AudioComponent();
		setMusic(gameMusic);
		setSoundEffect(hitWallNoise);

		ResourceHolder resourceHolder = ResourceHolder();

		/*for(int i=0;i<(width*height);i++){
			storeGrid(i,gridSpots[i]);
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
			}*/
			//if(gridSpots[i]==0)
			//{
				//cups

				GameObject *pCups = new GameObject();
				//pCups = 
				VisualComponent* res = resourceHolder.GetMeshVisual("Models/coffeeCup.fbx",m_pRenderer);
				for(GameObject::ChildrenGameObjectsIter iter=pCups->getFirstChild();iter!=pCups->getLastChild();iter++)
				{
					if((*iter).second!=NULL){
				
						(*iter).second->addComponent(pCupMaterial);
						VisualComponent *pVisual=static_cast<VisualComponent*>(res);
						if(pVisual)
							pVisual->createVertexLayout(m_pRenderer);
					}
				}
				pCups->getTransform().setPosition(1, 1, 1);
				pCups->getTransform().setScale(50,50,50);
				m_GameObjectList.push_back(pCups);
			//}
		//}

		

		/*GameObject *pCar=resourceHolder.GetMesh("Models/armoredrecon.fbx",m_pRenderer);
        for(GameObject::ChildrenGameObjectsIter iter=pCar->getFirstChild();iter!=pCar->getLastChild();iter++)
        {
                pMaterial=new Material();
                pMaterial->loadEffect("Effects/Texture.fx",m_pRenderer);
                pMaterial->loadDiffuseTexture("Textures/armoredrecon_diff.png",m_pRenderer);
                iter->second->addComponent(pMaterial);
                VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
                pVisual->createVertexLayout(m_pRenderer);
        }

        m_GameObjectList.push_back(pCar);*/


		//Player
		CubeVisualComponent *pCube=new CubeVisualComponent();
		pCube->create(m_pRenderer);
		Player *pPlayer = new Player(263);
		pPlayer->SetMoveDirection(0);
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