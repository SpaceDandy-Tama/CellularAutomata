#pragma once

#include "Entity.h"

#include "Game.h";

namespace CellularAutomata
{
	class Cell : public Entity
	{
	public:
		Cell(int x, int y) : Entity(glm::vec3(x, y, 0) * (Game::CellSize + Game::CellInline), glm::quat(), glm::vec3(Game::CellSize), Mesh::Quad, Game::MaterialDead)
		{
			CurrentState = NextState = CELLSTATE_DEAD;
			GridPos = glm::uvec2(x, y);
		}

		virtual void OnUpdate(Timestep& ts) override
		{
			Entity::OnUpdate(ts);
		}

		static Cell* All[GridWidth][GridHeight];
		
		glm::ivec2 GridPos;
		int CurrentState;
		int NextState;
	};

}