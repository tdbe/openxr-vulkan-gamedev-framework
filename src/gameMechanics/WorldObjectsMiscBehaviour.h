#include "GameBehaviour.h"
#include "../GameData.h"

/* [tdbe] 
 *  Mechanics for misc / deco world objects
 */
class WorldObjectsMiscBehaviour : public GameBehaviour
{
    public:
        WorldObjectsMiscBehaviour(GameObject& bikeObject, Material& logoMat);
        virtual ~WorldObjectsMiscBehaviour();

        //Start();
        virtual void Update(const float deltaTime, const float gameTime, const Inputspace::InputData &inputData, 
                            Inputspace::InputHaptics &inputHaptics);

    private:
        GameObject& bikeObject;
        Material& logoMat;

        void mechanic_bikeObject(const float gameTime);
        void rotateMatColor(const float gameTime);
};