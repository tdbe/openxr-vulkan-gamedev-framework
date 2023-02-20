#pragma once
#include "Util.h"

namespace Inputspace{

    enum class ControllerEnum
    {
        LEFT = 0,
        RIGHT = 1,
        // 
        // [tdbe] TODO: figure out what happens in openxr with multiple controllers e.g. valve vr controllers, pucks 
        COUNT = 2,
        NONE = -1
    };
    enum class SideEnum
    {
        LEFT = 0,
        RIGHT = 1,
        COUNT = 2
    };

    // [tdbe] Owned by Input. Updated every Sync tick. 
    // It should contain all the input your game uses.
    struct InputData {
        // [tdbe] Poses
        std::vector<glm::mat4> eyePoseMatrixes;//(int)SideEnum::COUNT
        std::vector<util::posef> eyePoses;//(int)SideEnum::COUNT
        glm::mat4 headPoseMatrix;
        util::posef headPose;
        std::vector<glm::mat4> controllerAimPoseMatrixes;//(int)ControllerEnum::COUNT
        std::vector<util::posef> controllerAimPoses;
        std::vector<glm::mat4> controllerGripPoseMatrixes;
        std::vector<util::posef> controllerGripPoses;

        // [tdbe] Input States. Also includes lastChangeTime, isActive, changedSinceLastSync properties.
        std::vector<XrActionStateFloat> grabState{XR_TYPE_ACTION_STATE_FLOAT};
        std::vector<XrActionStateVector2f> thumbStickState{XR_TYPE_ACTION_STATE_VECTOR2F};
        std::vector<XrActionStateBoolean> menuClickState{XR_TYPE_ACTION_STATE_BOOLEAN};
        std::vector<XrActionStateBoolean> selectClickState{XR_TYPE_ACTION_STATE_BOOLEAN};
        std::vector<XrActionStateFloat> triggerState{XR_TYPE_ACTION_STATE_BOOLEAN};
        

        // [tdbe] Headset State. Use to detect status / user proximity / user presence / user engagement https://registry.khronos.org/OpenXR/specs/1.0/html/xrspec.html#session-lifecycle
        XrSessionState headsetActivityState = XR_SESSION_STATE_UNKNOWN;

        void SizeVectors(ControllerEnum controllers, SideEnum sides){
            eyePoseMatrixes.resize((int)sides);
            eyePoses.resize((int)sides);

            controllerAimPoseMatrixes.resize((int)controllers);
            controllerAimPoses.resize((int)controllers);
            controllerGripPoseMatrixes.resize((int)controllers);
            controllerGripPoses.resize((int)controllers);
            grabState.resize((int)controllers);
            thumbStickState.resize((int)controllers);
            menuClickState.resize((int)controllers);
            selectClickState.resize((int)controllers);
            triggerState.resize((int)controllers);
        }
    };

    // [tdbe] Owned by Input. Modifiable from gameplay.
    // Stores, per controller, the last requested haptics output.
    // To be sent to the input system at the end of the frame via Input::ApplyHapticFeedbackRequests.
    struct InputHaptics{
        public:
            struct HapticsData{
                bool isActive = false;
                float amplitude01 = 0.3f;
                int64_t duration = XR_MIN_HAPTIC_DURATION;
                float frequency = XR_FREQUENCY_UNSPECIFIED;
            };
            
        private:
            // [tdbe] the way it is now, each spot in the vector is a controller slot.
            std::vector<HapticsData> hapticsDataVect;
        
        public: 
            void RequestHapticFeedback( ControllerEnum index,
                                        float amplitude01 = 0.3f,
                                        int64_t duration = XR_MIN_HAPTIC_DURATION,
                                        float frequency = XR_FREQUENCY_UNSPECIFIED
            ){
                HapticsData hapticsData = {
                    .isActive = true,
                    .amplitude01 = amplitude01, 
                    .duration = duration, 
                    .frequency = frequency
                };
                if((int) index >= hapticsDataVect.size()){
                    hapticsDataVect.resize((int) index+1);
                }
                hapticsDataVect[(int)index] = hapticsData;
            }

            ~InputHaptics(){}

        //"internal:" would be nice to have that here
            const std::vector<HapticsData>& GetHapticFeedbackRequests(){
                return hapticsDataVect;
            }
            void ClearHapticFeedbackRequests(){
                hapticsDataVect.clear();
            }
    };
}