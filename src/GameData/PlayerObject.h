#pragma once
#include <string>
#include <array>

#include "Entities/GameEntityObject.h"

namespace Game
{
    /// [tdbe] Note: this is meant to be used in a list or a table of states.
    /// because a player can be e.g. in locomotion and grabbing with each hand, all at the same time.
    /// Used as flagging so other interactions scripts can know they shouldn't e.g. grab stuff while in inappropriate states.
    enum class PlayerStates
    {
        Idle = 0,
        LocomotionState = 1,
        ChaperoneState = 2,
        GrabbingLeft = 3,
        GrabbingRight = 4,
        COUNT = 5
    };

    struct PlayerObject
    {
        std::string name = "player object";
        /// <summary>
        /// [tdbe] Use this <see crwef="worldRoot"/> for player locomotion and also add it to any objects that move with the
        /// player. E.g. the head and hands matrixes will only show the relative movement/rotation of those devices, will
        /// not also include the position of the player due to locomotion within the game world, ie the <see
        /// crwef="worldRoot"/>.
        /// </summary>
        GameDataId::ID worldRootId;
        GameDataId::ID handLeftId;
        GameDataId::ID handRightId;
        
        void SetPlayerState(PlayerStates state, bool value)
        {
            playerActiveStates[(int)state] = value;
        };

        bool IsPlayerInState(PlayerStates state) const
        {
            return playerActiveStates[(int)state];
        };

        PlayerObject(std::string name = "player object")
        {
            this->name = name;
        };

        PlayerObject(GameDataId::ID rootId,
                     GameDataId::ID handLeftId,
                     GameDataId::ID handRightId,
                     std::string name = "player object")
        {
            this->name = name;
            this->worldRootId = rootId;
            this->handLeftId = handLeftId;
            this->handRightId = handRightId;
        };

        ~PlayerObject() {};

      private:
        /// [tdbe] meant to be used as a table of states, as various different ones can happen at the same time.
        std::array<bool, (int)PlayerStates::COUNT> playerActiveStates = { true, false, false, false, false };
    };
} // namespace Game