#pragma once

#include "../GameApplication/Texture.h"
#include "D3D10.h"
#include <list>
#include <string>
using namespace std;

class ResourceHolder
{
public:
	ResourceHolder();
	~ResourceHolder();

	Texture GetTexture(LPCSTR fileName);
	bool DeleteTexture(LPCSTR fileName);

	ID3D10Effect* GetEffect(LPCSTR fileName);
	bool DeleteEffect(LPCSTR fileName);

private:
	map<Texture> texture;
	ID3D10Effect *held_Effect[10];
	
};