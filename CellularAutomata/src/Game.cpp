#include "Game.h"

namespace CellularAutomata
{
	Shader* Game::ShaderColor = nullptr;
	Material* Game::MaterialAlive = nullptr;
	Material* Game::MaterialDead = nullptr;
	glm::ivec2 Game::GridSize = glm::ivec2(GridWidth, GridHeight);
	float Game::CellSize = 4.0f;
	float Game::CellInline = 1.0f;
}