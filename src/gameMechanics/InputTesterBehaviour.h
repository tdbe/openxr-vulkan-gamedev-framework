#include "GameBehaviour.h"

/* [tdbe] 
 *  Mechanics for testing various inputs
 *  and giving vibration feedback
 */
class InputTesterBehaviour : public GameBehaviour
{
    public:
        InputTesterBehaviour();
        virtual ~InputTesterBehaviour();

        //Start();
        virtual void Update(const float deltaTime, const float gameTime, const Inputspace::InputData &inputData, 
                            Inputspace::InputHaptics &inputHaptics);

    private:
        void Mechanic_GrabState(const Inputspace::InputData &inputData, Inputspace::InputHaptics &inputHaptics);
};