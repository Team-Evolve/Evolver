#pragma once

#include "../Object.h"

namespace evolver
{
	class Cube : public Object
	{
	public:
		Cube();
		~Cube();

		void Render();
		void Cleanup();
	};
}
