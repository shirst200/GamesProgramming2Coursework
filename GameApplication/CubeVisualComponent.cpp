#include "CubeVisualComponent.h"
#include "../D3D10Renderer/Vertex.h"
#include "../D3D10Renderer/D3D10Renderer.h"

bool CubeVisualComponent::create(IRenderer * pRenderer)
{
	m_iNoVerts=8;
	Vertex verts[8];
	verts[0].position=XMFLOAT3(-0.5f,-0.5f,0.5f);
	verts[0].normal=XMFLOAT3(-0.25f,-0.25f,0.5f);
	verts[0].textureCoords=XMFLOAT2(0.0f,1.0f);
	

	verts[1].position=XMFLOAT3(-0.5f,0.5f,0.5f);
	verts[1].normal=XMFLOAT3(-0.25f,0.25f,0.5f);
	verts[1].textureCoords=XMFLOAT2(0.0f,0.0f);
	
	verts[2].position=XMFLOAT3(0.5f,-0.5f,0.5f);
	verts[2].normal=XMFLOAT3(0.25f,-0.25f,0.5f);
	verts[2].textureCoords=XMFLOAT2(1.0f,1.0f);

	verts[3].position=XMFLOAT3(0.5f,0.5f,0.5f);
	verts[3].normal=XMFLOAT3(0.25f,0.25f,0.5f);
	verts[3].textureCoords=XMFLOAT2(1.0f,0.0f);
	
	verts[4].position=XMFLOAT3(-0.5f,-0.5f,-0.5f);
	verts[4].normal=XMFLOAT3(-0.25f,-0.25f,-0.5f);
	verts[4].textureCoords=XMFLOAT2(0.0f,1.0f);
	
	verts[5].position=XMFLOAT3(-0.5f,0.5f,-0.5f);
	verts[5].normal=XMFLOAT3(-0.25f,0.25f,-0.5f);
	verts[5].textureCoords=XMFLOAT2(0.0f,0.0f);

	verts[6].position=XMFLOAT3(0.5f,-0.5f,-0.5f);
	verts[6].normal=XMFLOAT3(0.25f,-0.25f,-0.5f);
	verts[6].textureCoords=XMFLOAT2(1.0f,1.0f);
	
	verts[7].position=XMFLOAT3(0.5f,0.5f,-0.5f);
	verts[7].normal=XMFLOAT3(0.25f,0.25f,-0.5f);
	verts[7].textureCoords=XMFLOAT2(1.0f,0.0f);


	for(int i=0; i<m_iNoVerts; i++)
	{
		bool end = false;
		if(i+2>=m_iNoVerts)
		{
			verts[i].tangent=verts[i-1].tangent;
		}
		else
		{
			createTangent(&verts[i], &verts[i+1],&verts[i+2]);
		}
	}


	int indices[]={0,1,2,1,3,2,		//front 
					4,5,6,5,7,6,	//back
					4,5,0,1,0,5,
					2,3,7,6,7,2,
					1,5,7,7,3,1,
					0,4,2,4,6,2
					};
	m_iNoIndices=36;

	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pVertexBuffer=pD3D10Renderer->createVertexBuffer(m_iNoVerts,verts);
	m_pIndexBuffer=pD3D10Renderer->createIndexBuffer(m_iNoIndices,indices);
	

	return true;
}
void CubeVisualComponent::createTangent(Vertex *vertex1, Vertex *vertex2, Vertex *vertex3)
{
	float vector1[3], vector2[3];
	float tuVector[2], tvVector[2];
	float den;
	float length;

	vector1[0] = vertex2->position.x - vertex1->position.x;
	vector1[1] = vertex2->position.y - vertex1->position.y;
	vector1[2] = vertex2->position.z - vertex1->position.z;

	vector2[0] = vertex3->position.x - vertex1->position.x;
	vector2[1] = vertex3->position.y - vertex1->position.y;
	vector2[2] = vertex3->position.z - vertex1->position.z;

	tuVector[0] = vertex2->textureCoords.x - vertex1->textureCoords.x;
	tvVector[0] = vertex2->textureCoords.y - vertex1->textureCoords.y;

	tuVector[1] = vertex3->textureCoords.x - vertex1->textureCoords.x;
	tvVector[1] = vertex3->textureCoords.y - vertex1->textureCoords.y;

	den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);

	vertex1->tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
	vertex1->tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
	vertex1->tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

	length = sqrt((vertex1->tangent.x * vertex1->tangent.x) + (vertex1->tangent.y * vertex1->tangent.y) + (vertex1->tangent.z * vertex1->tangent.z));
			
	vertex1->tangent.x = vertex1->tangent.x / length;
	vertex1->tangent.y = vertex1->tangent.y / length;
	vertex1->tangent.z = vertex1->tangent.z / length;

}