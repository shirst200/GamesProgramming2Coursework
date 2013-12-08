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
        pCameraComp->setLook(1.5f,1.5f,1.5f);
        pCameraComp->setFOV(m_GameOptionDesc.width/m_GameOptionDesc.height);
        
		GameObject *pCameraGO = new GameObject();
        pCameraGO->setName("MainCamera");
        pCameraGO->addComponent(pCameraComp);
        setMainCamera(pCameraComp);
		pCameraGO->getTransform().setPosition(1.5f,5.0f,-1.5f);

        m_GameObjectList.push_back(pCameraGO);

		bool gridSpots[height*width] = {1,1,1,1,
										1,0,0,1,
										1,0,0,1,
										1,1,1,1};

		for(int i=0;i<(width*height);i++){
			if(gridSpots[i])
			{
				CubeVisualComponent *pCube=new CubeVisualComponent();
				pCube->create(m_pRenderer);
        
				Material *pMaterial=new Material();
				pMaterial->loadEffect("Effects/Texture.fx",m_pRenderer);
				pMaterial->loadDiffuseTexture("Textures/Spotlight.jpg",m_pRenderer);

				GameObject *pTestObj=new GameObject();
				pTestObj->setName("TestObject");
				pTestObj->addComponent(pCube);
				pTestObj->addComponent(pMaterial);

				pCube->createVertexLayout(m_pRenderer);
        
				pTestObj->getTransform().setPosition(i%width, 1, i/height);

				m_GameObjectList.push_back(pTestObj);
			}
		}
		//Player
		CubeVisualComponent *pCube=new CubeVisualComponent();
		pCube->create(m_pRenderer);
		Player *pPlayer = new Player(5);
		pPlayer->SetMoveDirection(1);
		Material *pMaterial=new Material();
		pMaterial->loadEffect("Effects/Texture.fx",m_pRenderer);
		pMaterial->loadDiffuseTexture("Textures/Spotlight.jpg",m_pRenderer);

		GameObject *pTestObj=new GameObject();
		pTestObj->setName("TestObject");
		pTestObj->addComponent(pPlayer);
		pTestObj->addComponent(pCube);
		pTestObj->addComponent(pMaterial);

		pCube->createVertexLayout(m_pRenderer);
        
		pTestObj->getTransform().setPosition(1, 1, 1);

		m_GameObjectList.push_back(pTestObj);

        return true;
}