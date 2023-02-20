#pragma once

#include "../Util.h"
#include "../InputData.h"
#include "../Model.h"

/* [tdbe] 
 *  Quick base class as a base for all game mechanics.
 */
class GameBehaviour 
{
    public:
        GameBehaviour();
        virtual ~GameBehaviour();
        //Start();
        virtual void Update(const float deltaTime, const float gameTime, const Inputspace::InputData &inputData, 
                            Inputspace::InputHaptics &inputHaptics, const glm::mat4 &inverseCameraMatrix);

    private:

};