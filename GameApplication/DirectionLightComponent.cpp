#include "DirectionLightComponent.h"
#include "Transform.h"
#include "GameObject.h"



void DirectionLightComponent::update(){
	if(orbit)
	{
		
		count = count + 0.01;
		XMFLOAT3 lightPos;
		lightPos.x = sin(count);
		lightPos.z = cos(count);
		setDirection(lightPos.x,m_LightDirection.y,lightPos.z);
		
		
	}
}