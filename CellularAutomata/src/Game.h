#pragma once

#include "Shader.h"
#include "Material.h"

namespace CellularAutomata
{
#define GridWidth 64
#define GridHeight 64

	class Game
	{
	public:
		static Shader* ShaderColor;
		static Material* MaterialAlive;
		static Material* MaterialDead;

		static glm::ivec2 GridSize;
		static float CellOffset;
		static float CellSize;
		static float CellInline;

		static bool Paused;
	};
}