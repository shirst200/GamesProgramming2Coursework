#pragma once
#include <Windows.h>

//forward declarations of the D3D10 interfaces
#include <D3DX10.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>
#include "D3D10.h"
#include <iostream>
#include <map>

using namespace std;

class ResourceHolder
{
public:
	ResourceHolder();
	~ResourceHolder();

	ID3D10Texture2D* GetTexture(LPCSTR fileName);
	bool DeleteTexture(LPCSTR fileName);

	ID3D10Effect* GetEffect(LPCSTR fileName);
	bool DeleteEffect(LPCSTR fileName);

private:
	map<LPCSTR, ID3D10Texture2D*> texture;
	map<LPCSTR, ID3D10Effect*> effect;
	
};