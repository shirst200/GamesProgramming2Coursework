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
		
		XMFLOAT3 vectorToPosition =XMFLOAT3( pos.x-position.x,pos.y-position.y,pos.z-position.z);
		float differance = acosf((pos.x*position.x+pos.y*position.y+pos.z*position.z)/((sqrt(pos.x*pos.x+pos.y*pos.y+pos.z*pos.z))*sqrt(position.x*position.x+position.y*position.y+position.z*position.z)));
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