#include "DirectionLightComponent.h"
#include "Transform.h"
#include "GameObject.h"

void DirectionLightComponent::update(float deltaTime)
{
	// checks if we want the light to rotate, this uses deltatime which is calculated in GameApplication.cpp
	if(rotate==1)
	{
		//first value of deltatime needs to be set to 0.0f for a proper progression
		if (check == 0.0f)
		{
			check = 1.0f;
			deltaTime=0.0f;
		}
		//increments the time by deltatime
		count = count + deltaTime/2;
		XMFLOAT3 lightPos;
		//uses the time value in sin and cos to give a rotation
        lightPos.x = sin(count);
        lightPos.z = cos(count);
		setDirection(lightPos.x,m_LightDirection.y,lightPos.z);

	}
}