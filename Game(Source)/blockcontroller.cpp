#include "blockcontroller.h"

using namespace LumenAusf;

BlockController::~BlockController () { std::cerr << "removed \"BlockController\" from " + gameObject->name << std::endl; }

void BlockController::Awake () {}

void BlockController::Start () {}

void BlockController::Update () {}

void BlockController::onEnable () {}

void BlockController::onDisable () {}

void BlockController::onDestroy () { Map::Instance ()->field[num / 9][num % 9] = nullptr; }

void BlockController::Destroy () {}
