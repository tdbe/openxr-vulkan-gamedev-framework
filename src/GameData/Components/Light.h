#pragma once
#include <glm/vec3.hpp>

#include "GameComponent.h"

using namespace Game;

namespace Game
{
    /// [tdbe] Multiple types of lights (incl volumetric).
    /// [RequireComponentOnOwnerEntities(typeof<Transform>))]
    /// [RequireOwnerRestriction(1)]
    struct Light : public GameComponent
    {
      public:
        static const struct LightTypes
        {
            static const int LIGHT_TYPE_DIRECTIONAL = 0;
            static const int LIGHT_TYPE_POINT = 1;
            static const int LIGHT_TYPE_SPHERE = 2;
            static const int LIGHT_TYPE_TUBE = 3;
            static const int LIGHT_TYPE_CUBE = 4;
            static const int LIGHT_TYPE_QUAD = 5;
            static const int LIGHT_TYPE_DISC = 6;

            static const int LIGHT_TYPE_TENTACLE = 103;
        } lightTypes;

        GameEntity* GetOwner() const;

        /// [tdbe] update light properties (also relies on the owner's Transform)
        void SetRenderProperties(int lightType);
        /// [tdbe] update light properties (also relies on the owner's Transform)
        /// <param name="colorAndIntensity">You are technically allowed to use values above 1.0</param>
        void SetRenderProperties(glm::vec4 colorAndIntensity, int lightType);
        /// [tdbe] update light properties (also relies on the owner's Transform)
        /// <param name="colorAndIntensity">You are technically allowed to use values above 1.0</param>
        void SetRenderProperties(glm::vec4 colorAndIntensity);
        /// [tdbe] update light properties (also relies on the owner's Transform)
        void SetRenderProperties(glm::vec3 color);
        /// [tdbe] update light properties (also relies on the owner's Transform)
        /// <param name="colorAndIntensity">You are technically allowed to use values above 1.0</param>
        /// <param name="radiusMultiplier">Extra radius to adjust in addition to the radius coming from the light's transform's scale.</param>
        void SetRenderProperties(glm::vec4 colorAndIntensity, float radiusMultiplier);
        /// [tdbe] update light properties (also relies on the owner's Transform)
        /// <param name="colorAndIntensity">You are technically allowed to use values above 1.0</param>
        /// <param name="radiusMultiplier">Extra radius to adjust in addition to the radius coming from the light's transform's scale.</param>
        void SetRenderProperties(glm::vec4 colorAndIntensity, float radiusMultiplier, int lightType);
        /// [tdbe] update light properties (also relies on the owner's Transform)
        /// <param name="radiusMultiplier">Extra radius to adjust in addition to the radius coming from the light's transform's scale.</param>
        void SetRenderProperties(float radiusMultiplier, int lightType);
        /// [tdbe] update light properties (also relies on the owner's Transform)
        /// <param name="radiusMultiplier">Extra radius to adjust in addition to the radius coming from the light's transform's scale.</param>
        void SetRenderProperties(float radiusMultiplier);
        /// [tdbe] send this to the shaders, it represents everything about this light
        glm::mat4 GetShaderMatrix();

        /// [tdbe] just a dumb flag that tells the shaders to skip past this light in their for loop 
        /// (we still send this light's data to the shader as part of the fixed lights array)
        void SetVisible(bool visible);
        bool IsVisible();
        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override;
        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemVersionChanged() override;

        /// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
        /// See <see cref="GameData::LoadGameWorld"/>. And remember to add it to some <see cref="GameEntity"/> or <see cref="GameEntityObject"/>.
        Light(GameDataId::ID id = {}, GameDataId::ID owner = {});
        ~Light();

      private:
        bool isVisible = true;
        float lightType = LightTypes::LIGHT_TYPE_DIRECTIONAL;
        /// [tdbe] extra radius to adjust in addition to the radius coming from the light's transform's scale.
        float radiusMultiplier = 1.0f;

        // [tdbe] each matrix row is: const int COLOR = 0 (.w means disabled if 0.0); const int CENTRAL_VEC = 1 (and .w
        // is radius); const int SHAPE_VEC_0 = 2; const int SHAPE_VEC_1 = 3;
        glm::mat4 shaderMatrix = glm::mat4(1.0f);
        glm::vec4 colorAndIntensity = glm::vec4(1.0f);

        /// [tdbe] For performance. 
        /// NOTE: assumes the game entity owner of the light component doesn't change and neither does its Transform. In a bigger game engine you'd enforce or track this.
        Transform* cachedTransformComponent = nullptr;

        // [tdbe] for lights, the matrix will be baked into the multi value shadermatrix that gets sent to the shaders
        glm::mat4 GetWorldMatrix();
        void SetShaderProperties();
    };
} // namespace Game