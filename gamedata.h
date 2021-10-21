#pragma once
#include "assetmanager.h"
#include "statemachine.h"
#include "score.h"

struct GameData
{
    AssetManager assets;
    StateMachine states;
    Score score;
};

using GameDataRef = std::shared_ptr<GameData>;