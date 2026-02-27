
#include "../../Utils/Util.h"
#include "Parent.h"
#include "Children.h"
#include "Transform.h"
#include "ARoot.h"
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
    myTransform->ParentTo(parentTransform->GetWorldPose());
    
    // [tdbe] if it has a parent, it can't be a root object
    ARoot* rootAttrib = owner->GetComponentByTypeIndex<ARoot>();
    if(rootAttrib != nullptr) 
    {
        owner->ClearComponentId(rootAttrib->id);
        rootAttrib->ClearOwnerId(owner->id);
        GameData::Instance().ClearComponent(rootAttrib->id, true);
    }
}

void Parent::ClearParent(bool ripple)
{
    if(ripple)
        RemoveOwnerFromChildrenOfParent();
    parentId = GameDataId::ID();
    
    // [tdbe] must update the Transform Local TRS (position (translation), rotation, scale)
    auto owner = GameData::Instance().GetEntity(GetOwner()->id);
    auto myTransform = owner->GetComponentByTypeIndex<Transform>();
    myTransform->Unparent();
    
    // [tdbe] if it doesn't have a parent and does have childen, it is a root object
    auto children = owner->GetComponentByTypeIndex<Children>();
    ARoot* rootAttrib = owner->GetComponentByTypeIndex<ARoot>();
    if(rootAttrib == nullptr && children->HasChildren())
    {
        rootAttrib = GameData::Instance().entityObjectsWorld->rootAttributeComponents->GetFreeItem();
        rootAttrib->AddOwnerId(owner->id);
        owner->AddComponentId(rootAttrib->id);
    }
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