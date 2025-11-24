#pragma once
#include "../Utils/Util.h"
#include "../GameData/GameData.h"
#include "GameBehaviour.h"
using namespace Behaviours;

GameBehaviour::GameBehaviour()
{
}

void GameBehaviour::Update(const float deltaTime, const float gameTime, const Inputspace::InputData &inputData, 
    Inputspace::InputHaptics &inputHaptics)
{
}

GameBehaviour::~GameBehaviour()
{
}