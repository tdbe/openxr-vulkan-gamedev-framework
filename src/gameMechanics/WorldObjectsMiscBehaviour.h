#include "GameBehaviour.h"
#include "../Model.h"

/* [tdbe] 
 *  Mechanics for misc / deco world objects
 */
class WorldObjectsMiscBehaviour : public GameBehaviour
{
    public:
        WorldObjectsMiscBehaviour(Model& bikeModel);
        virtual ~WorldObjectsMiscBehaviour();

        //Start();
        virtual void Update(const float deltaTime, const float gameTime, const Inputspace::InputData &inputData, 
                            Inputspace::InputHaptics &inputHaptics, const glm::mat4 &inverseCameraMatrix);

    private:
        Model& bikeModel;

        void mechanic_bikeModel(const float deltaTime);
};