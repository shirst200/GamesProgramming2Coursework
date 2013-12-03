#include "ResourceHolder.h"

ID3D10Texture2D* ResourceHolder::GetTexture(LPCSTR fileName)
{
	if(texture.find(fileName)==texture.end())
	{
		texture.insert(fileName);
		return texture.at(fileName);
	}
	else{return texture.at(fileName);}
}

bool ResourceHolder::DeleteTexture(LPCSTR fileName)
{

}

ID3D10Effect* ResourceHolder::GetEffect(LPCSTR fileName)
{

}

bool ResourceHolder::DeleteEffect(LPCSTR fileName)
{

}