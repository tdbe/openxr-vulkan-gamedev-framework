#include "GameBehaviour.h"
#include "../GameData.h"

/* [tdbe] 
 *  Mechanics for moving around (xr locomotion)
 *  My idea here is to rotate and pan the world (without tilting), 
 *  by grabbing with both hands, and dragging or rotating the scene.
 *  To prevent sickness, I'll make a "tunelvision scene", with a virtual floor.
 */
class LocomotionBehaviour : public GameBehaviour
{
    public:
        LocomotionBehaviour(PlayerObject& playerObject, float movementSpeedScaler_, float movementAccelerationPow_, float rotationSpeedScaler_);
        virtual ~LocomotionBehaviour();

        //Start();
        virtual void Update(const float deltaTime, const float gameTime, const Inputspace::InputData &inputData, 
                            Inputspace::InputHaptics &inputHaptics);

    private:
        enum class VisualsState{
            Clear = 0,
            Start = 1,
            Update = 2,
            End = 3,
            StartBackwards = 4,
            UpdateBackwards = 5,
            EndBackwards = 6
        };
        VisualsState currentVisualsState = VisualsState::Clear;
        struct VisualsStateData{
            
        };
        VisualsStateData visualsStateData;

        enum class MovementState{
            Clear = 0,
            Start = 1,
            Update = 2,
            End = 3
        };
        MovementState currentMovementState = MovementState::Clear;
        struct MoveStateData{
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

        PlayerObject& playerObject;
        float movementSpeedScaler;
        float movementAccelerationPow;
        float rotationSpeedScaler;

        void HandleVisualsState(const float deltaTime, const Inputspace::InputData &inputData, XrActionStateFloat& grabLeft, XrActionStateFloat& grabRight, float avgGrabInput, Inputspace::InputHaptics &inputHaptics);
        void HandleMovementState(const float deltaTime, const Inputspace::InputData &inputData, XrActionStateFloat& grabLeft, XrActionStateFloat& grabRight, float avgGrabInput, Inputspace::InputHaptics &inputHaptics);
};