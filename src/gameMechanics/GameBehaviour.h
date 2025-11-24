#pragma once
#include "../OpenXrInput/InputData.h"

namespace Behaviours
{
    /// [tdbe] Quick base class as a base for all game mechanics.
    class GameBehaviour
    {
      public:
        GameBehaviour();
        virtual ~GameBehaviour();
        // Start();
        virtual void Update(const float deltaTime,
                            const float gameTime,
                            const Inputspace::InputData& inputData,
                            Inputspace::InputHaptics& inputHaptics);

      private:
    };
} // namespace Behaviours