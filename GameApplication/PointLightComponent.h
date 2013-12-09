#pragma once

#include "LightComponent.h"
#include "GameObject.h"
class PointLightComponent:public LightComponent
{
public:
	PointLightComponent(float brightness)
	{
		intencity=brightness;
		m_Name="pointLight";
	}
	~PointLightComponent();

	float calculateLightReceved(XMFLOAT3 position)
	{
		XMFLOAT3 pos=m_pOwnerGameObject->getTransform().getPosition();
		float distance = (pos.x+position.x)*(pos.x+position.x)+(pos.y+position.y)*(pos.y+position.y)+(pos.z+position.z)*(pos.z+position.z);
		if (distance>intencity)
			{return 0;}
		return (3*intencity/(4*3.14159265359*(distance*distance)));
	}

private:
	float intencity;
}