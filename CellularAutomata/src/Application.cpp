#include "Engine.h"
#include "Resource.h"

using namespace OrzoEngine;

#include "Module.h"
#include "Modules/Habitat.h"
#include "Modules/Weapons.h"
#include "Modules/Magnets.h"
#include "Modules/SolarPV.h"
#include "Modules/Nuclear.h"
#include "Modules/HangarP.h"

#include "CameraControl.h"
#include "Game.h"

#include "Menu.h"
#include "Menus/MenuMain.h"
#include "Menus/MenuPause.h"
#include "Menus/MenuHUD.h"

using namespace SpacewardDefender;

CameraControl CamControl = CameraControl(100.0f);

void OnUpdate(Timestep& ts)
{
    if (Game::MainMenu->Active || Game::PauseMenu->Active)
    {
        if (Game::MainMenu->Active)
            Game::MainMenu->Update(ts);
        else if (Game::PauseMenu->Active)
            Game::PauseMenu->Update(ts);

        return;
    }

    for (Module*& module : Module::All)
        module->OnUpdate(ts);
    
    CamControl.Update(ts);
    Game::HUDMenu->Update(ts);
}

void OnRender()
{
    for (Module*& module : Module::All)
        module->OnRender();

    if (Game::HUDMenu->Active)
        Game::HUDMenu->Render();

    if (Game::MainMenu->Active)
        Game::MainMenu->Render();
    else if (Game::PauseMenu->Active)
        Game::PauseMenu->Render();
}

int main(void)
{
    //Engine Setup
#if !_DEBUG
    Engine::IsFullscreen = true;
#endif
    Engine::EnableTests = false;
    Engine::WindowTitle = "Spaceward Defender";
    Engine::AntiAliasingSampleCount = 4;
    Engine::VerticalSyncBufferCount = 1;
    Resource::AddDir("../res/sprites/");

    Engine::UpdateCallback = OnUpdate;
    Engine::RenderCallback = OnRender;

    //Engine Init
    if (Engine::Init() < 0)
        return -1;

    //Shaders
    Shader shaderBasic = Shader(OrzoEngine::Resource::Path("Basic.shader"));
    Shader shaderColor = Shader(OrzoEngine::Resource::Path("Color.shader"));
    Shader shaderText = Shader(OrzoEngine::Resource::Path("Text.shader"));
    Game::ShaderBasic = &shaderBasic;
    Game::ShaderColor = &shaderColor;
    Game::ShaderText = &shaderText;

    //Texture
    Game::TextureHabitat = new Texture(OrzoEngine::Resource::Path("module1.png"));
    Game::TextureWeapons = new Texture(OrzoEngine::Resource::Path("module2.png"));
    Game::TextureMagnets = new Texture(OrzoEngine::Resource::Path("module3.png"));
    Game::TextureSolarPV = new Texture(OrzoEngine::Resource::Path("module4.png"));
    Game::TextureNuclear = new Texture(OrzoEngine::Resource::Path("module5.png"));
    Game::TextureHangarP = new Texture(OrzoEngine::Resource::Path("SpaceModule6Graph0001.png"));

    Game::TextureFighter1 = new Texture(OrzoEngine::Resource::Path("Fighter1.png"));
    Game::TextureFighter2 = new Texture(OrzoEngine::Resource::Path("Fighter2.png"));
    Game::TextureFighter3 = new Texture(OrzoEngine::Resource::Path("Fighter3.png"));

    Game::TextureShip1 = new Texture(OrzoEngine::Resource::Path("Ship1.png"));
    Game::TextureShip2 = new Texture(OrzoEngine::Resource::Path("Ship2.png"));
    Game::TextureShip3 = new Texture(OrzoEngine::Resource::Path("Ship3.png"));
    Game::TextureShip4 = new Texture(OrzoEngine::Resource::Path("Ship4.png"));

    //Materials
    Material materialHabitat = Material(Game::ShaderBasic, Color::White, Game::TextureHabitat);
    Material materialWeapons = Material(Game::ShaderBasic, Color::White, Game::TextureWeapons);
    Material materialMagnets = Material(Game::ShaderBasic, Color::White, Game::TextureMagnets);
    Material materialSolarPV = Material(Game::ShaderBasic, Color::White, Game::TextureSolarPV);
    Material materialNuclear = Material(Game::ShaderBasic, Color::White, Game::TextureNuclear);
    Material materialHangarP = Material(Game::ShaderBasic, Color::White, Game::TextureHangarP);
    Habitat::Material = &materialHabitat;
    Weapons::Material = &materialWeapons;
    Magnets::Material = &materialMagnets;
    SolarPV::Material = &materialSolarPV;
    Nuclear::Material = &materialNuclear;
    HangarP::Material = &materialHangarP;

    Habitat habitat = Habitat(); //temp

    //Game
    MenuMain mainMenu = MenuMain(true);
    MenuPause pauseMenu = MenuPause();
    MenuHUD hudMenu = MenuHUD();
    Game::MainMenu = &mainMenu;
    Game::PauseMenu = &pauseMenu;
    Game::HUDMenu = &hudMenu;
    
    Game::Credits = 5000;
    Game::Energy = 0.0f;

    //Run
    return Engine::Run();
}