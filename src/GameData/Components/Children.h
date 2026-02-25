#pragma once
#include "GameComponent.h"
#include "../GameDataId.h"
#include <unordered_set>
#include <memory>

namespace Game
{
	/// [tdbe] Children component for entity hierarchy. TODO: replace with a good entity query (e.g. "get entities with parent").
    /// Related to <see cref="ARoot"/>, <see cref="Transform"/>, <see cref="Parent"/> and <see cref="SystemTRSParentingPropagation"/>".
    /// [tdbe] Note: this is mainly for conveniently knowing relationships, legacy OOP. If you want performance,
    /// you need to run a job over a queried entity pool (e.g. find all entities with parent) or look entity up in a Parents array,
    /// otherwse you just iterate through 100% cache-miss children of children.
	/// [RequireOwnerRestriction(1)]
	struct Children : public GameComponent
	{
		GameEntity* GetOwner() const;
                
        /// [tdbe] Note: this is for knowing relationships. If you want performance,
        /// you need to run a job over the entity pool with a command buffer, 
        /// don't just iterate over 100% cache-miss children.
        const std::unordered_set<GameDataId::ID>& GetChildren() const
		{
			return *children;
		};

        bool HasChildren() const
		{
            if(children->size() == 0)
                return false;
            for(auto& childId: *children)
            {
                if(!childId.IsCleared())
                {
                    return true;    
                }
            }
            return false;
		};

        bool HasChild(const GameDataId::ID childId) const
		{
			return children->contains(childId);
		};

        /// [tdbe] ecs performance & racing warning: <param name="ripple"> also calls <see cref="AddOwnerToParentOfChild"/></param>
		void AddChild(const GameDataId::ID newChildId, bool ripple = true)
		{
			if (children->contains(newChildId))
				return;
            children->emplace(newChildId);
            if(ripple)
                AddOwnerToParentOfChild(newChildId);
		};
        
        /// [tdbe] ecs performance & racing warning: <param name="ripple"> also calls <see cref="RemoveOwnerFromParentOfChild"/></param>
        void ClearChild(const GameDataId::ID childId, bool ripple = true)
		{
            if(!HasChild(childId))
                return;
            #ifdef DEBUG_VERBOSE
                util::DebugLog("[Children]\t clearing this child: " + childId.PrintGlobalUID() + " because the paren't");
            #endif
            if(ripple)
                RemoveOwnerFromParentOfChild(childId);
			children->erase(childId);
            if(!HasChildren())
                ClearRootAttributeComponent();
		};

        /// [tdbe] ecs performance & racing warning: <param name="ripple"> also calls <see cref="RemoveOwnerFromParentOfChildren"/></param>
		void ClearChildren(bool ripple = true)
		{
            if(ripple)
                RemoveOwnerFromParentOfChildren();
			children->clear();
            ClearRootAttributeComponent();
		};
        
        /// [tdbe] Use <see cref="GameDataPool<T>::ClearItem"/>(s).
        virtual void NotifyItemCleared(bool unsafe, bool clearDataLoadedFromStorage = false) override
        {
            #ifdef DEBUG_VERBOSE
            util::DebugLog("[Component][Parent]\t clearing this item: " + this->id.PrintGlobalUID());
            #endif
            ClearChildren(!unsafe);
            GameComponent::NotifyItemCleared(unsafe, clearDataLoadedFromStorage);
        };

        /// [tdbe] Use <see cref="GameDataPool<T>::GetFreeItem"/>(s).
        virtual void NotifyItemVersionChanged() override
        {
            GameComponent::NotifyItemVersionChanged();
        };

        /// [tdbe] You shouldn't call this constructor directly, instead use <see cref="GameDataPool::GetFreeItem"/>.
        Children(GameDataId::ID id = {}, GameDataId::ID owner = {});
        ~Children();
            
      private:
        /// [tdbe] ecs performance & racing warning: This is an immediate way to jump to 
		/// the child entity's Parent component and set itself to as the parent.
        void AddOwnerToParentOfChild(const GameDataId::ID childId);
        
        /// [tdbe] ecs performance & racing warning: This is an immediate way to jump to 
		/// the child entity's Parent component and remove itself.
        void RemoveOwnerFromParentOfChild(const GameDataId::ID childId);
        
        /// [tdbe] ecs performance & racing warning: This is an immediate way to jump to 
		/// the children entity's' Parent components and remove itself.
        void RemoveOwnerFromParentOfChildren();
        
        /// [tdbe] we remove the <see cref="ARoot"/> attribute component if we don't hold any children.
        void ClearRootAttributeComponent();

        /// [tdbe] Note: this is for knowing relationships. If you want performance,
        /// you need to run a job over the entity pool with a command buffer, 
        /// don't just iterate over 100% cache-miss children.
        std::unique_ptr<std::unordered_set<GameDataId::ID>> children = std::make_unique<std::unordered_set<GameDataId::ID>>();
    };
    
}