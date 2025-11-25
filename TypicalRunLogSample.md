<details>
<summary>What a typical run log looks like. Game world load, setup, updates & render loops, unload and exit.</summary>
ipcLoader [RUNTIMEIPC]RuntimeIPC: Loaded library from C:\Program Files\Oculus\Support\oculus-runtime\RuntimeIPCServiceClient_64.dll
[Game][GameData][Singleton]      All data pools are here. instanceId: "GameData_{ 0 }".
[Game][GameData][LoadGameWorld]  .........................................................................................................................
[Game][GameData][LoadGameWorld]  Loading, deserializing, creating pools for entities and components, hooking some events, creating some quick access maps:

[GameDataPool][Constructed<MODEL_COMPONENTS>] maxPossibleSize: "{ 32 }", globalUIDSeed: "{ 400 }_MODEL_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Model.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 0 }, with id: { 400 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 0 }:{ 1 }
[MeshData] LoadModel: models/quad.obj; total meshData size so far: { 288 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 0 }:{ 1 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 1 }, with id: { 400 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 1 }:{ 2 }
[MeshData] LoadModel: models/ground_displaced_4096.obj; total meshData size so far: { 590112 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 1 }:{ 2 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 2 }, with id: { 400 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 2 }:{ 3 }
[MeshData] LoadModel: models/Ruins.obj; total meshData size so far: { 17245728 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 2 }:{ 3 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 3 }, with id: { 400 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 3 }:{ 4 }
[MeshData] LoadModel: models/Car.obj; total meshData size so far: { 18525888 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 3 }:{ 4 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 4 }, with id: { 400 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 4 }:{ 5 }
[MeshData] LoadModel: models/Beetle_glassless.obj; total meshData size so far: { 24642720 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 4 }:{ 5 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 5 }, with id: { 400 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 5 }:{ 6 }
[MeshData] LoadModel: models/Beetle_glass_only.obj; total meshData size so far: { 24903360 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 5 }:{ 6 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 6 }, with id: { 400 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 6 }:{ 7 }
[MeshData] LoadModel: models/Bike.obj; total meshData size so far: { 40369824 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 6 }:{ 7 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 7 }, with id: { 400 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 7 }:{ 8 }
[MeshData] LoadModel: models/Hand.obj; total meshData size so far: { 40708368 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 7 }:{ 8 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 8 }, with id: { 400 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 8 }:{ 9 }
[MeshData] LoadModel: models/cube.obj; total meshData size so far: { 40710096 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 8 }:{ 9 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 9 }, with id: { 400 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 9 }:{ 10 }
[MeshData] LoadModel: models/Logo_OpenXR_Vulkan.obj; total meshData size so far: { 41134032 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 9 }:{ 10 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 10 }, with id: { 400 }:{ 10 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 10 }:{ 11 }
[MeshData] LoadModel: models/Logo_Framework.obj; total meshData size so far: { 41486544 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 10 }:{ 11 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 11 }, with id: { 400 }:{ 11 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 11 }:{ 12 }
[MeshData] LoadModel: models/Text_Locomotion_Flat.obj; total meshData size so far: { 41797872 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 11 }:{ 12 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 12 }, with id: { 400 }:{ 12 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 12 }:{ 13 }
[MeshData] LoadModel: models/Text_Suda_Beam_Flat.obj; total meshData size so far: { 42086448 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 12 }:{ 13 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 13 }, with id: { 400 }:{ 13 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 13 }:{ 14 }
[MeshData] LoadModel: models/Text_See_Controls_md.obj; total meshData size so far: { 42286032 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 13 }:{ 14 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 14 }, with id: { 400 }:{ 14 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 14 }:{ 15 }
[MeshData] LoadModel: models/icosphere_subdiv4_half_smooth.obj; total meshData size so far: { 42470352 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 14 }:{ 15 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 15 }, with id: { 400 }:{ 15 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 15 }:{ 16 }
[MeshData] LoadModel: models/icosphere_subdiv4_smooth.obj; total meshData size so far: { 42654672 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 15 }:{ 16 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 16 }, with id: { 400 }:{ 16 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 16 }:{ 17 }
[MeshData] LoadModel: models/icosphere_subdiv3_0.75_smooth.obj; total meshData size so far: { 42700752 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 16 }:{ 17 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 17 }, with id: { 400 }:{ 17 }:{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 17 }:{ 18 }
[MeshData] LoadModel: models/tube_light_1_03.obj; total meshData size so far: { 42880464 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 17 }:{ 18 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 18 }, with id: { 400 }:{ 18 }:{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 18 }:{ 19 }
[MeshData] LoadModel: models/SudaBeam.obj; total meshData size so far: { 43348752 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 18 }:{ 19 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 19 }, with id: { 400 }:{ 19 }:{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 19 }:{ 20 }
[MeshData] LoadModel: models/Squid_Happy_Grumpy.obj; total meshData size so far: { 43747344 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 19 }:{ 20 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]   Found free item at index: { 20 }, with id: { 400 }:{ 20 }:{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]    { 400 }:{ 20 }:{ 21 }
[MeshData] LoadModel: models/SuzanneHighQuality20k.obj; total meshData size so far: { 46632528 }
[Game][GameData][LoadGameWorld][Component][Model]        Configured component with id: "{ 400 }:{ 20 }:{ 21 }", is std::type_index(typeid(Model)): true.

