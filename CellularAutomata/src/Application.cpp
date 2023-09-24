#include "Engine.h"
#include "Resource.h"

using namespace OrzoEngine;

#include "Game.h"
#include "Cell.h"

using namespace CellularAutomata;

std::vector<glm::ivec2> History;

bool IsWithinScreenBounds(glm::vec2 pos)
{
    return pos.x >= 0.0f && pos.y >= 0.0f && pos.x <= Engine::WindowWidth && pos.y <= Engine::WindowHeight;
}

void OnUpdate(Timestep& ts)
{
    //Pause/Unpause
    if (Input::GetKeyDown(KeyCode::Space))
    {
        if (Game::Paused)
            glfwSwapInterval(Engine::VerticalSyncBufferCount);
        else
            glfwSwapInterval(0);

        Game::Paused = !Game::Paused;
        History.clear();
    }

    if (Game::Paused == false)
    {
        //Speed Control
        if (Input::GetKeyDown(KeyCode::KeypadMinus))
        {
            if (Engine::VerticalSyncBufferCount < 20)
                glfwSwapInterval(Engine::VerticalSyncBufferCount++);
        }
        else if (Input::GetKeyDown(KeyCode::KeypadPlus))
        {
            if (Engine::VerticalSyncBufferCount > 1)
                glfwSwapInterval(Engine::VerticalSyncBufferCount--);
        }

        //Update
        for (int y = 0; y < Game::GridSize.y; y++)
        {
            for (int x = 0; x < Game::GridSize.x; x++)
            {
                Cell::All[x][y]->OnUpdate(ts);
            }
        }
    }
    else
    {
        //Undo
        if (Input::GetMouseButtonDown(KeyCode::Mouse1))
            History.clear();
        if (Input::GetKey(KeyCode::LeftControl) && Input::GetKeyDown(KeyCode::Z))
        {
            for (int i = 0; i < History.size(); i++)
                Cell::All[History[i].x][History[i].y]->NextState = CellState::Dead;
            History.clear();
        }

        //Paint
        glm::ivec2 gridPos;
        glm::vec2 mousePos = Input::GetMousePosition();
        mousePos.y = -mousePos.y + Engine::WindowHeight;
        if (IsWithinScreenBounds(mousePos))
        {
            gridPos.x = mousePos.x / (Game::CellSize + Game::CellInline);
            gridPos.y = mousePos.y / (Game::CellSize + Game::CellInline);

            if (Input::GetMouseButton(KeyCode::Mouse1))
            {
                Cell::All[gridPos.x][gridPos.y]->NextState = CellState::Alive;
                History.push_back(gridPos);
            }
        }

        //Reset
        if (Input::GetKeyDown(KeyCode::Backspace))
        {
            for (int y = 0; y < Game::GridSize.y; y++)
            {
                for (int x = 0; x < Game::GridSize.x; x++)
                {
                    Cell::All[x][y]->NextState = CellState::Dead;
                }
            }
        }

        //Save
        if (Input::GetKey(KeyCode::LeftControl) && Input::GetKeyDown(KeyCode::S))
        {
            std::cout << "!Saving not implemented yet!" << std::endl;
        }
    }

    //State Changes
    for (int y = 0; y < Game::GridSize.y; y++)
    {
        for (int x = 0; x < Game::GridSize.x; x++)
        {
            Cell::All[x][y]->ConfirmStateChanges();
        }
    }
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
    Engine::WindowWidth  = GridWidth * Game::CellSize + GridWidth * Game::CellInline + 2 * Game::CellInline;
    Engine::WindowHeight = GridHeight * Game::CellSize + GridHeight * Game::CellInline + 2 * Game::CellInline;
    Engine::EnableTests = false;
    Engine::EnableSoundTest = false;
    Engine::ListResourceDirectories = false;
    Engine::ShowInitializationOutput = false;
    Engine::WindowTitle = "Game of Life";
    Engine::AntiAliasingSampleCount = 4;

    Engine::UpdateCallback = OnUpdate;
    Engine::RenderCallback = OnRender;

    //Engine Init
    if (Engine::Init() < 0)
        return -1;

    //Game Init
    Engine::VerticalSyncBufferCount = 6;
    Shader shaderColor = Shader(OrzoEngine::Resource::Path("Color.shader"));
    Game::ShaderColor = &shaderColor;

    Material materialAlive = Material(Game::ShaderColor, Color::Color(0.69f, 0.69f, 0.69f), nullptr);
    Material materialDead = Material(Game::ShaderColor, Color::Color(0.11f, 0.11f, 0.11f), nullptr);
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

    std::cout << "INSTRUCTIONS:" << std::endl << std::endl;
    std::cout << "Paint the cells to life using your mouse" << std::endl;
    std::cout << "Ctrl+Z to undo your last stroke" << std::endl;
    //std::cout << "Ctrl+S to save your painting" << std::endl; //NOT IMPLEMENTED YET
    std::cout << "Press Space to pause/unpause the simulation" << std::endl;
    std::cout << "Num+ and Num- to adjust simulation speed" << std::endl;
    std::cout << "Backspace annihilates all the cells while paused" << std::endl;

    //Run
    return Engine::Run();
}