#include "ResourceHolder.h"

Texture ResourceHolder::GetTexture(LPCSTR fileName)
{
	Texture tixture=Texture(NULL);
	list<Texture>::iterator ListItem;
	for (ListItem = texture.begin();ListItem != texture.end();++ListItem)
	{
		tixture = ListItem;
		if(ListItem. .GetName()!=fileName)
		{
			return texture[i];
		}
	}
	texture.assign(new Texture(new const CHAR('s')),texture.end());
	Texture texture[i] = new Texture(fileName);
	return texture[i];
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