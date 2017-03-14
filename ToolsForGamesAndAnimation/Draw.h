#pragma once

#include "Mesh.h"
#include <list>
#include <map>
#include <algorithm>

class Draw {
	public:
		static void DrawAll();
		static void AddToDraw(Mesh *m);
		static void RemoveFromDraw(Mesh *m);

	private:
		static std::list<Mesh*> m_drawStack;
};

