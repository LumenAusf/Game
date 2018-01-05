#include "gameovercontroller.h"

using namespace LumenAusf;

GameOverController::~GameOverController () { std::cerr << "removed \"GameOverController\" from " + gameObject->name << std::endl; }

void GameOverController::Awake () {}

void GameOverController::Start () {}

void GameOverController::Update () {}

void GameOverController::onEnable () {}

void GameOverController::onDisable () {}

void GameOverController::onDestroy ()
{
    std::cerr << "GameOver" << std::endl;
    *running = false;
}

void GameOverController::Destroy () { this->~GameOverController (); }

void GameOverController::SetAnchor (bool* a) { running = a; }
