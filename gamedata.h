#pragma once
#include "assetmanager.h"
#include "statemanager.h"

struct GameData
{
    AssetManager assets;
    StateMachine states;
};

using GameDataRef = std::shared_ptr<GameData>;