
#include "../../Utils/Util.h"
#include "Parent.h"
#include "Children.h"
#include "Transform.h"
#include "../Entities/GameEntityObject.h"

using namespace Game;

Parent::Parent(GameDataId::ID id, GameDataId::ID owner) : GameComponent(id, owner)
{
    parentId = GameDataId::ID();
}

GameEntity* Parent::GetOwner() const
{
    std::vector<GameDataId::ID> ownerIDs = GetOwnerIDs();
    GameEntity* found = nullptr;
    if(!ownerIDs[0].IsCleared())
    {
        found = GameData::Instance().GetEntity(ownerIDs[0]);
    }
    return found;
}

void Parent::SetParent(GameDataId::ID newParentId, bool ripple)
{
    if (parentId == newParentId)
        return;

    if (parentId.version != GameDataId::FREE)
    {
        ClearParent(ripple);
    }

    parentId = newParentId;
    if(ripple)
        AddOwnerToChildrenOfParent();
        
    // [tdbe] must update the Transform Local TRS (position (translation), rotation, scale)
    auto owner = GameData::Instance().GetEntity(GetOwner()->id);
    auto myTransform = owner->GetComponentByTypeIndex<Transform>();
    auto parentTransform = GameData::Instance().GetEntity(parentId)->GetComponentByTypeIndex<Transform>();
    myTransform->OnParentWorldPoseUpdated(parentTransform->GetWorldPose());
}

void Parent::ClearParent(bool ripple)
{
    if(ripple)
        RemoveOwnerFromChildrenOfParent();
    parentId = GameDataId::ID();
    
    // [tdbe] must update the Transform Local TRS (position (translation), rotation, scale)
    auto owner = GameData::Instance().GetEntity(GetOwner()->id);
    auto myTransform = owner->GetComponentByTypeIndex<Transform>();
    myTransform->OnUnparent();
}


void Parent::RemoveOwnerFromChildrenOfParent()
{
    GameEntity* owner = GetOwner();
    auto childrenComponentOfParentEntity = 
        GameData::Instance().GetEntity(parentId)->GetComponentByTypeIndex<Children>();
    if(childrenComponentOfParentEntity->HasChild(owner->id))
    {
        // [tdbe] don't ripple: don't loop back to here, we're cleaning ourselves up.
        childrenComponentOfParentEntity->ClearChild(owner->id, false);
    }
}

void Parent::AddOwnerToChildrenOfParent()
{
    GameEntity* owner = GetOwner();
    auto childrenComponentOfParentEntity = 
        GameData::Instance().GetEntity(parentId)->GetComponentByTypeIndex<Children>();
    // [tdbe] don't ripple: don't loop back to here.
    childrenComponentOfParentEntity->AddChild(owner->id, false);
}


Parent::~Parent()
{
}