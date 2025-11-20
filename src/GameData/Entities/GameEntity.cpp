#pragma once
#include "../../Utils/Util.h"
#include "GameEntity.h"
#include "../GameData.h"
#include "../Components/GameComponent.h"
using namespace Game;

GameEntity::GameEntity(GameDataId::ID id) : GameDataId(id)
{
    components.resize(GameData::AllocationMagicNumbers.DEFAULT_COMPONENTS_PER_GAME_ENTITY_OBJECT, {});
}

void GameEntity::AddComponentId(GameDataId::ID component)
{
    if (component.IsCleared())
        std::throw_with_nested(std::exception(("[GameEntity][AddComponentId]\t You're trying to add a component which is invalid (cleared): \"{" +
                            component.PrintGlobalUID() + "}\" to Game Entity: \"{" + id.PrintGlobalUID() + "}\".").c_str()));

    size_t firstEmpty;
    bool foundEmpty = false;
    for (size_t i = 0u; i < components.size(); i++)
    {
        if (components[i].IsCleared())
        {
            if (!foundEmpty)
            {
                foundEmpty = true;
                firstEmpty = i;
            }
            continue;
        }

        if (components[i].Equals(component))
            return;
    }

    if (foundEmpty)
        components[firstEmpty] = component;
    else
        components.emplace_back(component);
}

void GameEntity::ClearComponentId(GameDataId::ID component)
{
    for (size_t i = 0u; i < components.size(); i++)
    {
        if (components[i].Equals(component))
        {
            components[i].Clear();
            break;
        }
    }
}

void GameEntity::ClearComponentIDs()
{
    for (GameDataId::ID component : components)
    {
        component.Clear();
    }
}

void GameEntity::NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage)
{
    if (!unsafe)
        ClearItemDependencies();
    ClearComponentIDs();
    GameDataId::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
}

void Game::GameEntity::NotifyItemVersionChanged()
{
    GameDataId::NotifyItemVersionChanged();
}

void Game::GameEntity::SetEnabled(bool enabled)
{
    this->isEnabled = enabled;
}

bool Game::GameEntity::IsEnabled() const
{
    return this->isEnabled;
}

std::vector<GameDataId::ID> GameEntity::GetAllComponentIDs() const
{
    return components;
}

size_t GameEntity::CountValidComponents() const
{
    size_t count = 0;
    for (size_t i = 0u; i < components.size(); i++)
    {
        if (components[i].IsCleared()) continue;

        count++;
    }
    return count;
}

void GameEntity::ClearItemDependencies()
{
    util::DebugLog("[GameEntity][ClearItem]\t " + id.PrintGlobalUID());

    if (id.IsCleared())
    {
        util::DebugError("[GameDataPool][ClearItem]\t There's a mistake: you're trying to clear id \"" +
                         id.PrintGlobalUID() +"\", which is already empty!");
    }

    // [tdbe] we need to clear (some of) the components of this <see cref="GameEntity"/>, and their references to us
    std::vector<GameDataId::ID> componentIDs = GetAllComponentIDs();
    for (GameDataId::ID compId : componentIDs)
    {
        if (compId.IsCleared())
            continue;

        GameComponent* comp = GameData::Instance().GetComponent(compId);
        if (comp == nullptr)
            continue;
        auto ownerIDs = comp->GetOwnerIDs();
        size_t validOwners = comp->CountValidOwners();

        // [tdbe] clear the convenience reference to this <see cref="GameEntity"/>, that the current component used to have.
        for (auto ownerId : ownerIDs)
        {
            if (ownerId == id)
            {
                comp->ClearOwnerId(ownerId);
                break;
            }
        }

        // [tdbe] and if this <see cref="GameEntity"/> was the sole owner of this component, then delete this component
        // completely. (mark it as free in its own data pool vector).
        // todo: maybe we don't want to do this for certain components like materials; but that implies having a proper
        // scene graph with resources.
        if (validOwners <= 1)
        {
            GameData::Instance().ClearComponent(compId);
        }
    }
}