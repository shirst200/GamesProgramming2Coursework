#pragma once

#include "LightComponent.h"
#include "Transform.h"
#include "math.h"

class SpotLightComponent:public LightComponent
{
public:
	SpotLightComponent(float brightness,float spread)
	{
		angle=spread/2;
		intencity=brightness;
		m_Name="pointLight";
	}
	~SpotLightComponent();

	float calculateLightReceved(XMFLOAT3 position)
	{
		
		
		XMFLOAT3 pos=Transform.getPosition();
		XMFLOAT3 direction = Transform.getRotation();
		XMFLOAT3 pVector =XMFLOAT3( pos.x-position.x,pos.y-position.y,pos.z-position.z);
		float differance = acosf((direction.x*pVector.x+direction.y*pVector.y+direction.z*pVector.z)/((sqrt(direction.x*direction.x+direction.y*direction.y+direction.z*direction.z))*sqrt(pVector.x*pVector.x+pVector.y*pVector.y+pVector.z*pVector.z)));
		if (differance>angle)
			{return 0;}

		float distance = (pos.x+position.x)*(pos.x+position.x)+(pos.y+position.y)*(pos.y+position.y)+(pos.z+position.z)*(pos.z+position.z);
		if (distance>intencity)
			{return 0;}
		int anglePower=1;
		if (differance>1/3*angle)
		{anglePower=3;}
		anglePower=anglePower*cosf(differance)+1;
		return (3*intencity*anglePower/(4*3.14159265359*(distance*distance)));
	}

private:
	float intencity;
	float angle;
}