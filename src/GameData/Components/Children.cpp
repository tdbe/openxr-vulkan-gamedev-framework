#include "../../Utils/Util.h"
#include "Children.h"
#include "Parent.h"
#include "ARoot.h"
#include "../Entities/GameEntityObject.h"

using namespace Game;

Children::Children(GameDataId::ID id, GameDataId::ID owner) : GameComponent(id, owner)
{
}

GameEntity* Children::GetOwner() const
{
    std::vector<GameDataId::ID> ownerIDs = GetOwnerIDs();
    GameEntity* found = nullptr;
    if(!ownerIDs[0].IsCleared())
    {
        found = GameData::Instance().GetEntity(ownerIDs[0]);
    }
    return found;
}

void Children::AddOwnerToParentOfChild(const GameDataId::ID childId)
{
    GameEntity* owner = GetOwner();
    auto parentComponentOfChildEntity = 
        GameData::Instance().GetEntity(childId)->GetComponentByTypeIndex<Parent>();
    // [tdbe] don't ripple: don't loop back to here.
    parentComponentOfChildEntity->SetParent(owner->id, false);
}

void Children::RemoveOwnerFromParentOfChild(const GameDataId::ID childId)
{
    auto parentComponentOfChildEntity = 
        GameData::Instance().GetEntity(childId)->GetComponentByTypeIndex<Parent>();
    // [tdbe] don't ripple: don't loop back to here, we're cleaning ourselves up.
    parentComponentOfChildEntity->ClearParent(false);
}

void Children::RemoveOwnerFromParentOfChildren()
{
    GameEntity* owner = GetOwner();
    for(auto childId : *children)
    {
        // [tdbe] no, we are not clearing children while iterating.
        RemoveOwnerFromParentOfChild(childId);
    }
}

void Children::ClearRootAttributeComponent()
{
    auto owner = GameData::Instance().GetEntity(GetOwner()->id);
    ARoot* rootAttrib = owner->GetComponentByTypeIndex<ARoot>();
    if(rootAttrib != nullptr) 
    {
        owner->ClearComponentId(rootAttrib->id);
        rootAttrib->ClearOwnerId(owner->id);
        GameData::Instance().ClearComponent(rootAttrib->id, true);
    }    
}

Children::~Children()
{
}