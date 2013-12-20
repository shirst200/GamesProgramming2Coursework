#pragma once

//Bring in the external files needed for model loading
#define FBXSDK_NEW_API
#include <fbxsdk.h>

class GameObject;

//Includes files needed to create the variables
#include <map>
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
	GameObject* GetMeshObject(LPCSTR fileName, IRenderer *pRenderer);
	VisualComponent* GetMeshVisual(LPCSTR fileName, IRenderer *pRenderer);
	bool DeleteMesh(LPCSTR fileName);
	void computeTangents(Vertex *pVerts,int vertexCount); 
	bool DeleteAllMeshes();


private:
	//To bring in a mesh as gameobject and visual component
	GameObject* RetreveMesh(LPCSTR fileName, IRenderer *pRenderer);

	//Mapped variables
	ID3D10Effect * m_pTempEffect;
	map < LPCSTR, ID3D10EffectMatrixVariable*> m_pWorldEffectVariable;
    ID3D10EffectMatrixVariable * m_pProjectionEffectVariable;
    ID3D10EffectMatrixVariable * m_pViewEffectVariable;
	ID3D10EffectTechnique * holder;
	ID3D10Device * m_pD3D10Device;

	//A variable mapping file names to textures and it's iterator
	map < LPCSTR, ID3D10Texture2D* > texture;
	map < LPCSTR, ID3D10Texture2D* > ::iterator iterText;

	//A variable mapping file names to effects and it's iterator
	map < LPCSTR, ID3D10Effect* > effect;
	map < LPCSTR, ID3D10Effect* > ::iterator iterEffect;

	//Variables mapping filenames to gameobjects or visual components and their iterators
	map < LPCSTR, GameObject* > mesh;
	map < LPCSTR, GameObject* > ::iterator iterMesh;
	map < LPCSTR, VisualComponent* > visual;
	map < LPCSTR, VisualComponent* > ::iterator iterVisual;
};