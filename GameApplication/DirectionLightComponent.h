#pragma once

#include "GameComponent.h"
#include "LightComponent.h"
#include "../Renderer/Renderer.h"
#include "Windows.h"
#define _XM_NO_INTRINSICS_
#include <xnamath.h>
#include <D3D10.h>
#include <D3DX10.h>

class DirectionLightComponent:public LightComponent
{
public:
	DirectionLightComponent()
	{
		m_Name = "DirectionalLight";
	}
	void setDirection(float x, float y, float z)
	{
		m_Direction=XMFLOAT3(x,y,z);
	}

	XMFLOAT3& getDirection()
	{
		return m_Direction;
	}
private:
	//Represents the direction of the light
	XMFLOAT3 m_Direction;
}