#include "Game.h"

namespace CellularAutomata
{
	Shader* Game::ShaderColor = nullptr;
	Material* Game::MaterialAlive = nullptr;
	Material* Game::MaterialDead = nullptr;

	glm::ivec2 Game::GridSize = glm::ivec2(GridWidth, GridHeight);
	float Game::CellOffset = 0.5f;
	float Game::CellSize = 9.0f;
	float Game::CellInline = 1.0f;

	bool Game::Paused = true;
}