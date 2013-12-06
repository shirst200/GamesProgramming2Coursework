#pragma once

//Includes files needed for the variables
#include "D3D10.h"
#include "D3DX10.h"
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

	//Mesh management
	/*ID3D10Mesh* GetMesh(LPCSTR fileName);
	bool DeleteMesh(LPCSTR fileName);*/

private:
	//Mapped variables
	ID3D10Effect * m_pTempEffect;

	map < LPCSTR, ID3D10EffectMatrixVariable*> m_pWorldEffectVariable;
    ID3D10EffectMatrixVariable * m_pProjectionEffectVariable;
    ID3D10EffectMatrixVariable * m_pViewEffectVariable;
ID3D10EffectTechnique * holder;
	ID3D10Device * m_pD3D10Device;
	map < LPCSTR, ID3D10Texture2D* > texture;
	map < LPCSTR, ID3D10Effect* > effect;
	//map < LPCSTR, ID3D10Mesh > mesh;
};