#pragma once
#include "../GameDataId.h"
#include "GameComponent.h"
#include "../../Utils/Util.h"
using namespace util;

namespace Game
{
/// [tdbe] AABB (axis-aligned bounding box) of model (mesh), and possibly other bounds. 
/// (The values here are in object-space (relative to the object's centre) and are not processed by the entity's Transform Matrix.)
/// (A physics collider would be another separate component that maybe also is aware of the bounds from here.)
/// [RequireComponentOnOwnerEntities(typeof<Model>)]
/// [RequireOwnerRestriction(1)]
struct Bounds final : public GameComponent
{
  public:
    /// [tdbe] TODO: visualize bounds
    struct AABB
    {
        glm::vec3 min;
        glm::vec3 max;

        std::array<glm::vec3,8> GetAlCorners()
        {
            std::array<glm::vec3, 8> corners {
                    glm::vec3(min.x, min.y, min.z), 
                    glm::vec3(max.x, min.y, min.z), 
                    glm::vec3(min.x, max.y, min.z),
                    glm::vec3(max.x, max.y, min.z), 
                    glm::vec3(min.x, min.y, max.z), 
                    glm::vec3(max.x, min.y, max.z),
                    glm::vec3(min.x, max.y, max.z), 
                    glm::vec3(max.x, max.y, max.z)
                   };
            return corners;
        };

        void SetVals(const glm::vec3 min, const glm::vec3 max)
        {
            this->min = min;
            this->max = max;
        };

        glm::vec3 GetCenter() const
        {
            return (min + max) / 2.0f;
        };

        glm::vec3 Size() const
        {
            return max - min;
        };

        bool Contains(const glm::vec3 point) const
        {
            return (point.x >= min.x && point.x <= max.x) && 
                   (point.y >= min.y && point.y <= max.y) &&
                   (point.z >= min.z && point.z <= max.z);
        };

        bool Intersects(const AABB other) const
        {
            return (min.x <= other.max.x && max.x >= other.min.x) && 
                   (min.y <= other.max.y && max.y >= other.min.y) &&
                   (min.z <= other.max.z && max.z >= other.min.z);
        };

        bool Intersects(const Plane& plane)
        {
            std::array<glm::vec3, 8> corners = GetAlCorners();

            // [tdbe] check if any opposite points are on opposite sides of the plane
            for (int i = 0; i < 8; i++)
            {
                for (int j = i + 1; j < 8; j++)
                {
                    // [tdbe] Is point in front of plane means: pretend the AABB.point is a vector 
                    // from world origin, and project it onto the plane's normal 
                    // to see if it's in the right direction. Then subtract the plane's distance 
                    // to see if it isn't under the plane.
                    float dot1 = glm::dot(plane.normal, corners[i]) - plane.distance;
                    float dot2 = glm::dot(plane.normal, corners[j]) - plane.distance;
                    if (dot1 * dot2 <= 0.0f)
                    {
                        return true;
                    }
                }
            }
            return false;
        };

        bool IsInFrontOfPlane(const Plane plane)
        {
            std::array<glm::vec3, 8> corners = GetAlCorners();

            // [tdbe] check if any point is behind the plane
            for (int i = 0; i < 8; i++)
            {
                float dot = glm::dot(plane.normal, corners[i]) - plane.distance;
                if (dot <= 0.0f)
                {
                    return false;
                }
            }

            return true;
        };

        AABB(const glm::vec3 min = glm::vec3(0.0f), const glm::vec3 max = glm::vec3(0.0f)) : 
            min(min), max(max)
        {
        };
    } aabb;

    void SetBoundsAABB(const Model* model)
    {
        aabb.SetVals(model->minPointAABB, model->maxPointAABB);
    };

    void SetBoundsAABB(glm::vec3 minPoint, glm::vec3 maxPoint)
    {
        aabb.SetVals(minPoint, maxPoint);
    }

    AABB GetBounds() const
    {
        return aabb;
    };

    AABB* GetBoundsPtr()
    {
        return &aabb;
    };

    void NotifyModelChanged(const Model* model)
    {
        SetBoundsAABB(model);
    };

    std::vector<GameEntity*> GetOwners() const
    {
        std::vector<GameDataId::ID> ownerIDs = GetOwnerIDs();
        std::vector<GameEntity*> foundVec = std::vector<GameEntity*>();
        for (GameDataId::ID entId : ownerIDs)
        {
            auto comp = GameData::Instance().GetEntity(entId);
            foundVec.emplace_back(comp);
        }
        return foundVec;
    };

    /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
    /// todo: this should be restricted to <see cref"GameDataPool"/>
    virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override
    {
        util::DebugLog("[Component][Bounds]\t clearing this item: " + this->id.PrintGlobalUID());
        GameComponent::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
        aabb.SetVals(glm::vec3(0.0f), glm::vec3(0.0f));
    };

    /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
    /// todo: this should be restricted to <see cref"GameDataPool"/>
    virtual void NotifyItemVersionChanged() override
    {
        GameComponent::NotifyItemVersionChanged();
    };

    /// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
    /// See <see cref="GameData::LoadGameWorld"/>. And remember to add it to some <see cref="GameEntity"/> or <see
    /// cref="GameEntityObject"/>.
    Bounds(GameDataId::ID id = {}, GameDataId::ID owner = {}) : GameComponent(id, owner) 
    {
    };
    ~Bounds() {};
};
} // namespace Game