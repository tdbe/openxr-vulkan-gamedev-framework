#include "CModel.h"
#include "../GameData.h"

using namespace Game;

/// [tdbe] this is just a wrapper for scriptable <see cref="GameData"/> it shouldn't be here but people are used to it here.
void CModel::SetName(std::string name)
{
    auto it = GameData::Instance().namedModelComponentIDs.right.find(id);
    if(it == GameData::Instance().namedModelComponentIDs.right.end())
    {
        GameData::Instance().namedModelComponentIDs.insert({name, id});
    }
    else
    {
        auto it = GameData::Instance().namedModelComponentIDs.left.find(GetName());
        GameData::Instance().namedModelComponentIDs.left.replace_key(it, name);
    }
}

/// [tdbe] this is just a wrapper for scriptable <see cref="GameData"/> it shouldn't be here but people are used to it here.
std::string CModel::GetName() const
{
    auto it = GameData::Instance().namedModelComponentIDs.right.find(id);
    if(it != GameData::Instance().namedModelComponentIDs.right.end())
        return GameData::Instance().namedModelComponentIDs.right.at(id);
    else
        return "NO_NAME_MODEL";
}