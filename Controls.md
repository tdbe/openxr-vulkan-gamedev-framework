## Note:

The input management code is pretty great™️and cross-platform, but this project was only tested on:
- old Oculus Rift CV1 (the 1.0 from 2016, not the Rift S)
- Valve Index (but on an older version of this project, in 2023)
- aethervr (openxr virtual headset) https://github.com/chnoblouch/aethervr

(Pls comment on this project if you test it on anything else / start an issue.)

## Glossary:
- Grips: the paddle or palm pressure sensor on your controller handle (not the index finger trigger).
- Thumbsticks: whatever joystick you may have on your controller(s). Alternatively a touchpad may work (not tested).
- Tap: (~fully) press and release something. E.g. squeeze a grip and then also let go.
- Press: action triggers when (and possibly also while) the button / trigger is pressed down. 

## In-game controls:

### Locomotion:
- Squeeze both Grips to enter the chaperone and locomotion mode: you'll be able to move & rotate the world as if you had grabbed it (as if it was a 3D object you grabbed with both hands). The speed is mildly accelerated with your hand speed.
- If you do the above but while also pushing any Thumbstick, it will act as a boost of up to 4x speed: up to 2x from one hand (via Thumbstick tilt, direction doesn't matter), and up to 2x + 2x from holding both Thumbsticks at the same time.
- press X and A simultaneously (or A and A or Select and Select or Menu and Menu (first button on each controller)) to teleport back to world x: 0, z: 0, (and y: 0) (y is up). This only resets the offset created by the locomotion system, and not also how much you physically walked in your room irl.

### Equipment:
- Tap a Grip (not both grips at the same time) to spawn (toggle) a "beam katana" in your hand: this is a tube light. You can have 2 active at the same time.

### Misc:
- NOTE: because of a known bug with Openxr input and Oculus Rift CV1 specifically, I disabled the trigger input completely, in Input.cpp, and I didn't use triggers for anything.



