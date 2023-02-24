#include "Input.h"


namespace
{
const std::string actionSetName = "actionset";
const std::string localizedActionSetName = "Actions";
} // namespace

namespace Inputspace
{
// [tdbe] Sets up: Action Set, Action Paths, Actions, Action Spaces, Binding Paths, Interaction Profiles, Action Poses.
Input::Input(XrInstance instance, XrSession session)
{
    XrResult result;
    this->session = session;
    // Create an action set.
    {
        XrActionSetCreateInfo actionSetCreateInfo = {XR_TYPE_ACTION_SET_CREATE_INFO};
        actionSetCreateInfo.priority = 0;
        memcpy(actionSetCreateInfo.actionSetName, actionSetName.data(), actionSetName.length() + 1u);
        memcpy(actionSetCreateInfo.localizedActionSetName, localizedActionSetName.data(), localizedActionSetName.length() + 1u);

        result = xrCreateActionSet(instance, &actionSetCreateInfo, &actionSetData.actionSet);
        if (XR_FAILED(result)){
            std::string cPlusPlusRemainsDumbUntilV23 = "100; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }

    }

    // [tdbe] Create Action paths for controllers
    actionSetData.controllerPaths.resize((int)ControllerEnum::COUNT);
    actionSetData.controllerPaths[(int)ControllerEnum::LEFT] = util::stringToPath(instance, "/user/hand/left");
    actionSetData.controllerPaths[(int)ControllerEnum::RIGHT] = util::stringToPath(instance, "/user/hand/right");

    // Create actions
    {
        // [tdbe] hand poses, e.g. matrix
        // [tdbe] the util::createAction takes the controllerPaths, so it binds to each controller
        if (!util::createAction(actionSetData.actionSet, actionSetData.controllerPaths, 
                                "handpose", "Hand Pose", XR_ACTION_TYPE_POSE_INPUT, actionSetData.aimPoseAction))
        {
            std::string cPlusPlusRemainsDumbUntilV23 = "110; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }

        if (!util::createAction(actionSetData.actionSet, actionSetData.controllerPaths, 
                                "grippose", "Grip Pose", XR_ACTION_TYPE_POSE_INPUT, actionSetData.gripPoseAction))
        {
            std::string cPlusPlusRemainsDumbUntilV23 = "120; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }
        
        // trigger
        if (!util::createAction(actionSetData.actionSet, actionSetData.controllerPaths, 
                                "trigger_v_action", "Trigger", XR_ACTION_TYPE_FLOAT_INPUT, actionSetData.triggerValueAction))
        {
            std::string cPlusPlusRemainsDumbUntilV23 = "200; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }
        // trigger
        if (!util::createAction(actionSetData.actionSet, actionSetData.controllerPaths, 
                                "squeeze_v_action", "Squeeze", XR_ACTION_TYPE_FLOAT_INPUT, actionSetData.squeezeValueAction))
        {
            std::string cPlusPlusRemainsDumbUntilV23 = "300; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }
        
        // grab
        if (!util::createAction(actionSetData.actionSet, actionSetData.controllerPaths, 
                                "grab_action", "Grab Action", XR_ACTION_TYPE_FLOAT_INPUT, actionSetData.grabAction))
        {
            std::string cPlusPlusRemainsDumbUntilV23 = "400; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }

        // thumbstick
        if (!util::createAction(actionSetData.actionSet, actionSetData.controllerPaths, 
                                "thumbstick_action", "Thumbstick Action", XR_ACTION_TYPE_VECTOR2F_INPUT, actionSetData.thumbstickAction))
        {
            std::string cPlusPlusRemainsDumbUntilV23 = "500; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }

        // bool menu
        if (!util::createAction(actionSetData.actionSet, actionSetData.controllerPaths, 
                                "menu_action", "Menu Action", XR_ACTION_TYPE_BOOLEAN_INPUT, actionSetData.menuClickAction))
        {
            std::string cPlusPlusRemainsDumbUntilV23 = "600; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }

        // bool select
        if (!util::createAction(actionSetData.actionSet, actionSetData.controllerPaths, 
                                "select_action", "Select Action", XR_ACTION_TYPE_BOOLEAN_INPUT, actionSetData.selectClickAction))
        {
            std::string cPlusPlusRemainsDumbUntilV23 = "610; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }

        // vibration output
        if (!util::createAction(actionSetData.actionSet, actionSetData.controllerPaths, 
                                "vibrate_action", "Vibration Action", XR_ACTION_TYPE_VIBRATION_OUTPUT, actionSetData.vibrateAction))
        {
            std::string cPlusPlusRemainsDumbUntilV23 = "700; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }
       
        // [tdbe] Note:
        // [tdbe] it's possible to bind an action to any controller, if you do it without a controller path.
        // [tdbe] and also when you get the action state info, you can pass XR_NULL_PATH to get any paths.
    }
 

    // [tdbe] Action Spaces for each controller. They will contain the controller poses.
    actionSetData.controllerReferenceSpaces_aim.resize((int)ControllerEnum::COUNT);
    actionSetData.controllerReferenceSpaces_grip.resize((int)ControllerEnum::COUNT);
    for (size_t ci = 0u; ci < (int)ControllerEnum::COUNT; ci++)
    {
        XrActionSpaceCreateInfo actionSpaceInfo{XR_TYPE_ACTION_SPACE_CREATE_INFO};
        actionSpaceInfo.action = actionSetData.aimPoseAction; 
        actionSpaceInfo.subactionPath = actionSetData.controllerPaths[ci];
        actionSpaceInfo.poseInActionSpace.orientation = {.x = 0, .y = 0, .z = 0, .w = 1.0};
        actionSpaceInfo.poseInActionSpace.position = {.x = 0, .y = 0, .z = 0};

        result = xrCreateActionSpace(session, &actionSpaceInfo, &actionSetData.controllerReferenceSpaces_aim[ci]);
        if (XR_FAILED(result)){
            std::string cPlusPlusRemainsDumbUntilV23 = "800; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }

        actionSpaceInfo.action = actionSetData.gripPoseAction; 
        result = xrCreateActionSpace(session, &actionSpaceInfo, &actionSetData.controllerReferenceSpaces_grip[ci]);
        if (XR_FAILED(result)){
            std::string cPlusPlusRemainsDumbUntilV23 = "810; XrResult: ";
            cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
            util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
            valid = false;
            return;
        }
    }

    // [tdbe] Create Binding Paths for different controllers, because they have (or don't have) different buttons/sensors etc.
    //{-------------------------------------------------------------------------------------------------
    std::array<XrPath, (int)ControllerEnum::COUNT> aimPosePath;// [tdbe] hand pose that allows applications to point in the world using the input source, according to the platform’s conventions for aiming with that kind of source.
    std::array<XrPath, (int)ControllerEnum::COUNT> gripPosePath;// [tdbe] hand pose that allows applications to reliably render a virtual object held in the user’s hand, whether it is tracked directly or by a motion controller.
    // https://raw.githubusercontent.com/KhronosGroup/OpenXR-Docs/master/specification/sources/images/grip_axes_diagram.png
    // https://raw.githubusercontent.com/KhronosGroup/OpenXR-Docs/master/specification/sources/images/ext_hand_tracking_joint_convention.png

    std::array<XrPath, (int)ControllerEnum::COUNT> triggerValuePath; 
    std::array<XrPath, (int)ControllerEnum::COUNT> triggerClickPath; 
    std::array<XrPath, (int)ControllerEnum::COUNT> triggerTouchPath; 

    std::array<XrPath, (int)ControllerEnum::COUNT> squeezeValuePath;
    std::array<XrPath, (int)ControllerEnum::COUNT> squeezeForcePath;
    std::array<XrPath, (int)ControllerEnum::COUNT> squeezeClickPath;

    std::array<XrPath, (int)ControllerEnum::COUNT> thumbstickPath;
    std::array<XrPath, (int)ControllerEnum::COUNT> thumbstickClickPath;
    std::array<XrPath, (int)ControllerEnum::COUNT> menuClickPath;
    std::array<XrPath, (int)ControllerEnum::COUNT> selectClickPath;
    
    std::array<XrPath, (int)ControllerEnum::COUNT> aClickPath;
    std::array<XrPath, (int)ControllerEnum::COUNT> bClickPath;
    std::array<XrPath, (int)ControllerEnum::COUNT> xClickPath;
    std::array<XrPath, (int)ControllerEnum::COUNT> yClickPath;

    std::array<XrPath, (int)ControllerEnum::COUNT> hapticPath;
    
    {
        xrStringToPath(instance, "/user/hand/left/input/aim/pose", &aimPosePath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/aim/pose", &aimPosePath[(int)ControllerEnum::RIGHT]);

        xrStringToPath(instance, "/user/hand/left/input/grip/pose", &gripPosePath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/grip/pose", &gripPosePath[(int)ControllerEnum::RIGHT]);

        xrStringToPath(instance, "/user/hand/left/input/trigger/value", &triggerValuePath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/trigger/value", &triggerValuePath[(int)ControllerEnum::RIGHT]);
        xrStringToPath(instance, "/user/hand/left/input/trigger/click", &triggerClickPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/trigger/click", &triggerClickPath[(int)ControllerEnum::RIGHT]);
        xrStringToPath(instance, "/user/hand/left/input/trigger/touch", &triggerTouchPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/trigger/touch", &triggerTouchPath[(int)ControllerEnum::RIGHT]);

        xrStringToPath(instance, "/user/hand/left/input/squeeze/value", &squeezeValuePath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/squeeze/value", &squeezeValuePath[(int)ControllerEnum::RIGHT]);
        xrStringToPath(instance, "/user/hand/left/input/squeeze/force", &squeezeForcePath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/squeeze/force", &squeezeForcePath[(int)ControllerEnum::RIGHT]);
        xrStringToPath(instance, "/user/hand/left/input/squeeze/click", &squeezeClickPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/squeeze/click", &squeezeClickPath[(int)ControllerEnum::RIGHT]);

        xrStringToPath(instance, "/user/hand/left/input/thumbstick", &thumbstickPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/thumbstick", &thumbstickPath[(int)ControllerEnum::RIGHT]);
        xrStringToPath(instance, "/user/hand/left/input/thumbstick/click", &thumbstickClickPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/thumbstick/click", &thumbstickClickPath[(int)ControllerEnum::RIGHT]);

        xrStringToPath(instance, "/user/hand/left/input/menu/click", &menuClickPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/menu/click", &menuClickPath[(int)ControllerEnum::RIGHT]);

        xrStringToPath(instance, "/user/hand/left/input/select/click", &selectClickPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/select/click", &selectClickPath[(int)ControllerEnum::RIGHT]);
        
        xrStringToPath(instance, "/user/hand/left/input/a/click", &aClickPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/a/click", &aClickPath[(int)ControllerEnum::RIGHT]);
        xrStringToPath(instance, "/user/hand/left/input/b/click", &bClickPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/b/click", &bClickPath[(int)ControllerEnum::RIGHT]);
        xrStringToPath(instance, "/user/hand/left/input/x/click", &xClickPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/x/click", &xClickPath[(int)ControllerEnum::RIGHT]);
        xrStringToPath(instance, "/user/hand/left/input/y/click", &yClickPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/input/y/click", &yClickPath[(int)ControllerEnum::RIGHT]);

        xrStringToPath(instance, "/user/hand/left/output/haptic", &hapticPath[(int)ControllerEnum::LEFT]);
        xrStringToPath(instance, "/user/hand/right/output/haptic", &hapticPath[(int)ControllerEnum::RIGHT]);
    }
    
    // [tdbe] Here we choose the bindings to go in the Interaction Profile of each controller type.
    {
        // Suggest bindings for KHR Simple.
        {
            XrPath khrSimpleInteractionProfilePath;
            result = xrStringToPath(instance, "/interaction_profiles/khr/simple_controller", &khrSimpleInteractionProfilePath);
            if (XR_FAILED(result)){
                std::string cPlusPlusRemainsDumbUntilV23 = "900; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
                valid = false;
                return;
            }

            std::vector<XrActionSuggestedBinding> bindings
            {{
                // [tdbe] here khronos uses "select click" for grab, instead of a missing "squeeze" etc 
                {actionSetData.grabAction, selectClickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.grabAction, selectClickPath[(int)ControllerEnum::RIGHT]},
                {actionSetData.gripPoseAction, gripPosePath[(int)ControllerEnum::LEFT]},// hand pose
                {actionSetData.gripPoseAction, gripPosePath[(int)ControllerEnum::RIGHT]},// hand pose
                {actionSetData.aimPoseAction, aimPosePath[(int)ControllerEnum::LEFT]},// hand pose
                {actionSetData.aimPoseAction, aimPosePath[(int)ControllerEnum::RIGHT]},// hand pose
                // [tdbe] TODO: unavailable for this controller
                //{actionSetData.thumbstickAction, thumbstickPath[(int)ControllerEnum::LEFT]},
                //{actionSetData.thumbstickAction, thumbstickPath[(int)ControllerEnum::RIGHT]},
                {actionSetData.selectClickAction, selectClickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.selectClickAction, selectClickPath[(int)ControllerEnum::RIGHT]},
                {actionSetData.menuClickAction, menuClickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.menuClickAction, menuClickPath[(int)ControllerEnum::RIGHT]},
                
                //{actionSetData.triggerAction, triggerValuePath[(int)ControllerEnum::LEFT]},
                //{actionSetData.triggerAction, triggerValuePath[(int)ControllerEnum::RIGHT]},
                
                {actionSetData.vibrateAction, hapticPath[(int)ControllerEnum::LEFT]},
                {actionSetData.vibrateAction, hapticPath[(int)ControllerEnum::RIGHT]}
            }};

            const XrInteractionProfileSuggestedBinding suggestedBindings = {
                .type = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING,
                .interactionProfile = khrSimpleInteractionProfilePath,
                .countSuggestedBindings = (uint32_t)bindings.size(),
                .suggestedBindings = bindings.data()
            };

            result = xrSuggestInteractionProfileBindings(instance, &suggestedBindings);
            if (XR_FAILED(result)){
                std::string cPlusPlusRemainsDumbUntilV23 = "1000; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
                valid = false;
                return;
            }
        }

        // Suggest bindings for the Oculus Touch.
        // https://docs.unity3d.com/Packages/com.unity.xr.openxr@1.6/manual/features/oculustouchcontrollerprofile.html
        {
            XrPath oculusTouchInteractionProfilePath;
            result = xrStringToPath(instance, "/interaction_profiles/oculus/touch_controller", &oculusTouchInteractionProfilePath);
            if (XR_FAILED(result)){
                std::string cPlusPlusRemainsDumbUntilV23 = "1100; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
                valid = false;
                return;
            }

            std::vector<XrActionSuggestedBinding> bindings
            {{
                {actionSetData.grabAction, squeezeValuePath[(int)ControllerEnum::LEFT]},
                {actionSetData.grabAction, squeezeValuePath[(int)ControllerEnum::RIGHT]},
                {actionSetData.gripPoseAction, gripPosePath[(int)ControllerEnum::LEFT]},// hand pose
                {actionSetData.gripPoseAction, gripPosePath[(int)ControllerEnum::RIGHT]},// hand pose
                {actionSetData.aimPoseAction, aimPosePath[(int)ControllerEnum::LEFT]},// hand pose
                {actionSetData.aimPoseAction, aimPosePath[(int)ControllerEnum::RIGHT]},// hand pose
                {actionSetData.thumbstickAction, thumbstickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.thumbstickAction, thumbstickPath[(int)ControllerEnum::RIGHT]},
                // [tdbe] TODO: unavailable for this controller
                // {actionSetData.selectClickAction, selectClickPath[(int)ControllerEnum::RIGHT]},
                // alt:
                {actionSetData.selectClickAction, aClickPath[(int)ControllerEnum::RIGHT]},
                // [tdbe] note: only on left side!
                {actionSetData.menuClickAction, menuClickPath[(int)ControllerEnum::LEFT]},
                 
                // [tdbe] NOTE: Old oculus Rifts for some reason fail on this path,
                // even though it's the official oculus binding. https://steamcommunity.com/app/250820/discussions/8/3088898048343567453/
                // Uncomment if you're not supporting old devices.
                //{actionSetData.triggerAction, triggerValuePath[(int)ControllerEnum::LEFT]},
                //{actionSetData.triggerAction, triggerValuePath[(int)ControllerEnum::RIGHT]},

                {actionSetData.vibrateAction, hapticPath[(int)ControllerEnum::LEFT]},
                {actionSetData.vibrateAction, hapticPath[(int)ControllerEnum::RIGHT]}
            }};

            const XrInteractionProfileSuggestedBinding suggestedBindings = 
            {
                .type = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING,
                .interactionProfile = oculusTouchInteractionProfilePath,
                .countSuggestedBindings = (uint32_t)bindings.size(),
                .suggestedBindings = bindings.data()
            };
            
            result = xrSuggestInteractionProfileBindings(instance, &suggestedBindings);
            if (XR_FAILED(result)){
                std::string cPlusPlusRemainsDumbUntilV23 = "1200; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
                valid = false;
                return;
            }
        }

        // Suggest bindings for the Vive Controller.
        {
            XrPath viveControllerInteractionProfilePath;
            result = xrStringToPath(instance, "/interaction_profiles/htc/vive_controller", &viveControllerInteractionProfilePath);
            if (XR_FAILED(result)){
                std::string cPlusPlusRemainsDumbUntilV23 = "1300; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
                valid = false;
                return;
            }
            std::vector<XrActionSuggestedBinding> bindings
            {{
                {actionSetData.grabAction, triggerValuePath[(int)ControllerEnum::LEFT]},
                {actionSetData.grabAction, triggerValuePath[(int)ControllerEnum::RIGHT]},
                {actionSetData.gripPoseAction, gripPosePath[(int)ControllerEnum::LEFT]},// hand pose
                {actionSetData.gripPoseAction, gripPosePath[(int)ControllerEnum::RIGHT]},// hand pose
                {actionSetData.aimPoseAction, aimPosePath[(int)ControllerEnum::LEFT]},// hand pose
                {actionSetData.aimPoseAction, aimPosePath[(int)ControllerEnum::RIGHT]},// hand pose
                // [tdbe] TODO: unavailable for this controller
                // {actionSetData.thumbstickAction, thumbstickPath[(int)ControllerEnum::LEFT]},
                // {actionSetData.thumbstickAction, thumbstickPath[(int)ControllerEnum::RIGHT]},
                // [tdbe] alt:
                
                // [tdbe] TODO: unavailable for this controller
                // {actionSetData.selectClickAction, selectClickPath[(int)ControllerEnum::LEFT]},
                // {actionSetData.selectClickAction, selectClickPath[(int)ControllerEnum::RIGHT]},
                // [tdbe] alt:

                {actionSetData.menuClickAction, menuClickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.menuClickAction, menuClickPath[(int)ControllerEnum::RIGHT]},
                
                //{actionSetData.triggerAction, triggerValuePath[(int)ControllerEnum::LEFT]},
                //{actionSetData.triggerAction, triggerValuePath[(int)ControllerEnum::RIGHT]},
                
                {actionSetData.vibrateAction, hapticPath[(int)ControllerEnum::LEFT]},
                {actionSetData.vibrateAction, hapticPath[(int)ControllerEnum::RIGHT]}
            }};
            XrInteractionProfileSuggestedBinding suggestedBindings
            {
                .type = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING,
                .interactionProfile = viveControllerInteractionProfilePath,
                .countSuggestedBindings = (uint32_t)bindings.size(),
                .suggestedBindings = bindings.data()
            };
            
            result = xrSuggestInteractionProfileBindings(instance, &suggestedBindings);
            if (XR_FAILED(result)){
                std::string cPlusPlusRemainsDumbUntilV23 = "1400; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
                valid = false;
                return;
            }
        }
        
        // Suggest bindings for the Valve Index Controller.
        {
            XrPath valveIndexControllerInteractionProfilePath;
            result = xrStringToPath(instance, "/interaction_profiles/valve/index_controller",
                                    &valveIndexControllerInteractionProfilePath);
            if (XR_FAILED(result)){
                util::error(Error::GenericOpenXR, "14");
                valid = false;
                return;
            }

            std::vector<XrActionSuggestedBinding> bindings
            {{
                {actionSetData.grabAction, squeezeForcePath[(int)ControllerEnum::LEFT]},
                {actionSetData.grabAction, squeezeForcePath[(int)ControllerEnum::RIGHT]},
                {actionSetData.gripPoseAction, gripPosePath[(int)ControllerEnum::LEFT]},// hand pose
                {actionSetData.gripPoseAction, gripPosePath[(int)ControllerEnum::RIGHT]},// hand pose
                {actionSetData.aimPoseAction, aimPosePath[(int)ControllerEnum::LEFT]},// hand pose
                {actionSetData.aimPoseAction, aimPosePath[(int)ControllerEnum::RIGHT]},// hand pose
                {actionSetData.thumbstickAction, thumbstickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.thumbstickAction, thumbstickPath[(int)ControllerEnum::RIGHT]},
                {actionSetData.selectClickAction, aClickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.selectClickAction, aClickPath[(int)ControllerEnum::RIGHT]},
                // [tdbe] TODO: unavailable for this controller
                // {actionSetData.menuClickAction, menuClickPath[(int)ControllerEnum::LEFT]},
                // {actionSetData.menuClickAction, menuClickPath[(int)ControllerEnum::RIGHT]},
                // [tdbe] alt:
                {actionSetData.menuClickAction, bClickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.menuClickAction, bClickPath[(int)ControllerEnum::RIGHT]},
                
                //{actionSetData.triggerAction, triggerValuePath[(int)ControllerEnum::LEFT]},
                //{actionSetData.triggerAction, triggerValuePath[(int)ControllerEnum::RIGHT]},
                
                {actionSetData.vibrateAction, hapticPath[(int)ControllerEnum::LEFT]},
                {actionSetData.vibrateAction, hapticPath[(int)ControllerEnum::RIGHT]}
            }};

            const XrInteractionProfileSuggestedBinding suggestedBindings = 
            {
                .type = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING,
                .interactionProfile = valveIndexControllerInteractionProfilePath,
                .countSuggestedBindings = (uint32_t)bindings.size(),
                .suggestedBindings = bindings.data()
            };

            result = xrSuggestInteractionProfileBindings(instance, &suggestedBindings);
            if (XR_FAILED(result)){
                std::string cPlusPlusRemainsDumbUntilV23 = "1500; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
                valid = false;
                return;
            }
        }

        // Suggest bindings for the Microsoft Mixed Reality Motion Controller.
        {
            XrPath microsoftMixedRealityInteractionProfilePath;
            result = xrStringToPath(instance, "/interaction_profiles/microsoft/motion_controller",
                                        &microsoftMixedRealityInteractionProfilePath);
            if (XR_FAILED(result)){
                std::string cPlusPlusRemainsDumbUntilV23 = "1600; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
                valid = false;
                return;
            }
            std::vector<XrActionSuggestedBinding> bindings
            {{
                {actionSetData.grabAction, squeezeClickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.grabAction, squeezeClickPath[(int)ControllerEnum::RIGHT]},
                {actionSetData.gripPoseAction, gripPosePath[(int)ControllerEnum::LEFT]},// hand pose
                {actionSetData.gripPoseAction, gripPosePath[(int)ControllerEnum::RIGHT]},// hand pose
                {actionSetData.aimPoseAction, aimPosePath[(int)ControllerEnum::LEFT]},// hand pose
                {actionSetData.aimPoseAction, aimPosePath[(int)ControllerEnum::RIGHT]},// hand pose
                {actionSetData.thumbstickAction, thumbstickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.thumbstickAction, thumbstickPath[(int)ControllerEnum::RIGHT]},
                // [tdbe] TODO: unavailable for this controller
                // {actionSetData.selectClickAction, selectClickPath[(int)ControllerEnum::LEFT]},
                // {actionSetData.selectClickAction, selectClickPath[(int)ControllerEnum::RIGHT]},
                // [tdbe] alt:
                {actionSetData.selectClickAction, menuClickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.selectClickAction, menuClickPath[(int)ControllerEnum::RIGHT]},

                {actionSetData.menuClickAction, menuClickPath[(int)ControllerEnum::LEFT]},
                {actionSetData.menuClickAction, menuClickPath[(int)ControllerEnum::RIGHT]},
                
                //{actionSetData.triggerAction, triggerValuePath[(int)ControllerEnum::LEFT]},
                //{actionSetData.triggerAction, triggerValuePath[(int)ControllerEnum::RIGHT]},
                
                {actionSetData.vibrateAction, hapticPath[(int)ControllerEnum::LEFT]},
                {actionSetData.vibrateAction, hapticPath[(int)ControllerEnum::RIGHT]}
            }};

            const XrInteractionProfileSuggestedBinding suggestedBindings = 
            {
                .type = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING,
                .interactionProfile = microsoftMixedRealityInteractionProfilePath,
                .countSuggestedBindings = (uint32_t)bindings.size(),
                .suggestedBindings = bindings.data()
            };

            result = xrSuggestInteractionProfileBindings(instance, &suggestedBindings);
            if (XR_FAILED(result)){
                std::string cPlusPlusRemainsDumbUntilV23 = "1700; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
                valid = false;
                return;
            }
        }
    }
    //}-------------------------------------------------------------------------------------------------

    // Attach the controller action set
    XrSessionActionSetsAttachInfo xrSessionAattachInfo = {
        .type = XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO,
        .countActionSets = 1,
        .actionSets = &actionSetData.actionSet
        };
    result = xrAttachSessionActionSets(session, &xrSessionAattachInfo);
    if (XR_FAILED(result)){
        std::string cPlusPlusRemainsDumbUntilV23 = "1800; XrResult: ";
        cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
        util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
        valid = false;
        return;
    }
}

bool Input::Sync(XrSpace xrReferenceSpace, XrTime predictedDisplayTime, std::vector<XrView> eyePoses, XrSessionState sessionState)
{
    // Sync the actions 
    const XrActiveActionSet activeActionSet{actionSetData.actionSet, XR_NULL_PATH};// Wildcard for all
    
    XrActionsSyncInfo actionsSyncInfo = { .type = XR_TYPE_ACTIONS_SYNC_INFO, 
                                        .countActiveActionSets = 1u,
                                        .activeActionSets = &activeActionSet};
                                        
    XrResult result = xrSyncActions(session, &actionsSyncInfo);
    if(XR_FAILED(result)){
        std::string cPlusPlusRemainsDumbUntilV23 = "1900; XrResult: ";
        cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
        util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
        valid = false;
        return valid;
    }
    
    // Update the actions
    inputData.SizeVectors(ControllerEnum::COUNT, SideEnum::COUNT);

    // [tdbe] Head action poses
    inputData.eyePoseMatrixes[(int)SideEnum::LEFT] = util::poseToMatrix(eyePoses[(int)SideEnum::LEFT].pose);
    inputData.eyePoses[(int)SideEnum::LEFT] = util::xrPosefToGlmPosef(eyePoses[(int)SideEnum::LEFT].pose);
    inputData.eyePoseMatrixes[(int)SideEnum::RIGHT] = util::poseToMatrix(eyePoses[(int)SideEnum::RIGHT].pose);
    inputData.eyePoses[(int)SideEnum::RIGHT] = util::xrPosefToGlmPosef(eyePoses[(int)SideEnum::RIGHT].pose);
    // [tdbe] TODO: figure out what/how head poses/joints work in openxr https://registry.khronos.org/OpenXR/specs/1.0/html/xrspec.html
    inputData.headPose = {
        .orientation = util::slerp(inputData.eyePoses[(int)SideEnum::LEFT].orientation, inputData.eyePoses[(int)SideEnum::RIGHT].orientation, .5),
        .position = util::slerp(inputData.eyePoses[(int)SideEnum::LEFT].position, inputData.eyePoses[(int)SideEnum::RIGHT].position, .5)
    };
    inputData.headPoseMatrix = util::poseToMatrix(inputData.headPose);

    // [tdbe] Headset State. Use to detect status / user proximity / user presence / user engagement https://registry.khronos.org/OpenXR/specs/1.0/html/xrspec.html#session-lifecycle
    inputData.headsetActivityState = sessionState;

    for (size_t i = 0u; i < (int)ControllerEnum::COUNT; i++){
        auto ci = static_cast<ControllerEnum>(i);
        // [tdbe] Pose
        XrActionStatePose aimPoseState = Input::GetActionPoseState(actionSetData.aimPoseAction, ci);
        if (aimPoseState.isActive)
        {
            XrSpaceLocation spaceLocation{.type = XR_TYPE_SPACE_LOCATION};   
            result = xrLocateSpace(actionSetData.controllerReferenceSpaces_aim[i], xrReferenceSpace, predictedDisplayTime, 
                                    &spaceLocation);
            if(XR_FAILED(result)){
                std::string cPlusPlusRemainsDumbUntilV23 = "2000; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
                valid = false;
                return valid;
            }

            // Check that the position and orientation are valid and tracked
            constexpr XrSpaceLocationFlags checkFlags =
                XR_SPACE_LOCATION_POSITION_VALID_BIT | XR_SPACE_LOCATION_POSITION_TRACKED_BIT |
                XR_SPACE_LOCATION_ORIENTATION_VALID_BIT | XR_SPACE_LOCATION_ORIENTATION_TRACKED_BIT;
            if ((spaceLocation.locationFlags & checkFlags) == checkFlags)
            {
                inputData.controllerAimPoseMatrixes.at(i) = util::poseToMatrix(spaceLocation.pose);
                inputData.controllerAimPoses.at(i) = util::xrPosefToGlmPosef(spaceLocation.pose);
            }
        }

        // [tdbe] Pose
        XrActionStatePose gripPoseState = Input::GetActionPoseState(actionSetData.gripPoseAction, ci);
        if (gripPoseState.isActive)
        {
            XrSpaceLocation spaceLocation{.type = XR_TYPE_SPACE_LOCATION};   
            result = xrLocateSpace(actionSetData.controllerReferenceSpaces_grip[i], xrReferenceSpace, predictedDisplayTime, 
                                    &spaceLocation);
            if(XR_FAILED(result)){
                std::string cPlusPlusRemainsDumbUntilV23 = "2100; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
                valid = false;
                return valid;
            }

            // Check that the position and orientation are valid and tracked
            constexpr XrSpaceLocationFlags checkFlags =
                XR_SPACE_LOCATION_POSITION_VALID_BIT | XR_SPACE_LOCATION_POSITION_TRACKED_BIT |
                XR_SPACE_LOCATION_ORIENTATION_VALID_BIT | XR_SPACE_LOCATION_ORIENTATION_TRACKED_BIT;
            if ((spaceLocation.locationFlags & checkFlags) == checkFlags)
            {
                inputData.controllerGripPoseMatrixes.at(i) = util::poseToMatrix(spaceLocation.pose);
                inputData.controllerGripPoses.at(i) = util::xrPosefToGlmPosef(spaceLocation.pose);
            }
        }

        // [tdbe] State (input value)
        XrActionStateFloat grabState = Input::GetActionFloatState(actionSetData.grabAction, ci);
        inputData.grabState.at(i) = grabState;

        // [tdbe] State
        XrActionStateVector2f thumbStickState = Input::GetActionVector2fState(actionSetData.thumbstickAction, ci);
        inputData.thumbStickState.at(i) = thumbStickState;

        // [tdbe] State
        XrActionStateBoolean menuClickState = Input::GetActionBooleanState(actionSetData.menuClickAction, ci);
        inputData.menuClickState.at(i) = menuClickState;      

        // [tdbe] State
        XrActionStateBoolean selectClickState = Input::GetActionBooleanState(actionSetData.selectClickAction, ci);
        inputData.selectClickState.at(i) = selectClickState;  

        // [tdbe] State
        //XrActionStateFloat triggerState = Input::GetActionFloatState(actionSetData.triggerAction, ci);
        //inputData.triggerState.at(i) = triggerState;  

        

        // [tdbe] Etc. add new actions as needed, from the existing bindings / paths / actions following these examples above ^
        
    }
    return true;
}

const InputData& Input::GetInputData() const
{
    return inputData;
}

InputHaptics& Input::GetInputHaptics()
{
    return inputHaptics;
}

void Input::ApplyHapticFeedbackRequests(InputHaptics& inputHaptics){
    const std::vector<InputHaptics::HapticsData>& haptDataVect = inputHaptics.GetHapticFeedbackRequests();
    size_t size = std::min(haptDataVect.size(), actionSetData.controllerPaths.size());
    for(size_t i =0; i<size; i++){
        if(!haptDataVect[i].isActive)
            continue;
        XrHapticVibration vibration{XR_TYPE_HAPTIC_VIBRATION};
        vibration.amplitude = haptDataVect[i].amplitude01;
        vibration.duration = haptDataVect[i].duration;
        vibration.frequency = haptDataVect[i].frequency;

        XrHapticActionInfo hapticActionInfo{XR_TYPE_HAPTIC_ACTION_INFO};
        hapticActionInfo.action = actionSetData.vibrateAction;
        hapticActionInfo.subactionPath = actionSetData.controllerPaths[i];
        xrApplyHapticFeedback(session, &hapticActionInfo, (XrHapticBaseHeader*)&vibration);
    }
    inputHaptics.ClearHapticFeedbackRequests();
}

/// @param controller -- if you pass ControllerEnum::COUNT, it will get from any controller (ie from XR_NULL_PATH)
XrActionStatePose Input::GetActionPoseState(XrAction targetAction, ControllerEnum controller)
{
    XrPath path = XR_NULL_PATH;// Wildcard for all
    if(controller != ControllerEnum::COUNT){
        path = actionSetData.controllerPaths[(int)controller];
    }
    XrActionStateGetInfo getInfo = {.type = XR_TYPE_ACTION_STATE_GET_INFO,
                                    .action = targetAction,
                                    .subactionPath = path};

    XrActionStatePose poseState{.type = XR_TYPE_ACTION_STATE_POSE};
    XrResult result = xrGetActionStatePose(session, &getInfo, &poseState);

    if(XR_FAILED(result)){
        std::string cPlusPlusRemainsDumbUntilV23 = "2200; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
        valid = false;
        return poseState;
    }
    return poseState;
}

/// @param controller -- if you pass ControllerEnum::COUNT, it will get from any controller (ie from XR_NULL_PATH)
XrActionStateBoolean Input::GetActionBooleanState(XrAction targetAction, ControllerEnum controller)
{
    XrPath path = XR_NULL_PATH;// Wildcard for all
    if(controller != ControllerEnum::COUNT){
        path = actionSetData.controllerPaths[(int)controller];
    }
    XrActionStateGetInfo getInfo = {.type = XR_TYPE_ACTION_STATE_GET_INFO,
                                    .action = targetAction,
                                    .subactionPath = path};

    XrActionStateBoolean poseState{.type = XR_TYPE_ACTION_STATE_BOOLEAN};
    XrResult result = xrGetActionStateBoolean(session, &getInfo, &poseState);

    if(XR_FAILED(result)){
        std::string cPlusPlusRemainsDumbUntilV23 = "2300; XrResult: ";
                cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
                util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
        valid = false;
        return poseState;
    }
    return poseState;
}

/// @param controller -- if you pass ControllerEnum::COUNT, it will get from any controller (ie from XR_NULL_PATH)
XrActionStateFloat Input::GetActionFloatState(XrAction targetAction, ControllerEnum controller)
{
    XrPath path = XR_NULL_PATH;// Wildcard for all
    if(controller != ControllerEnum::COUNT){
        path = actionSetData.controllerPaths[(int)controller];
    }
    XrActionStateGetInfo getInfo = {.type = XR_TYPE_ACTION_STATE_GET_INFO,
                                    .action = targetAction,
                                    .subactionPath = path};

    XrActionStateFloat poseState{.type = XR_TYPE_ACTION_STATE_FLOAT};
    XrResult result = xrGetActionStateFloat(session, &getInfo, &poseState);

    if(XR_FAILED(result)){
        std::string cPlusPlusRemainsDumbUntilV23 = "2400; XrResult: ";
        cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
        util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
        valid = false;
        return poseState;
    }
    return poseState;
}

/// @param controller -- if you pass ControllerEnum::COUNT, it will get from any controller (ie from XR_NULL_PATH)
XrActionStateVector2f Input::GetActionVector2fState(XrAction targetAction, ControllerEnum controller)
{
    XrPath path = XR_NULL_PATH;// Wildcard for all
    if(controller != ControllerEnum::COUNT){
        path = actionSetData.controllerPaths[(int)controller];
    }
    XrActionStateGetInfo getInfo = {.type = XR_TYPE_ACTION_STATE_GET_INFO,
                                    .action = targetAction,
                                    .subactionPath = path};

    XrActionStateVector2f poseState{.type = XR_TYPE_ACTION_STATE_VECTOR2F};
    XrResult result = xrGetActionStateVector2f(session, &getInfo, &poseState);

    if(XR_FAILED(result)){
        std::string cPlusPlusRemainsDumbUntilV23 = "2500; XrResult: ";
        cPlusPlusRemainsDumbUntilV23.append(std::to_string((int)result));
        util::error(Error::GenericOpenXR, cPlusPlusRemainsDumbUntilV23);
        valid = false;
        return poseState;
    }
    return poseState;
}


bool Input::isValid() const
{
  return valid;
}

Input::~Input()
{
    if (!actionSetData.controllerReferenceSpaces_aim.empty()){
        for (const XrSpace& space : actionSetData.controllerReferenceSpaces_aim)
        {
            xrDestroySpace(space);
        }
    }

    if (!actionSetData.controllerReferenceSpaces_grip.empty()){
        for (const XrSpace& space : actionSetData.controllerReferenceSpaces_grip)
        {
            xrDestroySpace(space);
        }
    }

    if (actionSetData.actionSet)
    {
        xrDestroyActionSet(actionSetData.actionSet);
    }

    if (actionSetData.aimPoseAction)
    {
        xrDestroyAction(actionSetData.aimPoseAction);
    }

    if (actionSetData.gripPoseAction)
    {
        xrDestroyAction(actionSetData.gripPoseAction);
    }

    if (actionSetData.triggerValueAction)
    {
        xrDestroyAction(actionSetData.triggerValueAction);
    }

    if (actionSetData.triggerClickAction)
    {
        xrDestroyAction(actionSetData.triggerClickAction);
    }

    if (actionSetData.squeezeValueAction)
    {
        xrDestroyAction(actionSetData.squeezeValueAction);
    }

    if (actionSetData.squeezeForceAction)
    {
        xrDestroyAction(actionSetData.squeezeForceAction);
    }

    if (actionSetData.squeezeClickAction)
    {
        xrDestroyAction(actionSetData.squeezeClickAction);
    }

    if (actionSetData.thumbstickAction)
    {
        xrDestroyAction(actionSetData.thumbstickAction);
    }

    if (actionSetData.thumbstickClickAction)
    {
        xrDestroyAction(actionSetData.thumbstickClickAction);
    }

    if (actionSetData.menuClickAction)
    {
        xrDestroyAction(actionSetData.menuClickAction);
    }

    if (actionSetData.selectClickAction)
    {
        xrDestroyAction(actionSetData.selectClickAction);
    }

    if (actionSetData.aClickAction)
    {
        xrDestroyAction(actionSetData.aClickAction);
    }

    if (actionSetData.bClickAction)
    {
        xrDestroyAction(actionSetData.bClickAction);
    }

    if (actionSetData.xClickAction)
    {
        xrDestroyAction(actionSetData.xClickAction);
    }

    if (actionSetData.yClickAction)
    {
        xrDestroyAction(actionSetData.yClickAction);
    }

    if (actionSetData.vibrateAction)
    {
        xrDestroyAction(actionSetData.vibrateAction);
    }

    if (actionSetData.grabAction)
    {
        xrDestroyAction(actionSetData.grabAction);
    }

    if (actionSetData.triggerAction)
    {
        xrDestroyAction(actionSetData.triggerAction);
    }
}
}