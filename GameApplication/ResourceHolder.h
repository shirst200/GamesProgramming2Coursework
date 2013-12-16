#pragma once

#define FBXSDK_NEW_API


#include "../D3D10Renderer/Vertex.h"
#include "../D3D10Renderer/D3D10Renderer.h"

class GameObject;

//Includes files needed for the variables
#include "D3D10.h"
#include "D3DX10.h"
#include <map>
#include <string>
#include <fbxsdk.h>
#include "..\Renderer\Renderer.h"
#include "..\GameApplication\components.h"
using namespace std;

class ResourceHolder
{
public:
	//Default constructor and deconstructor
	ResourceHolder(){};
	~ResourceHolder(){};

	//Texture management
	ID3D10Texture2D* GetTexture(LPCSTR fileName);
	bool DeleteTexture(LPCSTR fileName);
	bool DeleteAllTextures();

	//Effect management
	ID3D10Effect* GetEffect(LPCSTR fileName);
	bool DeleteEffect(LPCSTR fileName);
	bool DeleteAllEffects();

	//Mesh management
	GameObject* GetMesh(LPCSTR fileName, IRenderer *pRenderer);
	bool DeleteMesh(LPCSTR fileName);
	bool DeleteAllMeshes();

private:
	GameObject* RetreveMesh(LPCSTR fileName, IRenderer *pRenderer);

	//Mapped variables
	ID3D10Effect * m_pTempEffect;
	map < LPCSTR, ID3D10EffectMatrixVariable*> m_pWorldEffectVariable;
    ID3D10EffectMatrixVariable * m_pProjectionEffectVariable;
    ID3D10EffectMatrixVariable * m_pViewEffectVariable;
	ID3D10EffectTechnique * holder;
	ID3D10Device * m_pD3D10Device;

	map < LPCSTR, ID3D10Texture2D* > texture;
	map < LPCSTR, ID3D10Texture2D* > ::iterator iterText;
	map < LPCSTR, ID3D10Effect* > effect;
	map < LPCSTR, ID3D10Effect* > ::iterator iterEffect;
	map < LPCSTR, GameObject* > mesh;
	map < LPCSTR, GameObject* > ::iterator iterMesh;
};