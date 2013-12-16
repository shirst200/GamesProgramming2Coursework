#include "DirectionLightComponent.h"
#include "Transform.h"
#include "GameObject.h"

void DirectionLightComponent::update(float deltaTime)
{
	if(rotate==1)
	{
		count = count + deltaTime/2;
		XMFLOAT3 lightPos;
        lightPos.x = sin(count);
        lightPos.z = cos(count);
		setDirection(lightPos.x,m_LightDirection.y,lightPos.z);

	}
}