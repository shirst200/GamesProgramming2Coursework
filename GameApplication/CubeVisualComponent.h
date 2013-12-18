#include "VisualComponent.h"

class CubeVisualComponent:public VisualComponent
{
public:
	CubeVisualComponent(){};
	~CubeVisualComponent(){};
	void createTangent(Vertex *vertex1, Vertex *vertex2, Vertex *vertex3);
	bool create(IRenderer * pRenderer);
};