# TL;DR: 
Performant open-source OpenXR, Vulkan, ECS, C++. 
A boilerplate -> framework -> mini "game engine" to quickly make an actual playable modern royalty-free XR game.

Demystifies ECS / Memory Management, Single Pass Rendering, XR Input, and XR gamedev fundamentals, on top of @janhsimon's excellent timesaving khronos setup [openxr-vulkan-example](https://github.com/janhsimon/openxr-vulkan-example). 

\[Note: [you can leave github comments over on my blog post version 😉](https://blog.deferredreality.com/openxr-vulkan-c++-gamedev-boilerplate/)\]

[snowglobe_openxr_vulkan_framework_30crf_800x800_github.webm](https://github.com/user-attachments/assets/410545fc-c14d-42bc-a6b8-046b0b7bae35)

Demo video, summer 2025. (There's also a [youtube hq 1600x1600/1440p 60fps version](https://www.youtube.com/watch?v=0e41lgULUoA).)

# Abstract: 
\*Trey Parker voice\* Vulkan has a rich body of work, and many strengths as a people; but lack hoo-man compatibility. I've managed to translate their stack, for hoo-mans, whose lifetimes may otherwise be too short to first decipher the khronos lunar manuals for hope of achieving even the most basic useful contact.

It didn't help that [they don't want to touch](https://community.khronos.org/t/what-is-the-right-way-to-implement-single-pass-rendering-with-openxr/109157/9) Single-Pass rendering (the performant & industry-standard linchpin of rendering).

In any case, thanks to open-source you can now build something pretty good the right way, without worrying about mighty morphing license agreements or wetting the beaks of people with golden parachutes.

## Builds:
- See [Build-ProjectSetup.Readme.md](https://github.com/tdbe/openxr-vulkan-gamedev-framework/blob/main/Build-ProjectSetup.Readme.md) or just be lazy and run the windows build in `./out/` (or the github Release).

- "Recommended Specs and Minimum Requirements": The scene runs on a RTX 4070 mobile at 90FPS (the refresh rate of the headset) with 8 (animated) tube lights and 2 directional lights, and a lot of transparent objects overdraw. It also runs on a RTX 2060 mobile with a bit of lag spikes if you have too much overdraw right on your face.

## Controls:

- [Controls.md](https://github.com/tdbe/openxr-vulkan-gamedev-framework/blob/main/Controls.md)

# My feature stack so far:

(sections ordered from high-level to low-level)

## XR Locomotion
  - Rotating and (accelerated) Panning of the scene by grabbing with both hands, retreating into a non-euclideanly warped pocket dimension (pushing the world away from you non-linearly) and seeing a "tunnelvision" portal-style chaperone. Highest effectiveness and lowest sickness (carefully tweaked and tested across dozens of different people).
  - Uses state machines for movement and for visuals. Supports animated teleportation with targets.
![chaperone_demo_gif](https://github.com/user-attachments/assets/f5ef5e4b-5c8e-44c8-90fe-723dc2fd6602)

## Base XR gameplay mechanics
  - Mechanics system based on a list of `GameBehaviour`s set up as FSMs.
  - Each behaviour is Created (with its own required references), Updated (with frame & input data etc), and Destroyed.
  - Mechanics for locomotion, hands, XR Input testing, world objects.
  - Any `GameComponent` has one or more `GameEntity` parents and manual or automatic cleanup (and preventing dangling components when all owners are freed). But there's no parenting between different game entities / objects, so manipulate groups of matrixes yourself. `TODO:` add a parenting system that processes the chain of Transform matrixes.

## Physics
  - There's support for running jobs on `Bounds` components (generated at model load time), with proper functions for AABB intersection or enclosure tests, plane tests, rectangular selection (even at non-Axis-Aligned angles) / frustum casting, raycasting.
  - There's a concept of ground in the locomotion system.
  - But `TODO:` no actual Physics library added.
  
## Animation
  - \*crickets\* `TODO:` just add it via full/extended gltf support.
  - `TODO:` find something open-source for: IK, gpu-skinning, and LoDs.
  
## Audio
  - \*crickets\* `TODO:` add Audio component, and threaded spatial sound library with audio queueing.
  
## GUI
  - \*crickets\* `TODO:` vector or sdf text, and just textures. Then use previously made ui code.
  - `TODO:` main menu, in-game hands inventory
  - (I'm certainly not implementing a scene-graph management system (game editor))
  
## Jobs / Threading
  - The objects and memory is set up in a spanned ECS manner but `TODO:` no job system / threading example (there's only sequentially updated `GameBehaviour`s / state machines on the main thread).
  - `TODO:` add a simple chunking concept, run jobs in parallel on chunks.

## GameData
  - Everything is set in generic memory-span pools, by type. You set up a game world with maximum allocated memory for each pool, then during gameplay you can request to use a free object, or mark a used one as free and reusable. There's no need for defragmenting, or swap-and-pop (would be slower in average-case) ("ted talk" in `GameDataPool.h`).
  - Enities and components are based on `GameDataId` (serving as a weak reference): `[globalUIDSeed][index][version]` and a top-level `[typeIndex]` for convenience.
  - Everything is easy to request and keep track of through various means, even by name in hash maps for light scripting purposes. 
  - Cleanup is either manual (and cache coherent) or automated via (cache-missing) awareness of component dependencies.
  - `GameEntity` and `GameEntityObject` 
  - `GameComponent`: `Material`, `Model`, `Transform`, `Bounds`, `Light`.
  - Properties: `isVisible`, `isEnabled`, `name`, some events etc.
  - `PlayerObject`s {`GameEntityObject`s, `PlayerActiveStates`}.
  - `Material`s {`Shader`, Descriptor-set `UniformData`, instancing, optional/shared `Pipeline` (for e.g blend ops)}
  
## Rendering
  - Implemented the most high quality e.g. Disney BRDF lighting equations for diffuse, specular and MRP based (Most Representative Point) shape lights. There's a [blog post on correct tube lights](https://blog.deferredreality.com/mrp-volumetric-lights-are-broken/):
  ![mrp_volumetric_lights_gif](https://github.com/user-attachments/assets/2db52360-7aba-4801-b1b6-92affac455fd)
  - `TODO:` does not include clearcoat.
  - `TODO:` does not include subsurface scattering,
  - `TODO:` does not include shadows, 
  - `TODO:` no per-pixel transparent object sorting,
  - ^, ^^, ^^^: but, I'll someday add in raytracing into some form of nanite clumps or other semi-volumetric discrete mesh data, instead of going through the legacy shading/sorting timesinks again.
  - Per-material, per-model, per-pipeline properties. Easily create a material e.g. transparent, doublesided; add new `shaders` with all the static and dynamic uniform data you need, instance geometry etc.
  - Render pipeline knows if you modified any default properties and creates pipelines from unique materials. Tries its best to batch per unique material and per model to minimise GPU-CPU communication, and has instancing, but it's not Indirect Rendering.
  - Expanded, added to, and explained Khronos' & JanhSimon's `Headset`, `Context`, `Renderer`/`Pipeline` etc, and the easily misleading & hard to customize khronos vulkan <-> openxr implementation. Especially regarding multipass vs singlepass & multiview, and what it takes if you want to use your own renderer or a diffrent API like `webgpu`. (look for `"// [tdbe]" `)

## `Input` class and `InputData`.
  - A 'proper' universal xr input class, supporting (probably) all controllers/headsets, with customizable binding paths and action sets.
  - Nicely accessible data through `InputData` and `InputHaptics`, including matrixes and other tracked XR positional data.
  - Poses for controllers and for head.
  - Actions (buttons, sticks, triggers, pressure, proximity etc).
  - User presence / headset activity state.
  - Haptic feedback output.
  - Exposes action state data (e.g. `lastChangeTime`, `isActive`, `changedSinceLastSync`)

## Utils
  - Utils and math for XR, input, general gamedev.
  - Debugging.
  - `TODO:` Bring in gizmos, e.g. debug lines, wireframes for lights etc.


## A typical run log:

- Game world load, setup, updates & render loops, unload and exit. [TypicalRunLogSample.md](https://github.com/tdbe/openxr-vulkan-gamedev-framework/blob/main/TypicalRunLogSample.md) 

# Additional Attributions

| Asset | Title | Author | License |
| --- | --- | --- | --- |
| `models/SuzanneHighQuality20k.obj` | [Suzanne](https://github.com/alecjacobson/common-3d-test-models) | [Blender](https://en.wikipedia.org/wiki/List_of_common_3D_test_models) (but mesh smoothed and subdivided by [tdbe](https://github.com/tdbe/)) | [GNU GPL 2+](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html) |
| `models/SudaBeam.obj` | [SudaBeam](https://duckduckgo.com/?q=beam+katana+suda+no+more+heroes&t=ffab&ia=images&iax=images) | [tdbe](https://github.com/tdbe/), a simplified version of Suda 51's parody of a light saber | [GNU GPL 3+](https://www.gnu.org/licenses/gpl-3.0.en.html) |
| `models/Squid_Happy_Grumpy.obj` | Happy Grumpy Squid | [tdbe](https://github.com/tdbe/) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) |
| `models/ground_displaced_*.obj` | demo ground | [tdbe](https://github.com/tdbe/) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) |
| `models/icosphere_*.obj` | utility (ico)spheres | [tdbe](https://github.com/tdbe/) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) |
| `models/quad_*.obj` | utility quad | [tdbe](https://github.com/tdbe/) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) |
| `models/capsule_*.obj` | utility capsule | [tdbe](https://github.com/tdbe/) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) |
| `models/text_*.obj` | various texts | [tdbe](https://github.com/tdbe/) | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) |

   ⠀


-------------------------------

   ⠀

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
