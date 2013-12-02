#pragma once

#include "D3D10.h"
#include <D3DX10.h>
#include <string>
using namespace std;


class Texture{
public:
	Texture(LPCSTR location)
	{
		name=location;
		D3DX10CreateShaderResourceViewFromFileA(m_pD3D10Device, location ,NULL,NULL, &m_pBaseTextureMap,NULL);
	}
	~Texture();
	const char* GetName()
	{
		return name;
	}
	bool HasValue()
	{
		if(name!=NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
private:
	ID3D10Device * m_pD3D10Device;
	ID3D10Texture2D* tex;
	LPCSTR name;
	ID3D10ShaderResourceView * m_pBaseTextureMap;
};