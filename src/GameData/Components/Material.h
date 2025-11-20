#pragma once
#include "GameComponent.h"
#include "../GameDataId.h"
#include "../../OpenXrAndVulkan/Pipeline.h"

namespace Game
{
    /// [tdbe] Default Material struct. Can treat as "uber material" data, or can make multiple versions of this.
    /// When you create different "copies" of the same material (e.g. same shader & blending but different uniform properties (color etc)), 
    /// please create them together (next to each other in the <see cref="GameDataPool<Material>"/>) so that the renderer can batch them.
    /// If you add a new material at runtime, you must use an already existing pipeline. (and you probably can't batch it)
    /// (to batch materials with out of order pipelines, in the material buffer, we'd need a way to sort them, e.g. a new buffer just for 
    /// pipelines, with Material children with game Entity owners... not worth it)
    struct Material : public GameComponent
    {
      public:

        DynamicMaterialUniformData dynamicUniformData = {};
        // [tdbe] if you change any of the shaders, the renderer creates a new pipeline with the shaders.
        std::string vertShaderName = "shaders/Diffuse.vert.spv";
        std::string fragShaderName = "shaders/Diffuse.frag.spv";
        /// [tdbe] Cannot be changed after the <see cref="Renderer"/> process is started.
        /// So define how your material is blended, culled etc, before the game starts, before we create the <see cref="Renderer"/>.
        PipelineMaterialPayload pipelineData = {};
        /// [tdbe] Cannot be changed after the <see cref="Renderer"/> process gets started. 
        /// Wraps a <see cref="vkPipeline"/>; 
        /// A pipeline can be and is shared between materials which use the same shader / blend modes etc.
        Pipeline* pipeline = nullptr;
        /// [tdbe] gl_InstanceIndex in the shader
        uint32_t instanceCount = 1u;
        /// [tdbe] starting value of gl_InstanceIndex in the shader
        uint32_t firstInstance = 0u;

        void SetVisible(bool isVisible)
        {
            this->isVisible = isVisible;
        };

        bool IsVisible() const
        {
            return id.version != GameComponent::FREE && isVisible;
        };

        std::vector<GameEntity*> GetOwners() const
        {
            std::vector<GameDataId::ID> ownerIDs = GetOwnerIDs();
            std::vector<GameEntity*> foundVec = std::vector<GameEntity*>();
            for (int i = 0; i < ownerIDs.size(); i++)
            {
                auto comp = GameData::Instance().GetEntity(ownerIDs[i]);
                foundVec.emplace_back(comp);
            }
            return foundVec;
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemCleared(bool unsafe = false, bool clearDataLoadedFromStorage = false) override
        {
            util::DebugLog("[Component][Material]\t clearing this item: " + this->id.PrintGlobalUID());
            GameComponent::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
            dynamicUniformData = {};
            vertShaderName = "shaders/Diffuse.vert.spv";
            fragShaderName = "shaders/Diffuse.frag.spv";
            pipelineData = {};
            pipeline = nullptr;
            isVisible = true; // [tdbe] don't worry, items with empty versions don't get rendered
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemVersionChanged() override 
        {
            GameComponent::NotifyItemVersionChanged();
        };

        /// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
        /// See <see cref="GameData::LoadGameWorld"/>. And remember to add it to some <see cref="GameEntity"/> or <see cref="GameEntityObject"/>.
        Material(GameDataId::ID id = {}, GameDataId::ID owner = {}) : GameComponent(id, owner)
        {
        };
        ~Material() {};

      private:
        bool isVisible = true; // [tdbe] whether or not it will be rendered.
            
    };
}