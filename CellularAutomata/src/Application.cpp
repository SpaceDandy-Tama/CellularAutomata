#include "Engine.h"
#include "Resource.h"

using namespace OrzoEngine;

#include "Game.h"
#include "Cell.h"

using namespace CellularAutomata;

void OnUpdate(Timestep& ts)
{

}

void OnRender()
{
    for (int y = 0; y < Game::GridSize.y; y++)
    {
        for (int x = 0; x < Game::GridSize.x; x++)
        {
            Cell::All[x][y]->OnRender();
        }
    }
}

int main(void)
{
    //Engine Setup
#if !_DEBUG
    Engine::IsFullscreen = true;
#else
    Engine::WindowWidth = 690;
    Engine::WindowHeight = 690;
#endif
    Engine::EnableTests = false;
    Engine::WindowTitle = "Game of Life";
    Engine::AntiAliasingSampleCount = 4;
    Engine::VerticalSyncBufferCount = 1;

    Engine::UpdateCallback = OnUpdate;
    Engine::RenderCallback = OnRender;

    //Engine Init
    if (Engine::Init() < 0)
        return -1;

    //Game Init
    Shader shaderColor = Shader(OrzoEngine::Resource::Path("Color.shader"));
    Game::ShaderColor = &shaderColor;

    Material materialAlive = Material(Game::ShaderColor, Color::White, nullptr);
    Material materialDead = Material(Game::ShaderColor, Color::Color(0.1f, 0.1f, 0.1f), nullptr);
    Game::MaterialAlive = &materialAlive;
    Game::MaterialDead = &materialDead;

    for (int y = 0; y < Game::GridSize.y; y++)
    {
        for (int x = 0; x < Game::GridSize.x; x++)
        {
            Cell::All[x][y] = new Cell(x, y);
        }
    }

    Camera::GetCamera().m_Position = glm::vec3(Game::GridSize.x, Game::GridSize.y, 0) * (Game::CellSize + Game::CellInline) * 0.5f;

    //Run
    return Engine::Run();
}