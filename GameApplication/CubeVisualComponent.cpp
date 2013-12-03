#include "CubeVisualComponent.h"
#include "../D3D10Renderer/Vertex.h"
#include "../D3D10Renderer/D3D10Renderer.h"

bool CubeVisualComponent::create(IRenderer * pRenderer)
{
	m_iNoVerts=8;
	Vertex verts[8];
	verts[0].position=XMFLOAT3(-0.5f,-0.5f,0.0f);
	verts[1].position=XMFLOAT3(-0.5f,0.5f,0.0f);
	verts[2].position=XMFLOAT3(0.5f,-0.5f,0.0f);
	verts[3].position=XMFLOAT3(0.5f,0.5f,0.0f);

	verts[4].position=XMFLOAT3(-0.5f,-0.5f,-5.5f);
	verts[5].position=XMFLOAT3(-0.5f,0.5f,-5.5f);
	verts[6].position=XMFLOAT3(0.5f,-0.5f,-5.5f);
	verts[7].position=XMFLOAT3(0.5f,0.5f,-5.5f);

	
	XMVECTOR vec1 = XMLoadFloat3(&XMFLOAT3(verts[0].position.x, verts[0].position.y, verts[0].position.z));
	XMVECTOR vec2 = XMLoadFloat3(&XMFLOAT3(verts[1].position.x, verts[1].position.y, verts[1].position.z));
	XMVECTOR vec3 = XMLoadFloat3(&XMFLOAT3(verts[2].position.x, verts[2].position.y, verts[2].position.z));
	XMVECTOR norm1  = XMVector3Cross(XMVectorSubtract(vec2 ,vec1), XMVectorSubtract(vec3 ,vec1));

	XMVECTOR vec4 = XMLoadFloat3(&XMFLOAT3(verts[1].position.x, verts[1].position.y, verts[1].position.z));
	XMVECTOR vec5 = XMLoadFloat3(&XMFLOAT3(verts[3].position.x, verts[3].position.y, verts[3].position.z));
	XMVECTOR vec6 = XMLoadFloat3(&XMFLOAT3(verts[2].position.x, verts[2].position.y, verts[2].position.z));
	XMVECTOR norm2  = XMVector3Cross(XMVectorSubtract(vec5 ,vec4), XMVectorSubtract(vec6 ,vec4));

	for (int i =0;i<4;i++)
	{
		verts[i].normal.x=(norm1.x+norm2.x)/2;
		verts[i].normal.y=(norm1.y+norm2.x)/2;
		verts[i].normal.z=(norm1.z+norm2.z)/2;
		XMVECTOR normal=XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(verts[i].normal)));
		verts[i].normal.x=normal.x;
		verts[i].normal.y=normal.y;
		verts[i].normal.z=normal.z;
	}
	vec1 = XMLoadFloat3(&XMFLOAT3(verts[4].position.x, verts[4].position.y, verts[4].position.z));
	vec2 = XMLoadFloat3(&XMFLOAT3(verts[5].position.x, verts[5].position.y, verts[5].position.z));
	vec3 = XMLoadFloat3(&XMFLOAT3(verts[6].position.x, verts[6].position.y, verts[6].position.z));
	norm1  = XMVector3Cross(XMVectorSubtract(vec2 ,vec1), XMVectorSubtract(vec3 ,vec1));
	vec4 = XMLoadFloat3(&XMFLOAT3(verts[5].position.x, verts[5].position.y, verts[5].position.z));
	vec5 = XMLoadFloat3(&XMFLOAT3(verts[7].position.x, verts[7].position.y, verts[7].position.z));
	vec6 = XMLoadFloat3(&XMFLOAT3(verts[6].position.x, verts[6].position.y, verts[6].position.z));
	norm1  = XMVector3Cross(XMVectorSubtract(vec2 ,vec1), XMVectorSubtract(vec3 ,vec1));
		for (int i =4;i<8;i++)
	{
		verts[i].normal.x=(norm1.x+norm2.x)/2;
		verts[i].normal.y=(norm1.y+norm2.x)/2;
		verts[i].normal.z=(norm1.z+norm2.z)/2;
		XMVECTOR normal=XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(verts[i].normal)));
		verts[i].normal.x=normal.x;
		verts[i].normal.y=normal.y;
		verts[i].normal.z=normal.z;
	}

	int indices[]={	0,1,2,	1,3,2,
					1,5,3,	5,7,3,
					3,7,2,	7,6,2,
					4,0,6,	0,2,6,
					0,1,4,	1,5,4,
					4,5,6,	5,7,6};
	m_iNoIndices=36;


	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pVertexBuffer=pD3D10Renderer->createVertexBuffer(m_iNoVerts,verts);
	m_pIndexBuffer=pD3D10Renderer->createIndexBuffer(m_iNoIndices,indices);
	

	return true;
}

