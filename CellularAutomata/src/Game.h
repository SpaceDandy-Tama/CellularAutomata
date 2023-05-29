#pragma once

#include "Shader.h"
#include "Material.h"

namespace CellularAutomata
{
#define CELLSTATE_DEAD  0;
#define CELLSTATE_ALIVE 1;

#define GridWidth 128
#define GridHeight 128

	class Game
	{
	public:
		static Shader* ShaderColor;
		static Material* MaterialAlive;
		static Material* MaterialDead;

		static glm::ivec2 GridSize;
		static float CellSize;
		static float CellInline;
	};
}