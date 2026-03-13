#include "Material.h"
#include "../GameData.h"

using namespace Game;

void Material::SetName(std::string name)
{
    auto it = GameData::Instance().namedMaterialComponentIDs.right.find(id);
    if(it == GameData::Instance().namedMaterialComponentIDs.right.end())
    {
        GameData::Instance().namedMaterialComponentIDs.insert({name, id});
    }
    else
    {
        auto it = GameData::Instance().namedMaterialComponentIDs.left.find(GetName());
        GameData::Instance().namedMaterialComponentIDs.left.replace_key(it, name);
    }
}

std::string Material::GetName() const
{
    auto it = GameData::Instance().namedMaterialComponentIDs.right.find(id);
    if(it != GameData::Instance().namedMaterialComponentIDs.right.end())
        return GameData::Instance().namedMaterialComponentIDs.right.at(id);
    else
        return "NO_NAME_MATERIAL";
}