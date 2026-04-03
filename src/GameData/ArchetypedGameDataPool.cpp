
#include "ArchetypedGameDataPool.h"
#include "GameData.h"

using namespace Game;

bool UIDTypeCheckHelper::IsTypeUIDEntity(uint64_t uid)
{
    return uid <= GameData::TypeUIDs::GAME_ENTITY_OBJECTS;
}

// [tdbe] crickets here because of generic functions that need to be seen in creation/header
