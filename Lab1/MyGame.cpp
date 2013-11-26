#include "MyGame.h"

bool MyGame::initGame()
{
	CubeVisualComponent *pCube=new CubeVisualComponent();
	pCube->create(m_pRenderer);
	
	Material *pMaterial=new Material();
	pMaterial->loadEffect("Effects/Transform.fx",m_pRenderer);

	GameObject *pTestObj=new GameObject();
	pTestObj->setName("TestObject");
	pTestObj->addComponent(pCube);
	pTestObj->addComponent(pMaterial);

	pCube->createVertexLayout(m_pRenderer);
	
	pTestObj->getTransfrom().setPosition(0.5f,1.0f,1.0f);

	m_GameObjectList.push_back(pTestObj);

	CubeVisualComponent *pCube2=new CubeVisualComponent();
	pCube2->create(m_pRenderer);
	
	DirectionLightComponent *pLight=new DirectionLightComponent();
	pLight->setDiffuse(0.5f,0.5f,0.5f,0.5f);
	pLight->setSpecular(0.5f,0.5f,0.5f,0.5f);

	Material *pMaterial1=new Material();
	pMaterial1->loadEffect("Effects/Specular.fx",m_pRenderer);

	GameObject *pTestObj=new GameObject();
	pTestObj->setName("TestObject");
	pTestObj->addComponent(pCube);
	pTestObj->addComponent(pMaterial);

	pCube->createVertexLayout(m_pRenderer);
	
	pTestObj->getTransfrom().setPosition(0.5f,1.0f,1.0f);

	m_GameObjectList.push_back(pTestObj);

	return true;
}