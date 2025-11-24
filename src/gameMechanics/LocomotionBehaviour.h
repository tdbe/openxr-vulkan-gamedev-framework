#pragma once
#include "GameBehaviour.h"
#include "../GameData/GameDataId.h"
#include <array>

namespace Game
{
    // [tdbe] newb-friendly-note: predeclaring here so we can use pointers here and avoid circular dependency, we reference the real headers inside the .cpp
    struct Transform;
    struct Material;
    struct GameEntityObject;
    struct PlayerObject;
}

using namespace Game;

namespace Behaviours
{
    /// [tdbe] Mechanics for moving around (xr locomotion)
    /// My idea here is to rotate and pan the world (without pitch/roll tilting),
    /// by grabbing with both hands, and dragging or rotating the scene.
    /// To prevent sickness, I'll make a "tunelvision scene" / "thinking with portals", with a virtual floor.
    class LocomotionBehaviour : public GameBehaviour
    {
      public:
        void SetTeleportRequest(glm::vec3 destination);
        LocomotionBehaviour(PlayerObject& playerObject,
                            GameDataId::ID floorGridId,
                            GameDataId::ID ceilingGridId,
                            GameDataId::ID icosphereSkyboxId,
                            GameDataId::ID chaperoneSkyboxId,
                            GameDataId::ID handsMaterialId,
                            float movementSpeedScaler,
                            float movementAccelerationPow,
                            float rotationSpeedScaler);
        virtual ~LocomotionBehaviour();

        // Start();
        virtual void Update(const float deltaTime,
                            const float gameTime,
                            const Inputspace::InputData& inputData,
                            Inputspace::InputHaptics& inputHaptics);

      private:
        enum class VisualsState
        {
            Clear = 0,
            Start = 1,
            Intro = 2,
            Update = 3,
            Outro = 4,
            End = 5,
        };
        VisualsState currentVisualsState = VisualsState::Clear;
        struct VisualsStateData
        {
        };
        VisualsStateData visualsStateData;

        enum class MovementState
        {
            Clear = 0,
            Start = 1,
            Update = 2,
            End = 3
        };
        MovementState currentMovementState = MovementState::Clear;
        struct MoveStateData
        {
            glm::vec3 prevPosLeft;
            glm::vec3 prevPosRight;
            glm::vec3 prevPosMiddle;

            glm::vec3 posLeft;
            glm::vec3 posRight;
            glm::vec3 posMiddle;

            glm::vec3 moveDir;
            float moveInputSpeed;

            glm::vec3 prevDirLeftRight;
            glm::vec3 dirLeftRight;
        };
        MoveStateData moveStateData;
        struct TeleportRequest
        {
            enum State
            {
                Finished = 0,
                Requested = 1,
                Ongoing = 2,
            } state = State::Finished;
            const glm::vec3 origin = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            glm::vec3 targetDestination = origin;
        };
        TeleportRequest teleportRequest;

        PlayerObject& playerObject;
        GameDataId::ID floorGridId;
        GameDataId::ID ceilingGridId;
        GameDataId::ID icosphereSkyboxId;
        GameDataId::ID chaperoneSkyboxId;
        glm::mat4 origFloorGridMatr = glm::mat4(0.0f);
        glm::mat4 origSkyboxMatr = glm::mat4(0.0f);
        GameDataId::ID handsMaterialId;
        bool prevHandsMatVisible = false;
        std::array<bool, 2> prevHandsEnabled;
        float movementSpeedScaler = 0.0f;
        float movementAccelerationPow = 0.0f;
        float rotationSpeedScaler = 0.0f;

        void HandleVisualsState(const float deltaTime,
                                const Inputspace::InputData& inputData,
                                const XrActionStateFloat& grabLeft,
                                const XrActionStateFloat& grabRight,
                                const float avgGrabInput,
                                TeleportRequest::State& teleportState,
                                Inputspace::InputHaptics& inputHaptics);
        void HandleMovementState(const float deltaTime,
                                 const Inputspace::InputData& inputData,
                                 const XrActionStateFloat& grabLeft,
                                 const XrActionStateFloat& grabRight,
                                 const float avgGrabInput,
                                 const TeleportRequest& teleportState,
                                 Inputspace::InputHaptics& inputHaptics);
    };
} // namespace Behaviours