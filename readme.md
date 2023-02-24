OpenXR/Vulkan/C++ Gameplay, Input, and Rendering fundamentals, on top of @janhsimon's excellent timesaving openxr-vulkan-example.

Quickly make a performant XR game with common-sense gamedev principles. Explained; technical + friendly, conversational, human-speak tutorial style of how it's set up. Because there's quite a bit of evidence that khronos(openxr&vulkan) know not of what a hoo-man is. 🙃

# My feature stack so far:

## XR Locomotion
  - Mode: Rotating and accelerated Panning the scene by grabbing with both hands, and seeing a "tunnelvision" "external scene".
  - Uses state machines for movment and for visuals.

## Base XR gameplay mechanics
  - Mechanics system based on a list of `GameBehaviour`'s processed by Main's loop.
  - Each behaviour is Created (with its own required references), Updated (with frame & input data etc), and at the end Destroyed.
  - Sample mechanics for Locomotion, Hands, XR Input testing, World Objects.

## `GameData.h`
  - `GameObject`'s{`Material`, `Model`, Properties (e.g. `worldMatrix`, `isVisible`)}.
  - `PlayerObject`'s{`GameObject`'s, `PlayerActiveStates`}.
  - `Material`'s{`Shader`, Descriptor-set `niformData`, optional/shared `Pipeline` (for e.g blend ops)}
  
## Rendering
  - Eplained in Janhsimon's Headset & Context classes, the easily confusing & hard to customize khronos vulkan + openxr implementation. Especially regarding multipass vs singlepass & multiview, and what it takes if you want to use your own renderer or a diffrent api like webgpu.
  - Explained and tweaked the `Renderer`/Pipeline; look for "// [tdbe]" 
  - Per-material, per-model, per-pipeline properties. Easily create a material e.g. transparent, doublesided; add properties / new shader etc.
  - Render pipeline knows if you modified any default properties in materials and in that case creates unique mats/pipelines.

## `Input` class and `InputData`'s in `Inputspace`.
  - "proper" xr input, supporting "all" controllers/headsetss, with customizable binding paths and action sets.
  - nicely accessible through `InputData` and `InputHaptics`.
  - poses for controllers and for head.
  - actions (buttons, sticks, triggers, pressure, proximity etc).
  - user presence / headset activity state.
  - haptic feedback output.
  - exposes matrixes, and xr action state data (e.g. lastChangeTime, isActive, changedSinceLastSync)

## `Utils` class
  - Some Utils for XR, input, and extra gamedev math/utils.

-------------------------------

# Below is Janhsimon's original readme:

-------------------------------

![Teaser](teaser.gif)

# Overview

This project demonstrates how you can write your own VR application using OpenXR 1.1 and Vulkan 1.3. These are its main features:

- Basic rendering of example scene to the headset and into a resizeable mirror view on your desktop monitor. 
- Focus on easy to read and understand C++ without smart pointers, inheritance, templates, etc.
- Usage of the Vulkan `multiview` extension for extra performance.
- Warning-free code base spread over a small handful of classes.
- No OpenXR or Vulkan validation errors or warnings.
- CMake project setup for easy building.

Integrating both OpenXR and Vulkan yourself can be a daunting and painfully time-consuming task. Both APIs are very verbose and require the correct handling of countless minute details. This is why there are two main use cases where this project comes in handy:

1. Fork the repository and use it as a starting point to save yourself weeks of tedious integration work before you get to the juicy bits of VR development.
2. Reference the code while writing your own implementation from scratch, to help you out if you are stuck with a problem, or simply for inspiration.


# Running the OpenXR Vulkan Example

1. Download the latest [release](https://github.com/janhsimon/openxr-vulkan-example/releases) or build the project yourself with the steps below.
2. Make sure your headset is connected to your computer.
3. Run the program!


# Building the OpenXR Vulkan Example

1. Install the [Vulkan SDK](https://vulkan.lunarg.com) version 1.3 or newer.
2. Install [CMake](https://cmake.org/download) version 3.1 or newer.
3. Clone the repository and generate build files.
4. Build!

The repository includes binaries for all dependencies except the Vulkan SDK on Windows. These can be found in the `external` folder. You will have to build these dependencies yourself on other platforms. Use the address and version tag or commit hash in `version.txt` to ensure compatibility. Please don't hesitate to open a pull request if you have built dependencies for previously unsupported platforms.


# Attributions

| Asset | Title | Author | License |
| --- | --- | --- | --- |
| `models/Beetle.obj` | [Car Scene](https://sketchfab.com/3d-models/car-scene-b7b32eaca80d460c9338197e2c9d1408) | [toivo](https://sketchfab.com/toivo) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) |
| `models/Bike.obj` | [Sci-fi Hover Bike 04](https://sketchfab.com/3d-models/sci-fi-hover-bike-04-a326ca10a01b4cb29a357eb23e5f6e01) | [taktelon](https://sketchfab.com/taktelon) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) |
| `models/Car.obj` | [GAZ-21](https://sketchfab.com/3d-models/gaz-21-fdf5cbff00b04ab99a6ea3ab6b46533e) | [Ashkelon](https://sketchfab.com/Ashkelon) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) |
| `models/Hand.obj` | [Hand Anatomy Reference](https://sketchfab.com/3d-models/hand-anatomy-reference-2024d77a872a45f1baf6d81b51fe18a6) | [Ant B-D](https://sketchfab.com/ant_bd) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) |
| `models/Ruins.obj` | [Ancient Ruins Pack](https://sketchfab.com/3d-models/ancient-ruins-pack-4dad3b80562842f88d6568c5e1c469c2) | [Toni García Vilche](https://sketchfab.com/zul_gv) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) |
