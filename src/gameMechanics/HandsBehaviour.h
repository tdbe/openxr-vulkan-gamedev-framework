#include "GameBehaviour.h"
#include "../Model.h"

/* [tdbe] 
 *  Mechanics for displaying/moving hands
 */
class HandsBehaviour : public GameBehaviour
{
    public:
        HandsBehaviour(Model &handModelLeft, Model &handModelRight);
        virtual ~HandsBehaviour();

        //Start();
        virtual void Update(const float deltaTime, const float gameTime, const Inputspace::InputData &inputData, 
                            Inputspace::InputHaptics &inputHaptics, const glm::mat4 &inverseCameraMatrix);

    private:
        Model &handModelLeft;
        Model &handModelRight;
};