#include "Engine.h"
#include "Resource.h"

using namespace OrzoEngine;

void OnUpdate(Timestep& ts)
{

}

void OnRender()
{

}

int main(void)
{
    //Engine Setup
#if !_DEBUG
    Engine::IsFullscreen = true;
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

    //Run
    return Engine::Run();
}