[GameDataPool][Constructed<MATERIAL_COMPONENTS>] maxPossibleSize: "{ 50 }", globalUIDSeed: "{ 600 }_MATERIAL_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Material.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 0 }, with id: { 600 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 0 }:{ 1 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 0 }:{ 1 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 1 }, with id: { 600 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 1 }:{ 2 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 1 }:{ 2 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 2 }, with id: { 600 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 2 }:{ 3 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 2 }:{ 3 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 3 }, with id: { 600 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 3 }:{ 4 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 3 }:{ 4 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 4 }, with id: { 600 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 4 }:{ 5 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 4 }:{ 5 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 5 }, with id: { 600 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 5 }:{ 6 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 5 }:{ 6 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 6 }, with id: { 600 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 6 }:{ 7 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 6 }:{ 7 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 7 }, with id: { 600 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 7 }:{ 8 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 7 }:{ 8 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 28 }, with id: { 600 }:{ 28 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 28 }:{ 9 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 28 }:{ 9 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 29 }, with id: { 600 }:{ 29 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 29 }:{ 10 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 29 }:{ 10 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 30 }, with id: { 600 }:{ 30 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 30 }:{ 11 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 30 }:{ 11 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 31 }, with id: { 600 }:{ 31 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 31 }:{ 12 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 31 }:{ 12 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 32 }, with id: { 600 }:{ 32 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 32 }:{ 13 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 32 }:{ 13 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 33 }, with id: { 600 }:{ 33 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 33 }:{ 14 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 33 }:{ 14 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 34 }, with id: { 600 }:{ 34 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 34 }:{ 15 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 34 }:{ 15 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 35 }, with id: { 600 }:{ 35 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 35 }:{ 16 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 35 }:{ 16 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 36 }, with id: { 600 }:{ 36 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 36 }:{ 17 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 36 }:{ 17 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 37 }, with id: { 600 }:{ 37 }:{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 37 }:{ 18 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 37 }:{ 18 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 38 }, with id: { 600 }:{ 38 }:{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 38 }:{ 19 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 38 }:{ 19 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 39 }, with id: { 600 }:{ 39 }:{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 39 }:{ 20 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 39 }:{ 20 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]        Found free item at index: { 40 }, with id: { 600 }:{ 40 }:{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]         { 600 }:{ 40 }:{ 21 }
[Game][GameData][LoadGameWorld][Component][Material]     Configured component with id: "{ 600 }:{ 40 }:{ 21 }", is std::type_index(typeid(Material)): true.

[GameDataPool][Constructed<LIGHT_COMPONENTS>] maxPossibleSize: "{ 10 }", globalUIDSeed: "{ 700 }_LIGHT_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Light.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]   Found free item at index: { 0 }, with id: { 700 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]    { 700 }:{ 0 }:{ 1 }
[Game][GameData][LoadGameWorld][Component][Light]        Configured component with id: "{ 700 }:{ 0 }:{ 1 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]   Found free item at index: { 1 }, with id: { 700 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]    { 700 }:{ 1 }:{ 2 }
[Game][GameData][LoadGameWorld][Component][Light]        Configured component with id: "{ 700 }:{ 1 }:{ 2 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]   Found free item at index: { 2 }, with id: { 700 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]    { 700 }:{ 2 }:{ 3 }
[Game][GameData][LoadGameWorld][Component][Light]        Configured component with id: "{ 700 }:{ 2 }:{ 3 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]   Found free item at index: { 3 }, with id: { 700 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]    { 700 }:{ 3 }:{ 4 }
[Game][GameData][LoadGameWorld][Component][Light]        Configured component with id: "{ 700 }:{ 3 }:{ 4 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]   Found free item at index: { 4 }, with id: { 700 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]    { 700 }:{ 4 }:{ 5 }
[Game][GameData][LoadGameWorld][Component][Light]        Configured component with id: "{ 700 }:{ 4 }:{ 5 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]   Found free item at index: { 5 }, with id: { 700 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]    { 700 }:{ 5 }:{ 6 }
[Game][GameData][LoadGameWorld][Component][Light]        Configured component with id: "{ 700 }:{ 5 }:{ 6 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]   Found free item at index: { 6 }, with id: { 700 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]    { 700 }:{ 6 }:{ 7 }
[Game][GameData][LoadGameWorld][Component][Light]        Configured component with id: "{ 700 }:{ 6 }:{ 7 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]   Found free item at index: { 7 }, with id: { 700 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]    { 700 }:{ 7 }:{ 8 }
[Game][GameData][LoadGameWorld][Component][Light]        Configured component with id: "{ 700 }:{ 7 }:{ 8 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]   Found free item at index: { 8 }, with id: { 700 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]    { 700 }:{ 8 }:{ 9 }
[Game][GameData][LoadGameWorld][Component][Light]        Configured component with id: "{ 700 }:{ 8 }:{ 9 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]   Found free item at index: { 9 }, with id: { 700 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]    { 700 }:{ 9 }:{ 10 }
[Game][GameData][LoadGameWorld][Component][Light]        Configured component with id: "{ 700 }:{ 9 }:{ 10 }", is std::type_index(typeid(Light)): true.

[GameDataPool][Constructed<GAME_ENTITY_OBJECTS>] maxPossibleSize: "{ 100 }", globalUIDSeed: "{ 100 }_GAME_ENTITY_OBJECTS", firstEmptyIndex: { 0 }, T: struct Game::GameEntityObject.

[GameDataPool][Constructed<GAME_VFX_OBJECTS>] maxPossibleSize: "{ 4 }", globalUIDSeed: "{ 200 }_GAME_VFX_OBJECTS", firstEmptyIndex: { 0 }, T: struct Game::GameEntityObject.

[GameDataPool][Constructed<TRANSFORM_COMPONENTS>] maxPossibleSize: "{ 100 }", globalUIDSeed: "{ 300 }_TRANSFORM_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Transform.

