#pragma once
#include "../../Utils/Util.h"
#include "GameComponent.h"
#include "../Entities/GameEntity.h"
using namespace Game;

/// [tdbe] You shouldn't call this constructor directly, instead Add (emplace (or reuse)) with the <see
/// cref="GameDataPool"/>. And depending on type of Component, you probably should do it via the creation of a new <see
/// cref="GameEntityObject"/>.
GameComponent::GameComponent(GameDataId::ID id, GameDataId::ID owner) : GameDataId(id)
{
    owners = std::vector<GameDataId::ID>(1);
    if (!owner.IsCleared())
        owners.emplace_back(owner);
}

std::vector<GameDataId::ID> GameComponent::GetOwnerIDs() const
{
    return owners;
}

size_t GameComponent::CountValidOwners() const
{
    size_t count = 0;
    for (size_t i = 0u; i < owners.size(); i++)
    {
        if (owners[i].version == GameDataId::FREE) continue;

        count++;
    }
    return count;
}

void GameComponent::AddOwnerId(GameDataId::ID owner)
{
    if (owner.IsCleared())
        std::throw_with_nested(std::exception(
            ("[GameComponent][AddOwnerId]\t You're trying to add an owner which is invalid (cleared): \"{" +
             owner.PrintGlobalUID() + "}\" to Game Component: \"{" + id.PrintGlobalUID() + "}\".")
                .c_str()));

    size_t firstEmpty;
    bool foundEmpty = false;
    for (size_t i = 0u; i < owners.size(); i++)
    {
        if (owners[i].version == GameDataId::FREE)
        {
            if (!foundEmpty)
            {
                foundEmpty = true;
                firstEmpty = i;
            }
            continue;
        }

        if (owners[i].Equals(owner))
            return;
    }

    if (foundEmpty)
        owners[firstEmpty] = owner;
    else
        owners.emplace_back(owner);
}

void GameComponent::ClearOwnerId(GameDataId::ID owner)
{
    for (size_t i = 0u; i < owners.size(); i++)
    {
        if (owners[i].Equals(owner))
        {
            owners[i].Clear();
            break;
        }
    }
};

void GameComponent::ClearOwnerIDs()
{
    for (size_t i = 0u; i < owners.size(); i++)
    {
        owners[i].Clear();
    }
};

/// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
/// todo: this should be restricted to <see cref"GameDataPool"/>
void GameComponent::NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage)
{
    if (!unsafe)
        ClearItemDependencies();
    ClearOwnerIDs();
    GameDataId::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
}

void GameComponent::NotifyItemVersionChanged()
{
    GameDataId::NotifyItemVersionChanged();
}

void GameComponent::ClearItemDependencies()
{
    util::DebugLog("[GameComponent][ClearItem]\t " + id.PrintGlobalUID());

    if (id.IsCleared())
    {
        util::DebugError("[GameComponent][ClearItem]\t There's a mistake: you're trying to clear id \"" +
                         id.PrintGlobalUID() + "\", which is already empty!");
    }

    // [tdbe] we need to clear (some of) the owners of this <see cref="GameComponent"/>, and their references to us
    std::vector<GameDataId::ID> ownerIDs = GetOwnerIDs();
    for (GameDataId::ID ownerId : ownerIDs)
    {
        if (ownerId.IsCleared())
            continue;

        GameEntity* owningEntity = GameData::Instance().GetEntity(ownerId);
        if (owningEntity == nullptr)
            continue;
        auto componentIDs = owningEntity->GetAllComponentIDs();

        // [tdbe] clear the convenience reference to this <see cref="GameComponent"/>, that the current entity used to have.
        for (auto componentId : componentIDs)
        {
            if (componentId == id)
            {
                owningEntity->ClearComponentId(ownerId);
                break;
            }
        }
    }
}

GameComponent::~GameComponent() 
{
}
