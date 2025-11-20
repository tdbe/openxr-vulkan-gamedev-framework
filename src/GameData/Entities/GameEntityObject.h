#pragma once
#include <string>

#include "GameEntity.h"
#include "../GameData.h"
#include <functional>
#include <unordered_map>

namespace Game
{
    struct GameEntityObject : public GameEntity
    {
      public:
#pragma region Events
        using EventType = std::function<void(GameEntityObject*)>;
        static std::unordered_map<std::string, EventType> OnGameEntityObjectAddedHandlers;
        static std::unordered_map<std::string, EventType> OnGameEntityObjectRemovedHandlers;
        static void SubscribeGameEntityObjectEvents(std::string uniqueFunctionIdentifier_Added, EventType handler_Added,
                                                    std::string uniqueFunctionIdentifier_Removed, EventType handler_Removed)
        {
            OnGameEntityObjectAddedHandlers.insert_or_assign(uniqueFunctionIdentifier_Added, handler_Added);
            OnGameEntityObjectRemovedHandlers.insert_or_assign(uniqueFunctionIdentifier_Removed, handler_Removed);
        }
        static void UnsubscribeGameEntityObjectEvents(std::string uniqueFunctionIdentifier_Added,
                                                      std::string uniqueFunctionIdentifier_Removed)
        {
            if (!OnGameEntityObjectAddedHandlers.empty())
                OnGameEntityObjectAddedHandlers.erase(uniqueFunctionIdentifier_Added);
            if (!OnGameEntityObjectRemovedHandlers.empty())
                OnGameEntityObjectRemovedHandlers.erase(uniqueFunctionIdentifier_Removed);
        }
#pragma endregion Events
        void SetName(std::string name);
        std::string GetName() const;

        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override;
        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        /// todo: this should be restricted to <see cref"GameDataPool"/>
        virtual void NotifyItemVersionChanged() override;

        /// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
        /// See <see cref="GameData::LoadGameWorld"/>. And remember you can add components.
        GameEntityObject(GameDataId::ID id = {},
                         bool isVisible = true,
                         std::string name = "game object",
                         void (*runExtensions)(GameEntityObject* owner) = nullptr);
        ~GameEntityObject();

      private:
        std::string name = "game object";

#pragma region Events
        /// [tdbe] Raised when its version was updated.
        /// [tdbe] (There's a nice multi-subscribe Visual C++ event system, with __hook, __unhook, __event, __raise, keywords etc., however it would only be compilable from visual studio. So instead that, we emulate it in peasant land :))
        void RaiseGameEntityObjectAdded();
        /// [tdbe] Raised when this object was Cleared.
        /// [tdbe] (There's a nice multi-subscribe Visual C++ event system, with __hook, __unhook, __event, __raise, keywords etc., however it would only be compilable from visual studio. So instead that, we emulate it in peasant land :))
        void RaiseGameEntityObjectRemoved();
#pragma endregion Events
    };
} // namespace Game