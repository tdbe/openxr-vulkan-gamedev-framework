
#include "../../Utils/Util.h"
#include "GameEntityObject.h"
#include "../GameData.h"

using namespace Game;

std::unordered_map<std::string, GameEntityObject::EventType> GameEntityObject::OnGameEntityObjectAddedHandlers;
std::unordered_map<std::string, GameEntityObject::EventType> GameEntityObject::OnGameEntityObjectRemovedHandlers;

GameEntityObject::GameEntityObject(GameDataId::ID id,
                                   void (*runExtensions)(GameEntityObject* owner))
: GameEntity(id)
{

    if (runExtensions != nullptr)
    {
        runExtensions(this);
    }

    //RaiseGameEntityObjectAdded();
}

void GameEntityObject::NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage)
{
    #ifdef DEBUG_VERBOSE
    if(!unsafe)
        util::DebugLog("[GameEntityObject]\t clearing this item: " + GetName() + "; id: " + id.PrintGlobalUID());
    #endif
    RaiseGameEntityObjectRemoved();
    GameEntity::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
}

void Game::GameEntityObject::NotifyItemVersionChanged()
{
    GameEntity::NotifyItemVersionChanged();
    RaiseGameEntityObjectAdded();
}

void GameEntityObject::SetName(std::string name)
{
    auto it = GameData::Instance().namedGameObjectIDs.right.find(id);
    if(it == GameData::Instance().namedGameObjectIDs.right.end())
    {
        GameData::Instance().namedGameObjectIDs.insert({name, id});
    }
    else
    {
        auto it = GameData::Instance().namedGameObjectIDs.left.find(GetName());
        GameData::Instance().namedGameObjectIDs.left.replace_key(it, name);
    }
}

std::string GameEntityObject::GetName() const
{
    auto it = GameData::Instance().namedGameObjectIDs.right.find(id);
    if(it != GameData::Instance().namedGameObjectIDs.right.end())
        return GameData::Instance().namedGameObjectIDs.right.at(id);
    else
        return "NO_NAME_GAME_ENTITY_OBJECT";
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