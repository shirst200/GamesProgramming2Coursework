#pragma once

#include "GameComponent.h"
#include "../Renderer/Renderer.h"
#include "Windows.h"
#define _XM_NO_INTRINSICS_
#include <xnamath.h>
#include <D3D10.h>
#include <D3DX10.h>

class LightComponent:public GameComponent
{
public:
	LightComponent()
	{
		m_Name="Light";

	}

	void setDiffuse(float r, float g, float b, float a)
	{
		m_DiffuseColour=XMCOLOR(r,g,b,a);
	}

	void setUp(float r, float, g, float b, float a)
	{
		m_SpecularColour=XMCOLOR(r,g,b,a);
	}

	XMCOLOR& getDiffuse()
	{
		return m_DiffuseColour;
	}
	
	XMCOLOR& getSpecular()
	{
		return m_SpecularColour;
	}
private:
	//Represents te diffuse colour of the light
	XMCOLOR m_DiffuseColour;
	//Represents the specular colour of the light
	XMCOLOR m_SpecularColour;

}