[GameDataPool][Constructed<BOUNDS_COMPONENTS>] maxPossibleSize: "{ 32 }", globalUIDSeed: "{ 500 }_BOUNDS_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Bounds.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 0 }, with id: { 100 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 0 }:{ 1 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 0 }:{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 0 }, with id: { 300 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 0 }:{ 1 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "worldRoot", id: "{ 100 }:{ 0 }:{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 1 }, with id: { 100 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 1 }:{ 2 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 1 }:{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 1 }, with id: { 300 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 1 }:{ 2 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "mainDirectionalLight", id: "{ 100 }:{ 1 }:{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 2 }, with id: { 100 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 2 }:{ 3 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 2 }:{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 2 }, with id: { 300 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 2 }:{ 3 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 0 }, with id: { 500 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 0 }:{ 1 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "tentacle01", id: "{ 100 }:{ 2 }:{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 3 }, with id: { 100 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 3 }:{ 4 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 3 }:{ 4 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 3 }, with id: { 300 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 3 }:{ 4 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 1 }, with id: { 500 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 1 }:{ 2 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "tentacle02", id: "{ 100 }:{ 3 }:{ 4 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 4 }, with id: { 100 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 4 }:{ 5 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 4 }:{ 5 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 4 }, with id: { 300 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 4 }:{ 5 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 2 }, with id: { 500 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 2 }:{ 3 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "tentacle03", id: "{ 100 }:{ 4 }:{ 5 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 5 }, with id: { 100 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 5 }:{ 6 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 5 }:{ 6 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 5 }, with id: { 300 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 5 }:{ 6 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 3 }, with id: { 500 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 3 }:{ 4 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "tentacle04", id: "{ 100 }:{ 5 }:{ 6 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 6 }, with id: { 100 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 6 }:{ 7 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 6 }:{ 7 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 6 }, with id: { 300 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 6 }:{ 7 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 4 }, with id: { 500 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 4 }:{ 5 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "tentacle05", id: "{ 100 }:{ 6 }:{ 7 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 7 }, with id: { 100 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 7 }:{ 8 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 7 }:{ 8 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 7 }, with id: { 300 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 7 }:{ 8 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 5 }, with id: { 500 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 5 }:{ 6 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "tentacle06", id: "{ 100 }:{ 7 }:{ 8 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 8 }, with id: { 100 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 8 }:{ 9 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 8 }:{ 9 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 8 }, with id: { 300 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 8 }:{ 9 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 6 }, with id: { 500 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 6 }:{ 7 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "handLight01", id: "{ 100 }:{ 8 }:{ 9 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 9 }, with id: { 100 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 9 }:{ 10 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 9 }:{ 10 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 9 }, with id: { 300 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 9 }:{ 10 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 7 }, with id: { 500 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 7 }:{ 8 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "handLight02", id: "{ 100 }:{ 9 }:{ 10 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 10 }, with id: { 100 }:{ 10 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 10 }:{ 11 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 10 }:{ 11 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 10 }, with id: { 300 }:{ 10 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 10 }:{ 11 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "bikeLight", id: "{ 100 }:{ 10 }:{ 11 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 11 }, with id: { 100 }:{ 11 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 11 }:{ 12 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 11 }:{ 12 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 11 }, with id: { 300 }:{ 11 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 11 }:{ 12 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "icosphereSkybox", id: "{ 100 }:{ 11 }:{ 12 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 12 }, with id: { 100 }:{ 12 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 12 }:{ 13 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 12 }:{ 13 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 12 }, with id: { 300 }:{ 12 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 12 }:{ 13 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 8 }, with id: { 500 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 8 }:{ 9 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "handLeft", id: "{ 100 }:{ 12 }:{ 13 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 13 }, with id: { 100 }:{ 13 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 13 }:{ 14 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 13 }:{ 14 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 13 }, with id: { 300 }:{ 13 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 13 }:{ 14 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 9 }, with id: { 500 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 9 }:{ 10 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "handRight", id: "{ 100 }:{ 13 }:{ 14 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 14 }, with id: { 100 }:{ 14 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 14 }:{ 15 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 14 }:{ 15 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 14 }, with id: { 300 }:{ 14 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 14 }:{ 15 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 10 }, with id: { 500 }:{ 10 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 10 }:{ 11 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "ground", id: "{ 100 }:{ 14 }:{ 15 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 15 }, with id: { 100 }:{ 15 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 15 }:{ 16 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 15 }:{ 16 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 15 }, with id: { 300 }:{ 15 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 15 }:{ 16 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 11 }, with id: { 500 }:{ 11 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 11 }:{ 12 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "ruins", id: "{ 100 }:{ 15 }:{ 16 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 16 }, with id: { 100 }:{ 16 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 16 }:{ 17 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 16 }:{ 17 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 16 }, with id: { 300 }:{ 16 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 16 }:{ 17 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 12 }, with id: { 500 }:{ 12 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 12 }:{ 13 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "carLeft", id: "{ 100 }:{ 16 }:{ 17 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 17 }, with id: { 100 }:{ 17 }:{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 17 }:{ 18 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 17 }:{ 18 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 17 }, with id: { 300 }:{ 17 }:{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 17 }:{ 18 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 13 }, with id: { 500 }:{ 13 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 13 }:{ 14 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "carRight", id: "{ 100 }:{ 17 }:{ 18 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 18 }, with id: { 100 }:{ 18 }:{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 18 }:{ 19 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 18 }:{ 19 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 18 }, with id: { 300 }:{ 18 }:{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 18 }:{ 19 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 14 }, with id: { 500 }:{ 14 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 14 }:{ 15 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "beetle", id: "{ 100 }:{ 18 }:{ 19 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 19 }, with id: { 100 }:{ 19 }:{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 19 }:{ 20 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 19 }:{ 20 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 19 }, with id: { 300 }:{ 19 }:{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 19 }:{ 20 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 15 }, with id: { 500 }:{ 15 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 15 }:{ 16 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "beetleGlass", id: "{ 100 }:{ 19 }:{ 20 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 20 }, with id: { 100 }:{ 20 }:{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 20 }:{ 21 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 20 }:{ 21 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 20 }, with id: { 300 }:{ 20 }:{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 20 }:{ 21 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 16 }, with id: { 500 }:{ 16 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 16 }:{ 17 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "bike", id: "{ 100 }:{ 20 }:{ 21 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 21 }, with id: { 100 }:{ 21 }:{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 21 }:{ 22 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 21 }:{ 22 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 21 }, with id: { 300 }:{ 21 }:{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 21 }:{ 22 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 17 }, with id: { 500 }:{ 17 }:{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 17 }:{ 18 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "logo1", id: "{ 100 }:{ 21 }:{ 22 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 22 }, with id: { 100 }:{ 22 }:{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 22 }:{ 23 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 22 }:{ 23 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 22 }, with id: { 300 }:{ 22 }:{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 22 }:{ 23 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 18 }, with id: { 500 }:{ 18 }:{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 18 }:{ 19 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "logo2", id: "{ 100 }:{ 22 }:{ 23 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 23 }, with id: { 100 }:{ 23 }:{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 23 }:{ 24 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 23 }:{ 24 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 23 }, with id: { 300 }:{ 23 }:{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 23 }:{ 24 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 19 }, with id: { 500 }:{ 19 }:{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 19 }:{ 20 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "textLocomotion", id: "{ 100 }:{ 23 }:{ 24 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 24 }, with id: { 100 }:{ 24 }:{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 24 }:{ 25 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 24 }:{ 25 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 24 }, with id: { 300 }:{ 24 }:{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 24 }:{ 25 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 20 }, with id: { 500 }:{ 20 }:{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 20 }:{ 21 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "textSudaBeam", id: "{ 100 }:{ 24 }:{ 25 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 25 }, with id: { 100 }:{ 25 }:{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 25 }:{ 26 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 25 }:{ 26 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 25 }, with id: { 300 }:{ 25 }:{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 25 }:{ 26 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 21 }, with id: { 500 }:{ 21 }:{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 21 }:{ 22 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "textSeeControlsMd", id: "{ 100 }:{ 25 }:{ 26 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 26 }, with id: { 100 }:{ 26 }:{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 26 }:{ 27 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 26 }:{ 27 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 26 }, with id: { 300 }:{ 26 }:{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 26 }:{ 27 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 22 }, with id: { 500 }:{ 22 }:{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 22 }:{ 23 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "cube", id: "{ 100 }:{ 26 }:{ 27 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 27 }, with id: { 100 }:{ 27 }:{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 27 }:{ 28 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 27 }:{ 28 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 27 }, with id: { 300 }:{ 27 }:{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 27 }:{ 28 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 23 }, with id: { 500 }:{ 23 }:{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 23 }:{ 24 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "icosphereSmoothTripInstancing", id: "{ 100 }:{ 27 }:{ 28 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 28 }, with id: { 100 }:{ 28 }:{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 28 }:{ 29 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 28 }:{ 29 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 28 }, with id: { 300 }:{ 28 }:{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 28 }:{ 29 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 24 }, with id: { 500 }:{ 24 }:{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 24 }:{ 25 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "icosphereSmoothForInstancing", id: "{ 100 }:{ 28 }:{ 29 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 29 }, with id: { 100 }:{ 29 }:{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 29 }:{ 30 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 29 }:{ 30 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 29 }, with id: { 300 }:{ 29 }:{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 29 }:{ 30 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 25 }, with id: { 500 }:{ 25 }:{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 25 }:{ 26 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "sudaBeam01", id: "{ 100 }:{ 29 }:{ 30 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 30 }, with id: { 100 }:{ 30 }:{ 31 }, validSize: { 31 }, currentVersion: { 31 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 30 }:{ 31 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 30 }:{ 31 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 30 }, with id: { 300 }:{ 30 }:{ 31 }, validSize: { 31 }, currentVersion: { 31 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 30 }:{ 31 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 26 }, with id: { 500 }:{ 26 }:{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 26 }:{ 27 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "sudaBeam02", id: "{ 100 }:{ 30 }:{ 31 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 31 }, with id: { 100 }:{ 31 }:{ 32 }, validSize: { 32 }, currentVersion: { 32 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 31 }:{ 32 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 31 }:{ 32 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 31 }, with id: { 300 }:{ 31 }:{ 32 }, validSize: { 32 }, currentVersion: { 32 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 31 }:{ 32 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 27 }, with id: { 500 }:{ 27 }:{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 27 }:{ 28 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "squid", id: "{ 100 }:{ 31 }:{ 32 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 32 }, with id: { 100 }:{ 32 }:{ 33 }, validSize: { 33 }, currentVersion: { 33 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 32 }:{ 33 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 32 }:{ 33 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 32 }, with id: { 300 }:{ 32 }:{ 33 }, validSize: { 33 }, currentVersion: { 33 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 32 }:{ 33 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 28 }, with id: { 500 }:{ 28 }:{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 28 }:{ 29 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "monke", id: "{ 100 }:{ 32 }:{ 33 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 33 }, with id: { 100 }:{ 33 }:{ 34 }, validSize: { 34 }, currentVersion: { 34 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 33 }:{ 34 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 33 }:{ 34 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 33 }, with id: { 300 }:{ 33 }:{ 34 }, validSize: { 34 }, currentVersion: { 34 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 33 }:{ 34 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 29 }, with id: { 500 }:{ 29 }:{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 29 }:{ 30 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "monkeEye1", id: "{ 100 }:{ 33 }:{ 34 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]        Found free item at index: { 34 }, with id: { 100 }:{ 34 }:{ 35 }, validSize: { 35 }, currentVersion: { 35 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]         { 100 }:{ 34 }:{ 35 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 100 }:{ 34 }:{ 35 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 34 }, with id: { 300 }:{ 34 }:{ 35 }, validSize: { 35 }, currentVersion: { 35 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 34 }:{ 35 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]  Found free item at index: { 30 }, with id: { 500 }:{ 30 }:{ 31 }, validSize: { 31 }, currentVersion: { 31 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]   { 500 }:{ 30 }:{ 31 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "monkeEye2", id: "{ 100 }:{ 34 }:{ 35 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_VFX_OBJECTS>]   Found free item at index: { 0 }, with id: { 200 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<GAME_VFX_OBJECTS>]    { 200 }:{ 0 }:{ 1 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 200 }:{ 0 }:{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 35 }, with id: { 300 }:{ 35 }:{ 36 }, validSize: { 36 }, currentVersion: { 36 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 35 }:{ 36 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "icosphereSkybox", id: "{ 200 }:{ 0 }:{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_VFX_OBJECTS>]   Found free item at index: { 1 }, with id: { 200 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<GAME_VFX_OBJECTS>]    { 200 }:{ 1 }:{ 2 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 200 }:{ 1 }:{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 36 }, with id: { 300 }:{ 36 }:{ 37 }, validSize: { 37 }, currentVersion: { 37 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 36 }:{ 37 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "floorGrid", id: "{ 200 }:{ 1 }:{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_VFX_OBJECTS>]   Found free item at index: { 2 }, with id: { 200 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<GAME_VFX_OBJECTS>]    { 200 }:{ 2 }:{ 3 }
[Game][GameData][GameEntityObject]       Using: {name: "game object", id: "{ 200 }:{ 2 }:{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]       Found free item at index: { 37 }, with id: { 300 }:{ 37 }:{ 38 }, validSize: { 38 }, currentVersion: { 38 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]        { 300 }:{ 37 }:{ 38 }
[Game][GameData][LoadGameWorld][GameEntityObject]        Configured {name: "ceilingGrid", id: "{ 200 }:{ 2 }:{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[Game][GameData][LoadGameWorld][GameEntityObject]        Done configuring entities.

~~~~[Scripting] setting ground size:
~~~~[Scripting] setting floorGrid.
~~~~[Scripting] setting ceilingGrid.
[Scripting] Finished settup up startup scripted setups.

[RenderProcess][framesInFlight: { 2 }] Binded (bound) Descriptor Sets: total size for vertex & fragment data (and both static and dynamic data)
        aka uniformBufferSize: { 21312 };
        sizeof(StaticVertexUniformData): { 524 };
        sizeof(StaticFragmentUniformData): { 720 };
        sizeof(DynamicVertexUniformData): { 100 };
        sizeof(DynamicFragmentUniformData): { 48 };
        gameObjectCount: { 104 };
[RenderProcess] Finished Update Render process / descriptor sets.
[RenderProcess][framesInFlight: { 2 }] Binded (bound) Descriptor Sets: total size for vertex & fragment data (and both static and dynamic data)
        aka uniformBufferSize: { 21312 };
        sizeof(StaticVertexUniformData): { 524 };
        sizeof(StaticFragmentUniformData): { 720 };
        sizeof(DynamicVertexUniformData): { 100 };
        sizeof(DynamicFragmentUniformData): { 48 };
        gameObjectCount: { 104 };
[RenderProcess] Finished Update Render process / descriptor sets.
[Renderer] meshDataTotalSize: { 46632528 }
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.653764})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.302141}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.335142}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.369382}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.771381}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.625420})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.304346}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.337200}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.367262}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.753908}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.639132})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.302058}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.336815}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.369145}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.754465}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.633367})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.301119}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.332795}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.368726}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.768315}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.635300})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.302652}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.335902}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.369035}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.759811}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] TeleportRequest::State::Requested
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.877922})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.729590})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.607158})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.446616})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.370158})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.280601}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.292912}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.303870}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.314147}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.326876}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.339073}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.349599}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.364192}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.374281}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.386708}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.486731}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.596881}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.739753}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.836838}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.965659}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.615682})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.303346}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.335584}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.369440}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.780915}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.621447})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.303899}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.336658}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.371234}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.763600}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.624853})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.306974}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.335724}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.367689}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.755986}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.640544})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.305642}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.337170}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.371342}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.759603}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.645059})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.302568}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.334219}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.372236}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.752495}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.638221})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.303495}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.334301}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.368522}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.735361}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.651266})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.300497}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.333366}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.369504}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.771140}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.664367})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.284418})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.302901}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.335944}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.366814}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.755482}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.638403})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.302513}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.336821}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.370307}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.756597}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.643567})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.302707}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.334583}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.367207}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.708523}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.651157})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.301690}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.339577}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.369091}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.769648}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.628651})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.303404}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.336722}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.370919}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.775589}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.616474})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.304295}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.336981}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.370562}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.714717}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] TeleportRequest::State::Requested
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.879100})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.735234})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.626680})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.491370})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.368371})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.281282}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.293086}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.305359}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.318345}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.332424}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.340389}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.352367}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.362967}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.374558}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.384859}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.507694}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.628976}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.757438}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.872246}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.998235}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.626324})
[LocomotionBehaviour][log] VisualsState::Start (anim: {0.270000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.303522}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.337095}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.369735}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Intro (anim: {0.390000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log]      MovementState::Start
[LocomotionBehaviour][log]      MovementState::End
[LocomotionBehaviour][log] VisualsState::Outro (anim: {0.764550}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::Outro (anim: {1.000000}, chaperoneRingRadius: {0.390000})
[LocomotionBehaviour][log] VisualsState::End
[Game][GameData][UnLoadGameWorld]        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][UnLoadGameWorld]        Unloading entities and components, unhooking events, clearing any maps:
[GameDataPool][ClearItems<GAME_ENTITY_OBJECTS>]  Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<GAME_ENTITY_OBJECTS>]  Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[GameEntityObject]       clearing this item: worldRoot; id: { 100 }:{ 0 }:{ 1 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 0 }:{ 1 }
[GameEntityObject]       clearing this item: mainDirectionalLight; id: { 100 }:{ 1 }:{ 2 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 1 }:{ 2 }
[GameEntityObject]       clearing this item: tentacle01; id: { 100 }:{ 2 }:{ 3 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 2 }:{ 3 }
[GameEntityObject]       clearing this item: tentacle02; id: { 100 }:{ 3 }:{ 4 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 3 }:{ 4 }
[GameEntityObject]       clearing this item: tentacle03; id: { 100 }:{ 4 }:{ 5 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 4 }:{ 5 }
[GameEntityObject]       clearing this item: tentacle04; id: { 100 }:{ 5 }:{ 6 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 5 }:{ 6 }
[GameEntityObject]       clearing this item: tentacle05; id: { 100 }:{ 6 }:{ 7 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 6 }:{ 7 }
[GameEntityObject]       clearing this item: tentacle06; id: { 100 }:{ 7 }:{ 8 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 7 }:{ 8 }
[GameEntityObject]       clearing this item: handLight01; id: { 100 }:{ 8 }:{ 9 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 8 }:{ 9 }
[GameEntityObject]       clearing this item: handLight02; id: { 100 }:{ 9 }:{ 10 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 9 }:{ 10 }
[GameEntityObject]       clearing this item: bikeLight; id: { 100 }:{ 10 }:{ 11 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 10 }:{ 11 }
[GameEntityObject]       clearing this item: icosphereSkybox; id: { 100 }:{ 11 }:{ 12 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 11 }:{ 12 }
[GameEntityObject]       clearing this item: handLeft; id: { 100 }:{ 12 }:{ 13 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 12 }:{ 13 }
[GameEntityObject]       clearing this item: handRight; id: { 100 }:{ 13 }:{ 14 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 13 }:{ 14 }
[GameEntityObject]       clearing this item: ground; id: { 100 }:{ 14 }:{ 15 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 14 }:{ 15 }
[GameEntityObject]       clearing this item: ruins; id: { 100 }:{ 15 }:{ 16 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 15 }:{ 16 }
[GameEntityObject]       clearing this item: carLeft; id: { 100 }:{ 16 }:{ 17 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 16 }:{ 17 }
[GameEntityObject]       clearing this item: carRight; id: { 100 }:{ 17 }:{ 18 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 17 }:{ 18 }
[GameEntityObject]       clearing this item: beetle; id: { 100 }:{ 18 }:{ 19 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 18 }:{ 19 }
[GameEntityObject]       clearing this item: beetleGlass; id: { 100 }:{ 19 }:{ 20 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 19 }:{ 20 }
[GameEntityObject]       clearing this item: bike; id: { 100 }:{ 20 }:{ 21 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 20 }:{ 21 }
[GameEntityObject]       clearing this item: logo1; id: { 100 }:{ 21 }:{ 22 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 21 }:{ 22 }
[GameEntityObject]       clearing this item: logo2; id: { 100 }:{ 22 }:{ 23 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 22 }:{ 23 }
[GameEntityObject]       clearing this item: textLocomotion; id: { 100 }:{ 23 }:{ 24 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 23 }:{ 24 }
[GameEntityObject]       clearing this item: textSudaBeam; id: { 100 }:{ 24 }:{ 25 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 24 }:{ 25 }
[GameEntityObject]       clearing this item: textSeeControlsMd; id: { 100 }:{ 25 }:{ 26 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 25 }:{ 26 }
[GameEntityObject]       clearing this item: cube; id: { 100 }:{ 26 }:{ 27 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 26 }:{ 27 }
[GameEntityObject]       clearing this item: icosphereSmoothTripInstancing; id: { 100 }:{ 27 }:{ 28 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 27 }:{ 28 }
[GameEntityObject]       clearing this item: icosphereSmoothForInstancing; id: { 100 }:{ 28 }:{ 29 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 28 }:{ 29 }
[GameEntityObject]       clearing this item: sudaBeam01; id: { 100 }:{ 29 }:{ 30 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 29 }:{ 30 }
[GameEntityObject]       clearing this item: sudaBeam02; id: { 100 }:{ 30 }:{ 31 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 30 }:{ 31 }
[GameEntityObject]       clearing this item: squid; id: { 100 }:{ 31 }:{ 32 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 31 }:{ 32 }
[GameEntityObject]       clearing this item: monke; id: { 100 }:{ 32 }:{ 33 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 32 }:{ 33 }
[GameEntityObject]       clearing this item: monkeEye1; id: { 100 }:{ 33 }:{ 34 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 33 }:{ 34 }
[GameEntityObject]       clearing this item: monkeEye2; id: { 100 }:{ 34 }:{ 35 }
[Game][GameDataId]       Id Cleared: { 100 }:{ 34 }:{ 35 }
[GameDataPool][Destructed<GAME_ENTITY_OBJECTS>] and all its heap items.

