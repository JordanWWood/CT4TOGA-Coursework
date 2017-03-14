#include "Draw.h"

std::list<Mesh*> Draw::m_drawStack = *(new std::list<Mesh*>);

using namespace std;
void Draw::DrawAll() {
	std::map<float, Mesh> floatToMesh;
	std::vector<float*> floats;

	for each (Mesh * m in m_drawStack) {
		floatToMesh[m->GetLastTransform()->GetPos().z] = *m;
		floats.push_back(&m->GetLastTransform()->GetPos().z);
	}

	//std::sort(floats.begin(), floats.end());
	//std::reverse(floats.begin(), floats.end());

	cout << floats.size() << endl;

	for each (float * f in floats) {
		if (&f != NULL) { 
			cout << f << ":" << *f << ":" << m_drawStack.size() << endl;
			floatToMesh[*f].dDraw();
		} else cout << "NULL" << endl;
	} 
}

void Draw::AddToDraw(Mesh * m) {
	m_drawStack.push_back(m);
}

void Draw::RemoveFromDraw(Mesh * m) {
	std::list<Mesh*> builder;
	for each (Mesh* mesh in m_drawStack) {
		if (&m != &mesh) {
			builder.push_back(mesh);
		}
	}

	m_drawStack = builder;
}