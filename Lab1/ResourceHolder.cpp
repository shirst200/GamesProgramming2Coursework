#include "ResourceHolder.h"

ID3D10Texture2D* ResourceHolder::GetTexture(LPCSTR fileName)
{
	//Searches for the resource
	if(texture.find(fileName)==texture.end())
	{
		//If not found add and return the added value
		texture.insert(fileName);
		return texture.at(fileName);
	}
	//If found return
	return texture.at(fileName);
}

bool ResourceHolder::DeleteTexture(LPCSTR fileName)
{
	//Searches for the texture
	if(texture.find(fileName)==texture.end())
	{
		//If not found return false
		return false;
	}
	if(FAILED(texture.erase(fileName)))
	{
		//If failed to delete return false
		return false;
	}
	//If texture deleted return true
	return true;
}

ID3D10Effect* ResourceHolder::GetEffect(LPCSTR fileName)
{
	//Searches for effect
	if(effect.find(fileName)==effect.end())
	{
		//If not found add and return it
		effect.insert(fileName);
		return effect.at(fileName);
	}
	//If effect found return it
	return effect.at(fileName);
}

bool ResourceHolder::DeleteEffect(LPCSTR fileName)
{
	//Searches for effect
	if(effect.find(fileName)==effect.end())
	{
		//If effect not found return false
		return false;
	}
	if(FAILED(effect.erase(fileName)))
	{
		//If failed to delete effect return false
		return false;
	}
	//If resource was deleted return true
	return true;
}

ID3D10Mesh* ResourceHolder::GetMesh(LPCSTR fileName)
{
	//Searches for mesh
	if(mesh.find(fileName)==mesh.end())
	{
		//If not found add and return it
		mesh.insert(fileName);
		return mesh.at(fileName);
	}
	//If found return it
	return mesh.at(fileName);
}

bool ResourceHolder::DeleteMesh(LPCSTR fileName)
{
	//Searches for mesh
	if(mesh.find(fileName)==mesh.end())
	{
		//If not found return false
		return false;
	}
	if(FAILED(mesh.erase(fileName)))
	{
		//If failed to delete return false
		return false;
	}
	//If deleted return true
	return true;
}