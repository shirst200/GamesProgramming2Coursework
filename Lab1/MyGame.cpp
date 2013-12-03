#include "MyGame.h"

bool MyGame::initGame()
{
        CubeVisualComponent *pCube=new CubeVisualComponent();
        pCube->create(m_pRenderer);
        
        Material *pMaterial=new Material();
        pMaterial->loadEffect("Effects/Specular.fx",m_pRenderer);


        DirectionLightComponent *pDirLight=new DirectionLightComponent();


        GameObject *pTestObj=new GameObject();
        pTestObj->setName("TestObject");
        pTestObj->addComponent(pCube);
        pTestObj->addComponent(pMaterial);
        pTestObj->addComponent(pDirLight);


        pCube->createVertexLayout(m_pRenderer);
        
        pTestObj->getTransfrom().setPosition(2.0f,1.0f,1.0f);


        m_GameObjectList.push_back(pTestObj);

	
        pCube=new CubeVisualComponent();
        pCube->create(m_pRenderer);
        
        pMaterial=new Material();
        pMaterial->loadEffect("Effects/Texture.fx",m_pRenderer);
        pMaterial->loadDiffuseTexture("Textures/Spotlight.jpg",m_pRenderer);

        pTestObj=new GameObject();
        pTestObj->setName("TestObject1");
        pTestObj->addComponent(pCube);
        pTestObj->addComponent(pMaterial);


        pCube->createVertexLayout(m_pRenderer);
        
        pTestObj->getTransfrom().setPosition(-0.5f,1.0f,1.0f);
		 m_GameObjectList.push_back(pTestObj);

	return true;
}