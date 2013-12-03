#pragma once

//forward declarations of the D3D10 interfaces
#include "D3D10.h"
#include <map>

using namespace std;

class ResourceHolder
{
public:
	//Default constructor and deconstructor
	ResourceHolder();
	~ResourceHolder();

	//Texture management
	ID3D10Texture2D* GetTexture(LPCSTR fileName);
	bool DeleteTexture(LPCSTR fileName);

	//Effect management
	ID3D10Effect* GetEffect(LPCSTR fileName);
	bool DeleteEffect(LPCSTR fileName);

	//Mesh manager
	ID3D10Mesh* GetMesh(LPCSTR fileName);
	bool DeleteMesh(LPCSTR fileName);

private:
	//Mapped variables
	map < LPCSTR, ID3D10Texture2D* > texture;
	map < LPCSTR, ID3D10Effect* > effect;
	map < LPCSTR, ID3D10Mesh > mesh;
};