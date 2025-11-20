#pragma once
#include <typeindex>
#include <vector>

#include "../GameDataId.h"
#include "../GameData.h"

namespace Game
{
    struct GameEntity : GameDataId
    {
      public:
        /// [tdbe] faster than dynamic casts but won't return objects that inherit from T.
        /// [tdbe] newb-friendly-note: you'll get linker errors if you declare but don't define template
        /// functimons in the header file. (the compiler won't read the definition and won't know if/how to handle the
        /// various types, (and of course won't explain this to you in hu-man terms or any terms))
        template <typename T> std::vector<GameDataId::ID> GetComponentIDsByTypeIndex() const
        {
            // static_assert(std::is_base_of<GameComponent, T>::value, 
            // must inherit from GameComponent");
            auto target = std::type_index(typeid(T));
            std::vector<GameDataId::ID> foundVec = std::vector<GameDataId::ID>();
            for (int i = 0; i < components.size(); i++)
            {
                if (components[i].IsCleared())
                    continue;

                if (components[i].typeIndex == target)
                {
                    foundVec.emplace_back(components[i]);
                }
            }
            return foundVec;
        };
        std::vector<GameDataId::ID> GetAllComponentIDs() const;
        size_t CountValidComponents() const;

        /// [tdbe] (first component but might have more (of same type))
        template <typename T> T* GetComponentByTypeIndex() const
        {
            std::vector<GameDataId::ID> ids = GetComponentIDsByTypeIndex<T>();
            T* found = nullptr;
            for (int i = 0; i < ids.size(); i++)
            {
                found = static_cast<T*>(GameData::Instance().GetComponent(ids[i]));
                break;
            }
            return found;
        };

        template <typename T> std::vector<T*> GetComponentsByTypeIndex() const
        {
            std::vector<GameDataId::ID> ids = GetComponentIDsByTypeIndex<T>();
            std::vector<T*> foundVec = std::vector<T*>();
            for (int i = 0; i < ids.size(); i++)
            {
                auto comp = static_cast<T*>(GameData::Instance().GetComponent(ids[i]));
                foundVec.emplace_back(comp);
            }
            return foundVec;
        };

        /// [tdbe] Note: you create a component via its corresponding <see cref="GameDataPool"/>,
        /// here we just mark that component X is (also) attributed to game entity E.
        void AddComponentId(GameDataId::ID component);
        /// [tdbe] Note: this does not destroy or affect the actual components,
        /// here we just mark that component X was disassociated from game entity E.
        void ClearComponentId(GameDataId::ID component);
        /// [tdbe] Note: this does not destroy or affect the actual components,
        /// here we just mark that components {X,Y,Z} were disassociated from game entity E.
        void ClearComponentIDs();

        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        /// [tdbe] Clear this item (and mark it as Free in its pool).
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override;
        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemVersionChanged() override;

        void SetEnabled(bool enabled);
        bool IsEnabled() const;

        /// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
        /// See <see cref="GameData::LoadGameWorld"/>. And remember you can add components.
        GameEntity(GameDataId::ID id = {});
        virtual ~GameEntity() {};

      private:
        bool isEnabled = true; // [tdbe] e.g. whether or not it will be rendered. Some components also have an isVisible.

        /// [tdbe] References for immediate/scripting convenience. An entity usually has just a few (e.g. 3-5) components.
        /// Note: must be marked as free on <see cref="NotifyItemCleared"/>.
        /// [tdbe] todo: we'd need restrictions on some components: at least Transform should be unique if present.
        std::vector<GameDataId::ID> components;
        /// [tdbe] Also find anyone that caches our ID and clear it (e.g. our components have set us as their owner), and any lone component that would be left dangling.
        /// Note: if you wanted to be maximally efficient clearing millions of items, you wouldn't hop around memory with this function, you'd instead 
        /// construct some global command buffers marking all the entities and all the components the game wants to clear on this frame, 
        /// and then run a sync point with a job on the buffers coherently contiguously.
        void ClearItemDependencies();
    };
} // namespace Game