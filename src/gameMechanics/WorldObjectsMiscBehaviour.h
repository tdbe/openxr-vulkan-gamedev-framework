#pragma once
#include "GameBehaviour.h"
#include "../GameData/GameDataId.h"

namespace Game
{
    // [tdbe] newb-friendly-note: predeclaring here so we can use pointers here and avoid circular dependency, we reference the real headers inside the .cpp
    struct Material;
    struct GameEntityObject;
}
using namespace Game;

namespace Behaviours
{
    /// [tdbe] Mechanics for misc / deco world objects
    class WorldObjectsMiscBehaviour : public GameBehaviour
    {
      public:
        WorldObjectsMiscBehaviour(GameDataId::ID bikeObject,
                                  GameDataId::ID bikeLightObject,
                                  GameDataId::ID textMat,
                                  GameDataId::ID logoMat,
                                  GameDataId::ID handsMat);
        virtual ~WorldObjectsMiscBehaviour();

        // Start();
        virtual void Update(const float deltaTime,
                            const float gameTime,
                            const Inputspace::InputData& inputData,
                            Inputspace::InputHaptics& inputHaptics);

      private:
        GameDataId::ID bikeObject;
        GameDataId::ID bikeLightObject;
        GameDataId::ID textMat;
        GameDataId::ID logoMat;
        GameDataId::ID handsMat;

        void Mechanic_bikeObject(const float gameTime);
        glm::vec4 RotateMatColor(const float gameTime, const float minBrightness);
        glm::vec4 RotateMatColorUnrealistic(const float gameTime, const float minBrightness);
    };
} // namespace Behaviours