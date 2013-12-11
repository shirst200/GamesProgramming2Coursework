#include "DirectionLightComponent.h"
#include "Transform.h"
#include "GameObject.h"



void DirectionLightComponent::update(){
	if(orbit)
	{
		
		time(&current);
		XMFLOAT3 lightPos;
		lightPos.x = m_LightDirection.x + sin(difftime(start,current));
		lightPos.z = m_LightDirection.z + cos(difftime(start,current));
		setDirection(lightPos.x,m_LightDirection.y,lightPos.z);
		
		
	}
}