[GameDataPool][ClearItems<GAME_VFX_OBJECTS>]     Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<GAME_VFX_OBJECTS>]     Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[GameEntityObject]       clearing this item: icosphereSkybox; id: { 200 }:{ 0 }:{ 1 }
[Game][GameDataId]       Id Cleared: { 200 }:{ 0 }:{ 1 }
[GameEntityObject]       clearing this item: floorGrid; id: { 200 }:{ 1 }:{ 2 }
[Game][GameDataId]       Id Cleared: { 200 }:{ 1 }:{ 2 }
[GameEntityObject]       clearing this item: ceilingGrid; id: { 200 }:{ 2 }:{ 3 }
[Game][GameDataId]       Id Cleared: { 200 }:{ 2 }:{ 3 }
[GameDataPool][Destructed<GAME_VFX_OBJECTS>] and all its heap items.

[GameDataPool][ClearItems<TRANSFORM_COMPONENTS>]         Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<TRANSFORM_COMPONENTS>]         Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[Component][Transform]   clearing this item: { 300 }:{ 0 }:{ 1 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 0 }:{ 1 }
[Component][Transform]   clearing this item: { 300 }:{ 1 }:{ 2 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 1 }:{ 2 }
[Component][Transform]   clearing this item: { 300 }:{ 2 }:{ 3 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 2 }:{ 3 }
[Component][Transform]   clearing this item: { 300 }:{ 3 }:{ 4 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 3 }:{ 4 }
[Component][Transform]   clearing this item: { 300 }:{ 4 }:{ 5 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 4 }:{ 5 }
[Component][Transform]   clearing this item: { 300 }:{ 5 }:{ 6 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 5 }:{ 6 }
[Component][Transform]   clearing this item: { 300 }:{ 6 }:{ 7 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 6 }:{ 7 }
[Component][Transform]   clearing this item: { 300 }:{ 7 }:{ 8 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 7 }:{ 8 }
[Component][Transform]   clearing this item: { 300 }:{ 8 }:{ 9 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 8 }:{ 9 }
[Component][Transform]   clearing this item: { 300 }:{ 9 }:{ 10 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 9 }:{ 10 }
[Component][Transform]   clearing this item: { 300 }:{ 10 }:{ 11 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 10 }:{ 11 }
[Component][Transform]   clearing this item: { 300 }:{ 11 }:{ 12 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 11 }:{ 12 }
[Component][Transform]   clearing this item: { 300 }:{ 12 }:{ 13 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 12 }:{ 13 }
[Component][Transform]   clearing this item: { 300 }:{ 13 }:{ 14 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 13 }:{ 14 }
[Component][Transform]   clearing this item: { 300 }:{ 14 }:{ 15 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 14 }:{ 15 }
[Component][Transform]   clearing this item: { 300 }:{ 15 }:{ 16 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 15 }:{ 16 }
[Component][Transform]   clearing this item: { 300 }:{ 16 }:{ 17 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 16 }:{ 17 }
[Component][Transform]   clearing this item: { 300 }:{ 17 }:{ 18 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 17 }:{ 18 }
[Component][Transform]   clearing this item: { 300 }:{ 18 }:{ 19 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 18 }:{ 19 }
[Component][Transform]   clearing this item: { 300 }:{ 19 }:{ 20 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 19 }:{ 20 }
[Component][Transform]   clearing this item: { 300 }:{ 20 }:{ 21 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 20 }:{ 21 }
[Component][Transform]   clearing this item: { 300 }:{ 21 }:{ 22 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 21 }:{ 22 }
[Component][Transform]   clearing this item: { 300 }:{ 22 }:{ 23 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 22 }:{ 23 }
[Component][Transform]   clearing this item: { 300 }:{ 23 }:{ 24 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 23 }:{ 24 }
[Component][Transform]   clearing this item: { 300 }:{ 24 }:{ 25 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 24 }:{ 25 }
[Component][Transform]   clearing this item: { 300 }:{ 25 }:{ 26 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 25 }:{ 26 }
[Component][Transform]   clearing this item: { 300 }:{ 26 }:{ 27 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 26 }:{ 27 }
[Component][Transform]   clearing this item: { 300 }:{ 27 }:{ 28 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 27 }:{ 28 }
[Component][Transform]   clearing this item: { 300 }:{ 28 }:{ 29 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 28 }:{ 29 }
[Component][Transform]   clearing this item: { 300 }:{ 29 }:{ 30 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 29 }:{ 30 }
[Component][Transform]   clearing this item: { 300 }:{ 30 }:{ 31 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 30 }:{ 31 }
[Component][Transform]   clearing this item: { 300 }:{ 31 }:{ 32 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 31 }:{ 32 }
[Component][Transform]   clearing this item: { 300 }:{ 32 }:{ 33 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 32 }:{ 33 }
[Component][Transform]   clearing this item: { 300 }:{ 33 }:{ 34 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 33 }:{ 34 }
[Component][Transform]   clearing this item: { 300 }:{ 34 }:{ 35 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 34 }:{ 35 }
[Component][Transform]   clearing this item: { 300 }:{ 35 }:{ 36 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 35 }:{ 36 }
[Component][Transform]   clearing this item: { 300 }:{ 36 }:{ 37 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 36 }:{ 37 }
[Component][Transform]   clearing this item: { 300 }:{ 37 }:{ 38 }
[Game][GameDataId]       Id Cleared: { 300 }:{ 37 }:{ 38 }
[GameDataPool][Destructed<TRANSFORM_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<MODEL_COMPONENTS>]     Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<MODEL_COMPONENTS>]     Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[Component][Model]       clearing this item: { 400 }:{ 0 }:{ 1 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 0 }:{ 1 }
[Component][Model]       clearing this item: { 400 }:{ 1 }:{ 2 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 1 }:{ 2 }
[Component][Model]       clearing this item: { 400 }:{ 2 }:{ 3 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 2 }:{ 3 }
[Component][Model]       clearing this item: { 400 }:{ 3 }:{ 4 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 3 }:{ 4 }
[Component][Model]       clearing this item: { 400 }:{ 4 }:{ 5 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 4 }:{ 5 }
[Component][Model]       clearing this item: { 400 }:{ 5 }:{ 6 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 5 }:{ 6 }
[Component][Model]       clearing this item: { 400 }:{ 6 }:{ 7 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 6 }:{ 7 }
[Component][Model]       clearing this item: { 400 }:{ 7 }:{ 8 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 7 }:{ 8 }
[Component][Model]       clearing this item: { 400 }:{ 8 }:{ 9 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 8 }:{ 9 }
[Component][Model]       clearing this item: { 400 }:{ 9 }:{ 10 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 9 }:{ 10 }
[Component][Model]       clearing this item: { 400 }:{ 10 }:{ 11 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 10 }:{ 11 }
[Component][Model]       clearing this item: { 400 }:{ 11 }:{ 12 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 11 }:{ 12 }
[Component][Model]       clearing this item: { 400 }:{ 12 }:{ 13 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 12 }:{ 13 }
[Component][Model]       clearing this item: { 400 }:{ 13 }:{ 14 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 13 }:{ 14 }
[Component][Model]       clearing this item: { 400 }:{ 14 }:{ 15 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 14 }:{ 15 }
[Component][Model]       clearing this item: { 400 }:{ 15 }:{ 16 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 15 }:{ 16 }
[Component][Model]       clearing this item: { 400 }:{ 16 }:{ 17 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 16 }:{ 17 }
[Component][Model]       clearing this item: { 400 }:{ 17 }:{ 18 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 17 }:{ 18 }
[Component][Model]       clearing this item: { 400 }:{ 18 }:{ 19 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 18 }:{ 19 }
[Component][Model]       clearing this item: { 400 }:{ 19 }:{ 20 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 19 }:{ 20 }
[Component][Model]       clearing this item: { 400 }:{ 20 }:{ 21 }
[Game][GameDataId]       Id Cleared: { 400 }:{ 20 }:{ 21 }
[GameDataPool][Destructed<MODEL_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<BOUNDS_COMPONENTS>]    Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<BOUNDS_COMPONENTS>]    Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[Component][Bounds]      clearing this item: { 500 }:{ 0 }:{ 1 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 0 }:{ 1 }
[Component][Bounds]      clearing this item: { 500 }:{ 1 }:{ 2 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 1 }:{ 2 }
[Component][Bounds]      clearing this item: { 500 }:{ 2 }:{ 3 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 2 }:{ 3 }
[Component][Bounds]      clearing this item: { 500 }:{ 3 }:{ 4 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 3 }:{ 4 }
[Component][Bounds]      clearing this item: { 500 }:{ 4 }:{ 5 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 4 }:{ 5 }
[Component][Bounds]      clearing this item: { 500 }:{ 5 }:{ 6 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 5 }:{ 6 }
[Component][Bounds]      clearing this item: { 500 }:{ 6 }:{ 7 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 6 }:{ 7 }
[Component][Bounds]      clearing this item: { 500 }:{ 7 }:{ 8 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 7 }:{ 8 }
[Component][Bounds]      clearing this item: { 500 }:{ 8 }:{ 9 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 8 }:{ 9 }
[Component][Bounds]      clearing this item: { 500 }:{ 9 }:{ 10 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 9 }:{ 10 }
[Component][Bounds]      clearing this item: { 500 }:{ 10 }:{ 11 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 10 }:{ 11 }
[Component][Bounds]      clearing this item: { 500 }:{ 11 }:{ 12 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 11 }:{ 12 }
[Component][Bounds]      clearing this item: { 500 }:{ 12 }:{ 13 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 12 }:{ 13 }
[Component][Bounds]      clearing this item: { 500 }:{ 13 }:{ 14 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 13 }:{ 14 }
[Component][Bounds]      clearing this item: { 500 }:{ 14 }:{ 15 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 14 }:{ 15 }
[Component][Bounds]      clearing this item: { 500 }:{ 15 }:{ 16 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 15 }:{ 16 }
[Component][Bounds]      clearing this item: { 500 }:{ 16 }:{ 17 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 16 }:{ 17 }
[Component][Bounds]      clearing this item: { 500 }:{ 17 }:{ 18 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 17 }:{ 18 }
[Component][Bounds]      clearing this item: { 500 }:{ 18 }:{ 19 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 18 }:{ 19 }
[Component][Bounds]      clearing this item: { 500 }:{ 19 }:{ 20 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 19 }:{ 20 }
[Component][Bounds]      clearing this item: { 500 }:{ 20 }:{ 21 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 20 }:{ 21 }
[Component][Bounds]      clearing this item: { 500 }:{ 21 }:{ 22 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 21 }:{ 22 }
[Component][Bounds]      clearing this item: { 500 }:{ 22 }:{ 23 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 22 }:{ 23 }
[Component][Bounds]      clearing this item: { 500 }:{ 23 }:{ 24 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 23 }:{ 24 }
[Component][Bounds]      clearing this item: { 500 }:{ 24 }:{ 25 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 24 }:{ 25 }
[Component][Bounds]      clearing this item: { 500 }:{ 25 }:{ 26 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 25 }:{ 26 }
[Component][Bounds]      clearing this item: { 500 }:{ 26 }:{ 27 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 26 }:{ 27 }
[Component][Bounds]      clearing this item: { 500 }:{ 27 }:{ 28 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 27 }:{ 28 }
[Component][Bounds]      clearing this item: { 500 }:{ 28 }:{ 29 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 28 }:{ 29 }
[Component][Bounds]      clearing this item: { 500 }:{ 29 }:{ 30 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 29 }:{ 30 }
[Component][Bounds]      clearing this item: { 500 }:{ 30 }:{ 31 }
[Game][GameDataId]       Id Cleared: { 500 }:{ 30 }:{ 31 }
[GameDataPool][Destructed<BOUNDS_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[Component][Material]    clearing this item: { 600 }:{ 0 }:{ 1 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 0 }:{ 1 }
[Component][Material]    clearing this item: { 600 }:{ 1 }:{ 2 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 1 }:{ 2 }
[Component][Material]    clearing this item: { 600 }:{ 2 }:{ 3 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 2 }:{ 3 }
[Component][Material]    clearing this item: { 600 }:{ 3 }:{ 4 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 3 }:{ 4 }
[Component][Material]    clearing this item: { 600 }:{ 4 }:{ 5 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 4 }:{ 5 }
[Component][Material]    clearing this item: { 600 }:{ 5 }:{ 6 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 5 }:{ 6 }
[Component][Material]    clearing this item: { 600 }:{ 6 }:{ 7 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 6 }:{ 7 }
[Component][Material]    clearing this item: { 600 }:{ 7 }:{ 8 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 7 }:{ 8 }
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 8 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 9 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 10 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 11 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 12 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 13 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 14 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 15 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 16 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 17 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 18 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 19 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 20 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 21 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 22 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 23 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 24 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 25 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 26 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 600 }:{ 27 }:{ 0 }.
[Component][Material]    clearing this item: { 600 }:{ 28 }:{ 9 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 28 }:{ 9 }
[Component][Material]    clearing this item: { 600 }:{ 29 }:{ 10 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 29 }:{ 10 }
[Component][Material]    clearing this item: { 600 }:{ 30 }:{ 11 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 30 }:{ 11 }
[Component][Material]    clearing this item: { 600 }:{ 31 }:{ 12 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 31 }:{ 12 }
[Component][Material]    clearing this item: { 600 }:{ 32 }:{ 13 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 32 }:{ 13 }
[Component][Material]    clearing this item: { 600 }:{ 33 }:{ 14 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 33 }:{ 14 }
[Component][Material]    clearing this item: { 600 }:{ 34 }:{ 15 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 34 }:{ 15 }
[Component][Material]    clearing this item: { 600 }:{ 35 }:{ 16 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 35 }:{ 16 }
[Component][Material]    clearing this item: { 600 }:{ 36 }:{ 17 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 36 }:{ 17 }
[Component][Material]    clearing this item: { 600 }:{ 37 }:{ 18 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 37 }:{ 18 }
[Component][Material]    clearing this item: { 600 }:{ 38 }:{ 19 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 38 }:{ 19 }
[Component][Material]    clearing this item: { 600 }:{ 39 }:{ 20 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 39 }:{ 20 }
[Component][Material]    clearing this item: { 600 }:{ 40 }:{ 21 }
[Game][GameDataId]       Id Cleared: { 600 }:{ 40 }:{ 21 }
[GameDataPool][Destructed<MATERIAL_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<LIGHT_COMPONENTS>]     Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<LIGHT_COMPONENTS>]     Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[Component][Light]       clearing this item: { 700 }:{ 0 }:{ 1 }
[Game][GameDataId]       Id Cleared: { 700 }:{ 0 }:{ 1 }
[Component][Light]       clearing this item: { 700 }:{ 1 }:{ 2 }
[Game][GameDataId]       Id Cleared: { 700 }:{ 1 }:{ 2 }
[Component][Light]       clearing this item: { 700 }:{ 2 }:{ 3 }
[Game][GameDataId]       Id Cleared: { 700 }:{ 2 }:{ 3 }
[Component][Light]       clearing this item: { 700 }:{ 3 }:{ 4 }
[Game][GameDataId]       Id Cleared: { 700 }:{ 3 }:{ 4 }
[Component][Light]       clearing this item: { 700 }:{ 4 }:{ 5 }
[Game][GameDataId]       Id Cleared: { 700 }:{ 4 }:{ 5 }
[Component][Light]       clearing this item: { 700 }:{ 5 }:{ 6 }
[Game][GameDataId]       Id Cleared: { 700 }:{ 5 }:{ 6 }
[Component][Light]       clearing this item: { 700 }:{ 6 }:{ 7 }
[Game][GameDataId]       Id Cleared: { 700 }:{ 6 }:{ 7 }
[Component][Light]       clearing this item: { 700 }:{ 7 }:{ 8 }
[Game][GameDataId]       Id Cleared: { 700 }:{ 7 }:{ 8 }
[Component][Light]       clearing this item: { 700 }:{ 8 }:{ 9 }
[Game][GameDataId]       Id Cleared: { 700 }:{ 8 }:{ 9 }
[Component][Light]       clearing this item: { 700 }:{ 9 }:{ 10 }
[Game][GameDataId]       Id Cleared: { 700 }:{ 9 }:{ 10 }
[GameDataPool][Destructed<LIGHT_COMPONENTS>] and all its heap items.

[Game][Main][EXIT_SUCCESS]       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
</details>