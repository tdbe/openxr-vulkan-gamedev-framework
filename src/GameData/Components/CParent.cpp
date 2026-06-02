
#include "../../Utils/Util.h"
#include "CParent.h"
#include "CChildren.h"
#include "CTransform.h"
#include "../Entities/GameEntityObject.h"

using namespace Game;

CParent::CParent(GameDataId::ID id, GameDataId::ID owner) : GameComponent(id, owner)
{
    parentId = GameDataId::ID();
}

GameEntity* CParent::GetOwner() const
{
    std::vector<GameDataId::ID> ownerIDs = GetOwnerIDs();
    GameEntity* found = nullptr;
    if(!ownerIDs[0].IsCleared())
    {
        found = GameData::Instance().GetEntity(ownerIDs[0]);
    }
    return found;
}

void CParent::SetParent(GameDataId::ID newParentId, bool ripple)
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
        
    // [tdbe] must update the CTransform Local TRS (position (translation), rotation, scale)
    auto owner = GameData::Instance().GetEntity(GetOwner()->id);
    auto myTransform = owner->GetComponentByTypeIndex<CTransform>();
    auto parentTransform = GameData::Instance().GetEntity(parentId)->GetComponentByTypeIndex<CTransform>();
    myTransform->OnParentWorldPoseUpdated(parentTransform->GetWorldPose());
}

void CParent::ClearParent(bool ripple)
{
    if(ripple)
        RemoveOwnerFromChildrenOfParent();
    parentId = GameDataId::ID();
    
    // [tdbe] must update the CTransform Local TRS (position (translation), rotation, scale)
    auto owner = GameData::Instance().GetEntity(GetOwner()->id);
    auto myTransform = owner->GetComponentByTypeIndex<CTransform>();
    myTransform->OnUnparent();
}


void CParent::RemoveOwnerFromChildrenOfParent()
{
    GameEntity* owner = GetOwner();
    auto childrenComponentOfParentEntity = 
        GameData::Instance().GetEntity(parentId)->GetComponentByTypeIndex<CChildren>();
    if(childrenComponentOfParentEntity->HasChild(owner->id))
    {
        // [tdbe] don't ripple: don't loop back to here, we're cleaning ourselves up.
        childrenComponentOfParentEntity->ClearChild(owner->id, false);
    }
}

void CParent::AddOwnerToChildrenOfParent()
{
    GameEntity* owner = GetOwner();
    auto childrenComponentOfParentEntity = 
        GameData::Instance().GetEntity(parentId)->GetComponentByTypeIndex<CChildren>();
    // [tdbe] don't ripple: don't loop back to here.
    childrenComponentOfParentEntity->AddChild(owner->id, false);
}


CParent::~CParent()
{
}