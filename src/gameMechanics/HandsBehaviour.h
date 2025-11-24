#pragma once
#include "GameBehaviour.h"

#include "../GameData/PlayerObject.h"
using namespace Game;

namespace Behaviours
{
    /// [tdbe] Mechanics for displaying/moving hands
    class HandsBehaviour : public GameBehaviour
    {
      public:
        HandsBehaviour(PlayerObject& playerObject,
                       GameDataId::ID sudaBeam01,
                       GameDataId::ID handLight01,
                       GameDataId::ID sudaBeam02,
                       GameDataId::ID handLight02
                       );
        virtual ~HandsBehaviour();

        // Start();
        virtual void Update(const float deltaTime,
                            const float gameTime,
                            const Inputspace::InputData& inputData,
                            Inputspace::InputHaptics& inputHaptics);

      private:
        PlayerObject& playerObject;
        GameDataId::ID sudaBeam01;
        GameDataId::ID handLight01;
        GameDataId::ID sudaBeam02;
        GameDataId::ID handLight02;
        bool inventoryLeftInputCleared = true;
        bool inventoryRightInputCleared = true;
        bool inventoryLeftInputClearedAndHigh = false;
        bool inventoryRightInputClearedAndHigh = false;
    };
} // namespace Behaviours