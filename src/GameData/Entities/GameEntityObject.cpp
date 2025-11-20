#pragma once
#include "../../Utils/Util.h"
#include "GameEntityObject.h"
#include "../GameData.h"

using namespace Game;

std::unordered_map<std::string, GameEntityObject::EventType> GameEntityObject::OnGameEntityObjectAddedHandlers;
std::unordered_map<std::string, GameEntityObject::EventType> GameEntityObject::OnGameEntityObjectRemovedHandlers;

GameEntityObject::GameEntityObject(GameDataId::ID id,
                                   bool isVisible,
                                   std::string name,
                                   void (*runExtensions)(GameEntityObject* owner))
: GameEntity(id)
{
    this->name = name;
    isVisible = isVisible;

    if (runExtensions != nullptr)
    {
        runExtensions(this);
    }

    //RaiseGameEntityObjectAdded();
}

void GameEntityObject::NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage)
{
    util::DebugLog("[GameEntityObject]\t clearing this item: " + name + "; id: " + id.PrintGlobalUID());
    RaiseGameEntityObjectRemoved();
    name = "game object";
    GameEntity::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
}

void Game::GameEntityObject::NotifyItemVersionChanged()
{
    GameEntity::NotifyItemVersionChanged();
    RaiseGameEntityObjectAdded();
}

void GameEntityObject::SetName(std::string name)
{
    this->name = name;
}

std::string GameEntityObject::GetName() const
{
    return this->name;
}


void GameEntityObject::RaiseGameEntityObjectAdded()
{
    for (auto& handler : OnGameEntityObjectAddedHandlers)
    {
        handler.second(this);
    }
}

void GameEntityObject::RaiseGameEntityObjectRemoved()
{
    for (auto& handler : OnGameEntityObjectRemovedHandlers)
    {
        handler.second(this);
    }
}

GameEntityObject::~GameEntityObject()
{
}