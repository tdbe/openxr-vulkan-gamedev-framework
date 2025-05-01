#include "GameBehaviour.h"
#include "../GameData.h"

/* [tdbe] 
 *  Mechanics for displaying/moving hands
 */
class HandsBehaviour : public GameBehaviour
{
    public:
        HandsBehaviour(PlayerObject& playerObject);
        virtual ~HandsBehaviour();

        //Start();
        virtual void Update(const float deltaTime, const float gameTime, const Inputspace::InputData &inputData, 
                            Inputspace::InputHaptics &inputHaptics);

    private:
        PlayerObject& playerObject;
};