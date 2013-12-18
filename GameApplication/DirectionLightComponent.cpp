#include "DirectionLightComponent.h"
#include "Transform.h"
#include "GameObject.h"

void DirectionLightComponent::update(float deltaTime)
{
	if(rotate==1)
	{
		if (check == 0.0f)
		{
			check = 1.0f;
			deltaTime=0.0f;
		}
		count = count + deltaTime/2;
		XMFLOAT3 lightPos;
        lightPos.x = sin(count);
        lightPos.z = cos(count);
		setDirection(lightPos.x,0.0f,lightPos.z);

	}
}