#pragma once

#include "Entity.h"

#include "Game.h";

namespace CellularAutomata
{
	enum CellState
	{
		Dead = 0,
		Alive = 1
	};

	class Cell : public Entity
	{
	public:
		Cell(int x, int y) : Entity(glm::vec3(x + Game::CellOffset, y + Game::CellOffset, 0) * (Game::CellSize + Game::CellInline), glm::quat(), glm::vec3(Game::CellSize), Mesh::Quad, Game::MaterialDead)
		{
			CurrentState = NextState = CellState::Dead;
			GridPos = glm::uvec2(x, y);
		}

		static Cell* All[GridWidth][GridHeight];

		virtual void OnUpdate(Timestep& ts) override
		{
			Entity::OnUpdate(ts);

			if (CurrentState != NextState)
			{
				CurrentState = NextState;

				if (CurrentState == CellState::Alive)
					m_Material = Game::MaterialAlive;
				else
					m_Material = Game::MaterialDead;
			}

			if (Game::Paused)
				return;

			int numAlive = 0;

			CheckNeighboor(glm::ivec2(GridPos.x - 1, GridPos.y - 1)	, numAlive);
			CheckNeighboor(glm::ivec2(GridPos.x - 1, GridPos.y)		, numAlive);
			CheckNeighboor(glm::ivec2(GridPos.x - 1, GridPos.y + 1)	, numAlive);
			CheckNeighboor(glm::ivec2(GridPos.x + 1, GridPos.y - 1)	, numAlive);
			CheckNeighboor(glm::ivec2(GridPos.x + 1, GridPos.y)		, numAlive);
			CheckNeighboor(glm::ivec2(GridPos.x + 1, GridPos.y + 1)	, numAlive);
			CheckNeighboor(glm::ivec2(GridPos.x, GridPos.y - 1)		, numAlive);
			CheckNeighboor(glm::ivec2(GridPos.x, GridPos.y + 1)		, numAlive);

			if (CurrentState == CellState::Alive)
			{
				if (numAlive < 2 || numAlive > 3)
					NextState = CellState::Dead;
			}
			else if (CurrentState == CellState::Dead)
			{
				if (numAlive == 3)
					NextState = CellState::Alive;
			}
		}

		void CheckNeighboor(glm::ivec2 gridPos, int& numAlive)
		{
			bool boundsCheck = gridPos.x >= 0 && gridPos.y >= 0 && gridPos.x < Game::GridSize.x && gridPos.y < Game::GridSize.y;
			if (boundsCheck && Cell::All[gridPos.x][gridPos.y]->CurrentState == CellState::Alive)
			{
				numAlive++;
			}
		}
		
		glm::ivec2 GridPos;
		int CurrentState;
		int NextState;
	};

}