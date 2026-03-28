What a typical run log looks like, with `DEBUG` and `DEBUG_VERBOSE` turned on. Game world load, setup, updates & render loops, unload and exit.
```
[Game][Main][Starting]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][Main][Starting]	DEBUG flag enabled from CMakeLists.txt
[Game][Main][Starting]	DEBUG_VERBOSE flag enabled from CMakeLists.txt

ipcLoader [RUNTIMEIPC]RuntimeIPC: Loaded library from C:\Program Files\Oculus\Support\oculus-runtime\RuntimeIPCServiceClient_64.dll
[Context][createDevice] ~~~~~~~~~~~~~~~~~~~
[Context][createDevice] physicalDeviceProperties.deviceName: true; physicalDeviceProperties.deviceType: { 1 }; physicalDeviceProperties.limits.maxViewports:{ 16 }; physicalDeviceProperties.limits.maxViewportDimensions[0]:{ 32768 }; physicalDeviceProperties.limits.maxViewportDimensions[1]:{ 32768 }
[Game][GameData][Singleton]	 All data pools are here. instanceId: "GameData_{ 0 }".
[Game][GameData][LoadGameWorlds]	 .........................................................................................................................
[Game][GameData][LoadGameWorlds]	  Loading Game World(s).
[Game][GameData][LoadGameWorlds]	  Loading, deserializing, creating pools for entities and components, hooking some events, creating some quick access maps:

[Game][GameData][LoadModels]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadModels]		 Loading Models

[GameDataPool][Constructed<MODEL_COMPONENTS>] maxPossiblePoolSize: "{ 32 }", world: { 0 }, typeUID: "{ 128 }_MODEL_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Model, tiles: { 1 }, tileSize: { 32 }, items.size(): { 1 }
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 0 }:0b10000000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 0 }:{ 1 }
[MeshData] LoadModel: models/quad.obj; total meshData size so far: { 288 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 0 }:{ 1 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 0 }:0b10000000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 1 }:{ 2 }
[MeshData] LoadModel: models/ground_displaced_4096.obj; total meshData size so far: { 590112 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 1 }:{ 2 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 2 }, with id: { 0 }:0b10000000:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 2 }:{ 3 }
[MeshData] LoadModel: models/Ruins.obj; total meshData size so far: { 17245728 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 2 }:{ 3 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 3 }, with id: { 0 }:0b10000000:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 3 }:{ 4 }
[MeshData] LoadModel: models/Car.obj; total meshData size so far: { 18525888 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 3 }:{ 4 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 4 }, with id: { 0 }:0b10000000:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 4 }:{ 5 }
[MeshData] LoadModel: models/Beetle_glassless.obj; total meshData size so far: { 24642720 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 4 }:{ 5 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 5 }, with id: { 0 }:0b10000000:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 5 }:{ 6 }
[MeshData] LoadModel: models/Beetle_glass_only.obj; total meshData size so far: { 24903360 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 5 }:{ 6 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 6 }, with id: { 0 }:0b10000000:{ 0 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 6 }:{ 7 }
[MeshData] LoadModel: models/Bike.obj; total meshData size so far: { 40369824 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 6 }:{ 7 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 7 }, with id: { 0 }:0b10000000:{ 0 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 7 }:{ 8 }
[MeshData] LoadModel: models/Hand.obj; total meshData size so far: { 40708368 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 7 }:{ 8 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 8 }, with id: { 0 }:0b10000000:{ 0 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 8 }:{ 9 }
[MeshData] LoadModel: models/cube.obj; total meshData size so far: { 40710096 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 8 }:{ 9 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 9 }, with id: { 0 }:0b10000000:{ 0 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 9 }:{ 10 }
[MeshData] LoadModel: models/Logo_OpenXR_Vulkan.obj; total meshData size so far: { 41134032 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 9 }:{ 10 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 10 }, with id: { 0 }:0b10000000:{ 0 }:{ 10 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 10 }:{ 11 }
[MeshData] LoadModel: models/Logo_Framework.obj; total meshData size so far: { 41486544 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 10 }:{ 11 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 11 }, with id: { 0 }:0b10000000:{ 0 }:{ 11 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 11 }:{ 12 }
[MeshData] LoadModel: models/Text_Locomotion_Flat.obj; total meshData size so far: { 41797872 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 11 }:{ 12 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 12 }, with id: { 0 }:0b10000000:{ 0 }:{ 12 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 12 }:{ 13 }
[MeshData] LoadModel: models/Text_Suda_Beam_Flat.obj; total meshData size so far: { 42086448 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 12 }:{ 13 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 13 }, with id: { 0 }:0b10000000:{ 0 }:{ 13 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 13 }:{ 14 }
[MeshData] LoadModel: models/Text_See_Controls_md.obj; total meshData size so far: { 42286032 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 13 }:{ 14 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 14 }, with id: { 0 }:0b10000000:{ 0 }:{ 14 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 14 }:{ 15 }
[MeshData] LoadModel: models/icosphere_subdiv4_half_smooth.obj; total meshData size so far: { 42470352 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 14 }:{ 15 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 15 }, with id: { 0 }:0b10000000:{ 0 }:{ 15 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 15 }:{ 16 }
[MeshData] LoadModel: models/icosphere_subdiv4_smooth.obj; total meshData size so far: { 42654672 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 15 }:{ 16 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 16 }, with id: { 0 }:0b10000000:{ 0 }:{ 16 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 16 }:{ 17 }
[MeshData] LoadModel: models/icosphere_subdiv3_0.75_smooth.obj; total meshData size so far: { 42700752 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 16 }:{ 17 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 17 }, with id: { 0 }:0b10000000:{ 0 }:{ 17 }:{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 17 }:{ 18 }
[MeshData] LoadModel: models/tube_light_1_03.obj; total meshData size so far: { 42880464 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 17 }:{ 18 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 18 }, with id: { 0 }:0b10000000:{ 0 }:{ 18 }:{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 18 }:{ 19 }
[MeshData] LoadModel: models/SudaBeam.obj; total meshData size so far: { 43348752 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 18 }:{ 19 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 19 }, with id: { 0 }:0b10000000:{ 0 }:{ 19 }:{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 19 }:{ 20 }
[MeshData] LoadModel: models/Squid_Happy_Grumpy.obj; total meshData size so far: { 43747344 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 19 }:{ 20 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<MODEL_COMPONENTS>]	 Found free item at index: { 20 }, with id: { 0 }:0b10000000:{ 0 }:{ 20 }:{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<MODEL_COMPONENTS>]	 { 0 }:0b10000000:{ 0 }:{ 20 }:{ 21 }
[MeshData] LoadModel: models/SuzanneHighQuality20k.obj; total meshData size so far: { 46632528 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "{ 0 }:0b10000000:{ 0 }:{ 20 }:{ 21 }", is std::type_index(typeid(Model)): true.

[Game][GameData][LoadMaterials]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadMaterials]		 Loading Materials

[GameDataPool][Constructed<MATERIAL_COMPONENTS>] maxPossiblePoolSize: "{ 50 }", world: { 0 }, typeUID: "{ 512 }_MATERIAL_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Material, tiles: { 1 }, tileSize: { 50 }, items.size(): { 1 }

[GameDataPool][Constructed<MATERIAL_COMPONENTS>] maxPossiblePoolSize: "{ 4 }", world: { 1 }, typeUID: "{ 512 }_MATERIAL_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Material, tiles: { 1 }, tileSize: { 4 }, items.size(): { 1 }
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 0 }:0b1000000000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 0 }:{ 1 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 0 }:{ 1 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 0 }:0b1000000000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 1 }:{ 2 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 1 }:{ 2 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 2 }, with id: { 0 }:0b1000000000:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 2 }:{ 3 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 2 }:{ 3 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 3 }, with id: { 0 }:0b1000000000:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 3 }:{ 4 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 3 }:{ 4 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 4 }, with id: { 0 }:0b1000000000:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 4 }:{ 5 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 4 }:{ 5 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 5 }, with id: { 0 }:0b1000000000:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 5 }:{ 6 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 5 }:{ 6 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 6 }, with id: { 0 }:0b1000000000:{ 0 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 6 }:{ 7 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 6 }:{ 7 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 7 }, with id: { 0 }:0b1000000000:{ 0 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 7 }:{ 8 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 7 }:{ 8 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 28 }, with id: { 0 }:0b1000000000:{ 0 }:{ 28 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 28 }:{ 9 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 28 }:{ 9 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 29 }, with id: { 0 }:0b1000000000:{ 0 }:{ 29 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 29 }:{ 10 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 29 }:{ 10 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 30 }, with id: { 0 }:0b1000000000:{ 0 }:{ 30 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 30 }:{ 11 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 30 }:{ 11 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 31 }, with id: { 0 }:0b1000000000:{ 0 }:{ 31 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 31 }:{ 12 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 31 }:{ 12 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 32 }, with id: { 0 }:0b1000000000:{ 0 }:{ 32 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 32 }:{ 13 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 32 }:{ 13 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 33 }, with id: { 0 }:0b1000000000:{ 0 }:{ 33 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 33 }:{ 14 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 33 }:{ 14 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 34 }, with id: { 0 }:0b1000000000:{ 0 }:{ 34 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 34 }:{ 15 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 34 }:{ 15 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 35 }, with id: { 0 }:0b1000000000:{ 0 }:{ 35 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 35 }:{ 16 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 35 }:{ 16 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 36 }, with id: { 0 }:0b1000000000:{ 0 }:{ 36 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 0 }:0b1000000000:{ 0 }:{ 36 }:{ 17 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 0 }:0b1000000000:{ 0 }:{ 36 }:{ 17 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 1 }:0b1000000000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 1 }:0b1000000000:{ 0 }:{ 0 }:{ 1 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 1 }:0b1000000000:{ 0 }:{ 0 }:{ 1 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 1 }:0b1000000000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 1 }:0b1000000000:{ 0 }:{ 1 }:{ 2 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 1 }:0b1000000000:{ 0 }:{ 1 }:{ 2 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 2 }, with id: { 1 }:0b1000000000:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 1 }:0b1000000000:{ 0 }:{ 2 }:{ 3 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 1 }:0b1000000000:{ 0 }:{ 2 }:{ 3 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<MATERIAL_COMPONENTS>]	 Found free item at index: { 3 }, with id: { 1 }:0b1000000000:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<MATERIAL_COMPONENTS>]	 { 1 }:0b1000000000:{ 0 }:{ 3 }:{ 4 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "{ 1 }:0b1000000000:{ 0 }:{ 3 }:{ 4 }", is std::type_index(typeid(Material)): true.

[Game][GameData][LoadLights]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadLights]		 Loading Lights

[GameDataPool][Constructed<LIGHT_COMPONENTS>] maxPossiblePoolSize: "{ 10 }", world: { 0 }, typeUID: "{ 1024 }_LIGHT_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Light, tiles: { 1 }, tileSize: { 10 }, items.size(): { 1 }
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 0 }:0b10000000000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]	 { 0 }:0b10000000000:{ 0 }:{ 0 }:{ 1 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "{ 0 }:0b10000000000:{ 0 }:{ 0 }:{ 1 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 0 }:0b10000000000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]	 { 0 }:0b10000000000:{ 0 }:{ 1 }:{ 2 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "{ 0 }:0b10000000000:{ 0 }:{ 1 }:{ 2 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]	 Found free item at index: { 2 }, with id: { 0 }:0b10000000000:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]	 { 0 }:0b10000000000:{ 0 }:{ 2 }:{ 3 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "{ 0 }:0b10000000000:{ 0 }:{ 2 }:{ 3 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]	 Found free item at index: { 3 }, with id: { 0 }:0b10000000000:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]	 { 0 }:0b10000000000:{ 0 }:{ 3 }:{ 4 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "{ 0 }:0b10000000000:{ 0 }:{ 3 }:{ 4 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]	 Found free item at index: { 4 }, with id: { 0 }:0b10000000000:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]	 { 0 }:0b10000000000:{ 0 }:{ 4 }:{ 5 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "{ 0 }:0b10000000000:{ 0 }:{ 4 }:{ 5 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]	 Found free item at index: { 5 }, with id: { 0 }:0b10000000000:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]	 { 0 }:0b10000000000:{ 0 }:{ 5 }:{ 6 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "{ 0 }:0b10000000000:{ 0 }:{ 5 }:{ 6 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]	 Found free item at index: { 6 }, with id: { 0 }:0b10000000000:{ 0 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]	 { 0 }:0b10000000000:{ 0 }:{ 6 }:{ 7 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "{ 0 }:0b10000000000:{ 0 }:{ 6 }:{ 7 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]	 Found free item at index: { 7 }, with id: { 0 }:0b10000000000:{ 0 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]	 { 0 }:0b10000000000:{ 0 }:{ 7 }:{ 8 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "{ 0 }:0b10000000000:{ 0 }:{ 7 }:{ 8 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]	 Found free item at index: { 8 }, with id: { 0 }:0b10000000000:{ 0 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]	 { 0 }:0b10000000000:{ 0 }:{ 8 }:{ 9 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "{ 0 }:0b10000000000:{ 0 }:{ 8 }:{ 9 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<LIGHT_COMPONENTS>]	 Found free item at index: { 9 }, with id: { 0 }:0b10000000000:{ 0 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<LIGHT_COMPONENTS>]	 { 0 }:0b10000000000:{ 0 }:{ 9 }:{ 10 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "{ 0 }:0b10000000000:{ 0 }:{ 9 }:{ 10 }", is std::type_index(typeid(Light)): true.

[Game][GameData][LoadGameEntityObjects]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadGameEntityObjects]		 Loading Game Entity Objects (main entityObjectsWorld)

[GameDataPool][Constructed<GAME_ENTITY_OBJECTS>] maxPossiblePoolSize: "{ 100 }", world: { 0 }, typeUID: "{ 2 }_GAME_ENTITY_OBJECTS", firstEmptyIndex: { 0 }, T: struct Game::GameEntityObject, tiles: { 1 }, tileSize: { 128 }, items.size(): { 1 }

[GameDataPool][Constructed<TRANSFORM_COMPONENTS>] maxPossiblePoolSize: "{ 100 }", world: { 0 }, typeUID: "{ 8 }_TRANSFORM_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Transform, tiles: { 1 }, tileSize: { 128 }, items.size(): { 1 }

[GameDataPool][Constructed<PARENT_COMPONENTS>] maxPossiblePoolSize: "{ 100 }", world: { 0 }, typeUID: "{ 16 }_PARENT_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Parent, tiles: { 1 }, tileSize: { 128 }, items.size(): { 1 }

[GameDataPool][Constructed<CHILDREN_COMPONENTS>] maxPossiblePoolSize: "{ 100 }", world: { 0 }, typeUID: "{ 32 }_CHILDREN_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Children, tiles: { 1 }, tileSize: { 128 }, items.size(): { 1 }

[GameDataPool][Constructed<BOUNDS_COMPONENTS>] maxPossiblePoolSize: "{ 32 }", world: { 0 }, typeUID: "{ 256 }_BOUNDS_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Bounds, tiles: { 1 }, tileSize: { 128 }, items.size(): { 1 }
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 0 }, with id: { 0 }:0b000010:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 0 }:{ 1 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 0 }:{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 0 }:0b001000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 0 }:{ 1 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 0 }:0b010000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 0 }:{ 1 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 0 }:0b100000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 0 }:{ 1 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "worldRoot", id: "{ 0 }:0b000010:{ 0 }:{ 0 }:{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 1 }, with id: { 0 }:0b000010:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 1 }:{ 2 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 1 }:{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 0 }:0b001000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 1 }:{ 2 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 0 }:0b010000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 1 }:{ 2 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 0 }:0b100000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 1 }:{ 2 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "mainDirectionalLight", id: "{ 0 }:0b000010:{ 0 }:{ 1 }:{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 2 }, with id: { 0 }:0b000010:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 2 }:{ 3 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 2 }:{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 2 }, with id: { 0 }:0b001000:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 2 }:{ 3 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 2 }, with id: { 0 }:0b010000:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 2 }:{ 3 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 2 }, with id: { 0 }:0b100000:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 2 }:{ 3 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 0 }:0b100000000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 0 }:{ 1 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle01", id: "{ 0 }:0b000010:{ 0 }:{ 2 }:{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 3 }, with id: { 0 }:0b000010:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 3 }:{ 4 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 3 }:{ 4 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 3 }, with id: { 0 }:0b001000:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 3 }:{ 4 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 3 }, with id: { 0 }:0b010000:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 3 }:{ 4 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 3 }, with id: { 0 }:0b100000:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 3 }:{ 4 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 0 }:0b100000000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 1 }:{ 2 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle02", id: "{ 0 }:0b000010:{ 0 }:{ 3 }:{ 4 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 4 }, with id: { 0 }:0b000010:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 4 }:{ 5 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 4 }:{ 5 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 4 }, with id: { 0 }:0b001000:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 4 }:{ 5 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 4 }, with id: { 0 }:0b010000:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 4 }:{ 5 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 4 }, with id: { 0 }:0b100000:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 4 }:{ 5 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 2 }, with id: { 0 }:0b100000000:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 2 }:{ 3 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle03", id: "{ 0 }:0b000010:{ 0 }:{ 4 }:{ 5 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 5 }, with id: { 0 }:0b000010:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 5 }:{ 6 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 5 }:{ 6 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 5 }, with id: { 0 }:0b001000:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 5 }:{ 6 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 5 }, with id: { 0 }:0b010000:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 5 }:{ 6 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 5 }, with id: { 0 }:0b100000:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 5 }:{ 6 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 3 }, with id: { 0 }:0b100000000:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 3 }:{ 4 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle04", id: "{ 0 }:0b000010:{ 0 }:{ 5 }:{ 6 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 6 }, with id: { 0 }:0b000010:{ 0 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 6 }:{ 7 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 6 }:{ 7 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 6 }, with id: { 0 }:0b001000:{ 0 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 6 }:{ 7 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 6 }, with id: { 0 }:0b010000:{ 0 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 6 }:{ 7 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 6 }, with id: { 0 }:0b100000:{ 0 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 6 }:{ 7 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 4 }, with id: { 0 }:0b100000000:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 4 }:{ 5 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle05", id: "{ 0 }:0b000010:{ 0 }:{ 6 }:{ 7 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 7 }, with id: { 0 }:0b000010:{ 0 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 7 }:{ 8 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 7 }:{ 8 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 7 }, with id: { 0 }:0b001000:{ 0 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 7 }:{ 8 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 7 }, with id: { 0 }:0b010000:{ 0 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 7 }:{ 8 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 7 }, with id: { 0 }:0b100000:{ 0 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 7 }:{ 8 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 5 }, with id: { 0 }:0b100000000:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 5 }:{ 6 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle06", id: "{ 0 }:0b000010:{ 0 }:{ 7 }:{ 8 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 8 }, with id: { 0 }:0b000010:{ 0 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 8 }:{ 9 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 8 }:{ 9 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 8 }, with id: { 0 }:0b001000:{ 0 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 8 }:{ 9 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 8 }, with id: { 0 }:0b010000:{ 0 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 8 }:{ 9 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 8 }, with id: { 0 }:0b100000:{ 0 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 8 }:{ 9 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 6 }, with id: { 0 }:0b100000000:{ 0 }:{ 6 }:{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 6 }:{ 7 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "handLight01", id: "{ 0 }:0b000010:{ 0 }:{ 8 }:{ 9 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 9 }, with id: { 0 }:0b000010:{ 0 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 9 }:{ 10 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 9 }:{ 10 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 9 }, with id: { 0 }:0b001000:{ 0 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 9 }:{ 10 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 9 }, with id: { 0 }:0b010000:{ 0 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 9 }:{ 10 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 9 }, with id: { 0 }:0b100000:{ 0 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 9 }:{ 10 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 7 }, with id: { 0 }:0b100000000:{ 0 }:{ 7 }:{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 7 }:{ 8 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "handLight02", id: "{ 0 }:0b000010:{ 0 }:{ 9 }:{ 10 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 10 }, with id: { 0 }:0b000010:{ 0 }:{ 10 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 10 }:{ 11 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 10 }:{ 11 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 10 }, with id: { 0 }:0b001000:{ 0 }:{ 10 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 10 }:{ 11 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 10 }, with id: { 0 }:0b010000:{ 0 }:{ 10 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 10 }:{ 11 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 10 }, with id: { 0 }:0b100000:{ 0 }:{ 10 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 10 }:{ 11 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "bikeLight", id: "{ 0 }:0b000010:{ 0 }:{ 10 }:{ 11 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 11 }, with id: { 0 }:0b000010:{ 0 }:{ 11 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 11 }:{ 12 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 11 }:{ 12 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 11 }, with id: { 0 }:0b001000:{ 0 }:{ 11 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 11 }:{ 12 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 11 }, with id: { 0 }:0b010000:{ 0 }:{ 11 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 11 }:{ 12 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 11 }, with id: { 0 }:0b100000:{ 0 }:{ 11 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 11 }:{ 12 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "icosphereSkybox_world", id: "{ 0 }:0b000010:{ 0 }:{ 11 }:{ 12 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 12 }, with id: { 0 }:0b000010:{ 0 }:{ 12 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 12 }:{ 13 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 12 }:{ 13 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 12 }, with id: { 0 }:0b001000:{ 0 }:{ 12 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 12 }:{ 13 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 12 }, with id: { 0 }:0b010000:{ 0 }:{ 12 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 12 }:{ 13 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 12 }, with id: { 0 }:0b100000:{ 0 }:{ 12 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 12 }:{ 13 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 8 }, with id: { 0 }:0b100000000:{ 0 }:{ 8 }:{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 8 }:{ 9 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "ground", id: "{ 0 }:0b000010:{ 0 }:{ 12 }:{ 13 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 13 }, with id: { 0 }:0b000010:{ 0 }:{ 13 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 13 }:{ 14 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 13 }:{ 14 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 13 }, with id: { 0 }:0b001000:{ 0 }:{ 13 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 13 }:{ 14 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 13 }, with id: { 0 }:0b010000:{ 0 }:{ 13 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 13 }:{ 14 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 13 }, with id: { 0 }:0b100000:{ 0 }:{ 13 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 13 }:{ 14 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 9 }, with id: { 0 }:0b100000000:{ 0 }:{ 9 }:{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 9 }:{ 10 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "ruins", id: "{ 0 }:0b000010:{ 0 }:{ 13 }:{ 14 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 14 }, with id: { 0 }:0b000010:{ 0 }:{ 14 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 14 }:{ 15 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 14 }:{ 15 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 14 }, with id: { 0 }:0b001000:{ 0 }:{ 14 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 14 }:{ 15 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 14 }, with id: { 0 }:0b010000:{ 0 }:{ 14 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 14 }:{ 15 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 14 }, with id: { 0 }:0b100000:{ 0 }:{ 14 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 14 }:{ 15 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 10 }, with id: { 0 }:0b100000000:{ 0 }:{ 10 }:{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 10 }:{ 11 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "carLeft", id: "{ 0 }:0b000010:{ 0 }:{ 14 }:{ 15 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 15 }, with id: { 0 }:0b000010:{ 0 }:{ 15 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 15 }:{ 16 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 15 }:{ 16 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 15 }, with id: { 0 }:0b001000:{ 0 }:{ 15 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 15 }:{ 16 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 15 }, with id: { 0 }:0b010000:{ 0 }:{ 15 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 15 }:{ 16 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 15 }, with id: { 0 }:0b100000:{ 0 }:{ 15 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 15 }:{ 16 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 11 }, with id: { 0 }:0b100000000:{ 0 }:{ 11 }:{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 11 }:{ 12 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "carRight", id: "{ 0 }:0b000010:{ 0 }:{ 15 }:{ 16 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 16 }, with id: { 0 }:0b000010:{ 0 }:{ 16 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 16 }:{ 17 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 16 }:{ 17 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 16 }, with id: { 0 }:0b001000:{ 0 }:{ 16 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 16 }:{ 17 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 16 }, with id: { 0 }:0b010000:{ 0 }:{ 16 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 16 }:{ 17 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 16 }, with id: { 0 }:0b100000:{ 0 }:{ 16 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 16 }:{ 17 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 12 }, with id: { 0 }:0b100000000:{ 0 }:{ 12 }:{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 12 }:{ 13 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "beetle", id: "{ 0 }:0b000010:{ 0 }:{ 16 }:{ 17 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 17 }, with id: { 0 }:0b000010:{ 0 }:{ 17 }:{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 17 }:{ 18 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 17 }:{ 18 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 17 }, with id: { 0 }:0b001000:{ 0 }:{ 17 }:{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 17 }:{ 18 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 17 }, with id: { 0 }:0b010000:{ 0 }:{ 17 }:{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 17 }:{ 18 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 17 }, with id: { 0 }:0b100000:{ 0 }:{ 17 }:{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 17 }:{ 18 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 13 }, with id: { 0 }:0b100000000:{ 0 }:{ 13 }:{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 13 }:{ 14 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "beetleGlass", id: "{ 0 }:0b000010:{ 0 }:{ 17 }:{ 18 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 18 }, with id: { 0 }:0b000010:{ 0 }:{ 18 }:{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 18 }:{ 19 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 18 }:{ 19 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 18 }, with id: { 0 }:0b001000:{ 0 }:{ 18 }:{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 18 }:{ 19 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 18 }, with id: { 0 }:0b010000:{ 0 }:{ 18 }:{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 18 }:{ 19 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 18 }, with id: { 0 }:0b100000:{ 0 }:{ 18 }:{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 18 }:{ 19 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 14 }, with id: { 0 }:0b100000000:{ 0 }:{ 14 }:{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 14 }:{ 15 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "bike", id: "{ 0 }:0b000010:{ 0 }:{ 18 }:{ 19 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 19 }, with id: { 0 }:0b000010:{ 0 }:{ 19 }:{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 19 }:{ 20 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 19 }:{ 20 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 19 }, with id: { 0 }:0b001000:{ 0 }:{ 19 }:{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 19 }:{ 20 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 19 }, with id: { 0 }:0b010000:{ 0 }:{ 19 }:{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 19 }:{ 20 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 19 }, with id: { 0 }:0b100000:{ 0 }:{ 19 }:{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 19 }:{ 20 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 15 }, with id: { 0 }:0b100000000:{ 0 }:{ 15 }:{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 15 }:{ 16 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "logo1", id: "{ 0 }:0b000010:{ 0 }:{ 19 }:{ 20 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 20 }, with id: { 0 }:0b000010:{ 0 }:{ 20 }:{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 20 }:{ 21 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 20 }:{ 21 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 20 }, with id: { 0 }:0b001000:{ 0 }:{ 20 }:{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 20 }:{ 21 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 20 }, with id: { 0 }:0b010000:{ 0 }:{ 20 }:{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 20 }:{ 21 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 20 }, with id: { 0 }:0b100000:{ 0 }:{ 20 }:{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 20 }:{ 21 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 16 }, with id: { 0 }:0b100000000:{ 0 }:{ 16 }:{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 16 }:{ 17 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "logo2", id: "{ 0 }:0b000010:{ 0 }:{ 20 }:{ 21 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 21 }, with id: { 0 }:0b000010:{ 0 }:{ 21 }:{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 21 }:{ 22 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 21 }:{ 22 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 21 }, with id: { 0 }:0b001000:{ 0 }:{ 21 }:{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 21 }:{ 22 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 21 }, with id: { 0 }:0b010000:{ 0 }:{ 21 }:{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 21 }:{ 22 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 21 }, with id: { 0 }:0b100000:{ 0 }:{ 21 }:{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 21 }:{ 22 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 17 }, with id: { 0 }:0b100000000:{ 0 }:{ 17 }:{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 17 }:{ 18 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "textLocomotion", id: "{ 0 }:0b000010:{ 0 }:{ 21 }:{ 22 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 22 }, with id: { 0 }:0b000010:{ 0 }:{ 22 }:{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 22 }:{ 23 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 22 }:{ 23 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 22 }, with id: { 0 }:0b001000:{ 0 }:{ 22 }:{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 22 }:{ 23 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 22 }, with id: { 0 }:0b010000:{ 0 }:{ 22 }:{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 22 }:{ 23 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 22 }, with id: { 0 }:0b100000:{ 0 }:{ 22 }:{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 22 }:{ 23 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 18 }, with id: { 0 }:0b100000000:{ 0 }:{ 18 }:{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 18 }:{ 19 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "textSudaBeam", id: "{ 0 }:0b000010:{ 0 }:{ 22 }:{ 23 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 23 }, with id: { 0 }:0b000010:{ 0 }:{ 23 }:{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 23 }:{ 24 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 23 }:{ 24 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 23 }, with id: { 0 }:0b001000:{ 0 }:{ 23 }:{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 23 }:{ 24 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 23 }, with id: { 0 }:0b010000:{ 0 }:{ 23 }:{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 23 }:{ 24 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 23 }, with id: { 0 }:0b100000:{ 0 }:{ 23 }:{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 23 }:{ 24 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 19 }, with id: { 0 }:0b100000000:{ 0 }:{ 19 }:{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 19 }:{ 20 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "textSeeControlsMd", id: "{ 0 }:0b000010:{ 0 }:{ 23 }:{ 24 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 24 }, with id: { 0 }:0b000010:{ 0 }:{ 24 }:{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 24 }:{ 25 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 24 }:{ 25 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 24 }, with id: { 0 }:0b001000:{ 0 }:{ 24 }:{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 24 }:{ 25 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 24 }, with id: { 0 }:0b010000:{ 0 }:{ 24 }:{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 24 }:{ 25 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 24 }, with id: { 0 }:0b100000:{ 0 }:{ 24 }:{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 24 }:{ 25 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 20 }, with id: { 0 }:0b100000000:{ 0 }:{ 20 }:{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 20 }:{ 21 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "cube", id: "{ 0 }:0b000010:{ 0 }:{ 24 }:{ 25 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 25 }, with id: { 0 }:0b000010:{ 0 }:{ 25 }:{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 25 }:{ 26 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 25 }:{ 26 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 25 }, with id: { 0 }:0b001000:{ 0 }:{ 25 }:{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 25 }:{ 26 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 25 }, with id: { 0 }:0b010000:{ 0 }:{ 25 }:{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 25 }:{ 26 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 25 }, with id: { 0 }:0b100000:{ 0 }:{ 25 }:{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 25 }:{ 26 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 21 }, with id: { 0 }:0b100000000:{ 0 }:{ 21 }:{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 21 }:{ 22 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "icosphereSmoothTripInstancing", id: "{ 0 }:0b000010:{ 0 }:{ 25 }:{ 26 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 26 }, with id: { 0 }:0b000010:{ 0 }:{ 26 }:{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 26 }:{ 27 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 26 }:{ 27 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 26 }, with id: { 0 }:0b001000:{ 0 }:{ 26 }:{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 26 }:{ 27 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 26 }, with id: { 0 }:0b010000:{ 0 }:{ 26 }:{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 26 }:{ 27 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 26 }, with id: { 0 }:0b100000:{ 0 }:{ 26 }:{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 26 }:{ 27 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 22 }, with id: { 0 }:0b100000000:{ 0 }:{ 22 }:{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 22 }:{ 23 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "icosphereSmoothForInstancing", id: "{ 0 }:0b000010:{ 0 }:{ 26 }:{ 27 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 27 }, with id: { 0 }:0b000010:{ 0 }:{ 27 }:{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 27 }:{ 28 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 27 }:{ 28 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 27 }, with id: { 0 }:0b001000:{ 0 }:{ 27 }:{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 27 }:{ 28 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 27 }, with id: { 0 }:0b010000:{ 0 }:{ 27 }:{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 27 }:{ 28 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 27 }, with id: { 0 }:0b100000:{ 0 }:{ 27 }:{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 27 }:{ 28 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 23 }, with id: { 0 }:0b100000000:{ 0 }:{ 23 }:{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 23 }:{ 24 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "sudaBeam01", id: "{ 0 }:0b000010:{ 0 }:{ 27 }:{ 28 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 28 }, with id: { 0 }:0b000010:{ 0 }:{ 28 }:{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 28 }:{ 29 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 28 }:{ 29 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 28 }, with id: { 0 }:0b001000:{ 0 }:{ 28 }:{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 28 }:{ 29 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 28 }, with id: { 0 }:0b010000:{ 0 }:{ 28 }:{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 28 }:{ 29 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 28 }, with id: { 0 }:0b100000:{ 0 }:{ 28 }:{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 28 }:{ 29 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 24 }, with id: { 0 }:0b100000000:{ 0 }:{ 24 }:{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 24 }:{ 25 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "sudaBeam02", id: "{ 0 }:0b000010:{ 0 }:{ 28 }:{ 29 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 29 }, with id: { 0 }:0b000010:{ 0 }:{ 29 }:{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 29 }:{ 30 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 29 }:{ 30 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 29 }, with id: { 0 }:0b001000:{ 0 }:{ 29 }:{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 29 }:{ 30 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 29 }, with id: { 0 }:0b010000:{ 0 }:{ 29 }:{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 29 }:{ 30 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 29 }, with id: { 0 }:0b100000:{ 0 }:{ 29 }:{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 29 }:{ 30 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 25 }, with id: { 0 }:0b100000000:{ 0 }:{ 25 }:{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 25 }:{ 26 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "squid", id: "{ 0 }:0b000010:{ 0 }:{ 29 }:{ 30 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 30 }, with id: { 0 }:0b000010:{ 0 }:{ 30 }:{ 31 }, validSize: { 31 }, currentVersion: { 31 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 30 }:{ 31 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 30 }:{ 31 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 30 }, with id: { 0 }:0b001000:{ 0 }:{ 30 }:{ 31 }, validSize: { 31 }, currentVersion: { 31 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 30 }:{ 31 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 30 }, with id: { 0 }:0b010000:{ 0 }:{ 30 }:{ 31 }, validSize: { 31 }, currentVersion: { 31 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 30 }:{ 31 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 30 }, with id: { 0 }:0b100000:{ 0 }:{ 30 }:{ 31 }, validSize: { 31 }, currentVersion: { 31 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 30 }:{ 31 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 26 }, with id: { 0 }:0b100000000:{ 0 }:{ 26 }:{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 26 }:{ 27 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "monke", id: "{ 0 }:0b000010:{ 0 }:{ 30 }:{ 31 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 31 }, with id: { 0 }:0b000010:{ 0 }:{ 31 }:{ 32 }, validSize: { 32 }, currentVersion: { 32 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 31 }:{ 32 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 31 }:{ 32 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 31 }, with id: { 0 }:0b001000:{ 0 }:{ 31 }:{ 32 }, validSize: { 32 }, currentVersion: { 32 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 31 }:{ 32 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 31 }, with id: { 0 }:0b010000:{ 0 }:{ 31 }:{ 32 }, validSize: { 32 }, currentVersion: { 32 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 31 }:{ 32 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 31 }, with id: { 0 }:0b100000:{ 0 }:{ 31 }:{ 32 }, validSize: { 32 }, currentVersion: { 32 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 31 }:{ 32 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 27 }, with id: { 0 }:0b100000000:{ 0 }:{ 27 }:{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 27 }:{ 28 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "monkeEye1", id: "{ 0 }:0b000010:{ 0 }:{ 31 }:{ 32 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 32 }, with id: { 0 }:0b000010:{ 0 }:{ 32 }:{ 33 }, validSize: { 33 }, currentVersion: { 33 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 0 }:0b000010:{ 0 }:{ 32 }:{ 33 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 0 }:0b000010:{ 0 }:{ 32 }:{ 33 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 32 }, with id: { 0 }:0b001000:{ 0 }:{ 32 }:{ 33 }, validSize: { 33 }, currentVersion: { 33 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 0 }:0b001000:{ 0 }:{ 32 }:{ 33 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 32 }, with id: { 0 }:0b010000:{ 0 }:{ 32 }:{ 33 }, validSize: { 33 }, currentVersion: { 33 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 0 }:0b010000:{ 0 }:{ 32 }:{ 33 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 32 }, with id: { 0 }:0b100000:{ 0 }:{ 32 }:{ 33 }, validSize: { 33 }, currentVersion: { 33 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 0 }:0b100000:{ 0 }:{ 32 }:{ 33 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 28 }, with id: { 0 }:0b100000000:{ 0 }:{ 28 }:{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 0 }:0b100000000:{ 0 }:{ 28 }:{ 29 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "monkeEye2", id: "{ 0 }:0b000010:{ 0 }:{ 32 }:{ 33 }", is std::type_index(typeid(GameEntityObject)): true.

[Game][GameData][LoadVFXEntityObjects]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadVFXEntityObjects]		 Loading Game VFX Objects (vfxEntityObjectsWorld)

[GameDataPool][Constructed<GAME_ENTITY_OBJECTS>] maxPossiblePoolSize: "{ 6 }", world: { 1 }, typeUID: "{ 2 }_GAME_ENTITY_OBJECTS", firstEmptyIndex: { 0 }, T: struct Game::GameEntityObject, tiles: { 1 }, tileSize: { 128 }, items.size(): { 1 }

[GameDataPool][Constructed<TRANSFORM_COMPONENTS>] maxPossiblePoolSize: "{ 6 }", world: { 1 }, typeUID: "{ 8 }_TRANSFORM_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Transform, tiles: { 1 }, tileSize: { 128 }, items.size(): { 1 }

[GameDataPool][Constructed<PARENT_COMPONENTS>] maxPossiblePoolSize: "{ 6 }", world: { 1 }, typeUID: "{ 16 }_PARENT_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Parent, tiles: { 1 }, tileSize: { 128 }, items.size(): { 1 }

[GameDataPool][Constructed<CHILDREN_COMPONENTS>] maxPossiblePoolSize: "{ 6 }", world: { 1 }, typeUID: "{ 32 }_CHILDREN_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Children, tiles: { 1 }, tileSize: { 128 }, items.size(): { 1 }

[GameDataPool][Constructed<BOUNDS_COMPONENTS>] maxPossiblePoolSize: "{ 2 }", world: { 1 }, typeUID: "{ 256 }_BOUNDS_COMPONENTS", firstEmptyIndex: { 0 }, T: struct Game::Bounds, tiles: { 1 }, tileSize: { 128 }, items.size(): { 1 }
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 0 }, with id: { 1 }:0b000010:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 1 }:0b000010:{ 0 }:{ 0 }:{ 1 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 1 }:0b000010:{ 0 }:{ 0 }:{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 1 }:0b001000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 1 }:0b001000:{ 0 }:{ 0 }:{ 1 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 1 }:0b010000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 1 }:0b010000:{ 0 }:{ 0 }:{ 1 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 1 }:0b100000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 1 }:0b100000:{ 0 }:{ 0 }:{ 1 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 1 }:0b000010:{ 0 }:{ 0 }:{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 1 }, with id: { 1 }:0b000010:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 1 }:0b000010:{ 0 }:{ 1 }:{ 2 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 1 }:0b000010:{ 0 }:{ 1 }:{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 1 }:0b001000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 1 }:0b001000:{ 0 }:{ 1 }:{ 2 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 1 }:0b010000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 1 }:0b010000:{ 0 }:{ 1 }:{ 2 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 1 }:0b100000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 1 }:0b100000:{ 0 }:{ 1 }:{ 2 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "icosphereSkybox_chaperone", id: "{ 1 }:0b000010:{ 0 }:{ 1 }:{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 2 }, with id: { 1 }:0b000010:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 1 }:0b000010:{ 0 }:{ 2 }:{ 3 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 1 }:0b000010:{ 0 }:{ 2 }:{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 2 }, with id: { 1 }:0b001000:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 1 }:0b001000:{ 0 }:{ 2 }:{ 3 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 2 }, with id: { 1 }:0b010000:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 1 }:0b010000:{ 0 }:{ 2 }:{ 3 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 2 }, with id: { 1 }:0b100000:{ 0 }:{ 2 }:{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 1 }:0b100000:{ 0 }:{ 2 }:{ 3 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "floorGrid", id: "{ 1 }:0b000010:{ 0 }:{ 2 }:{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 3 }, with id: { 1 }:0b000010:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 1 }:0b000010:{ 0 }:{ 3 }:{ 4 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 1 }:0b000010:{ 0 }:{ 3 }:{ 4 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 3 }, with id: { 1 }:0b001000:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 1 }:0b001000:{ 0 }:{ 3 }:{ 4 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 3 }, with id: { 1 }:0b010000:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 1 }:0b010000:{ 0 }:{ 3 }:{ 4 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 3 }, with id: { 1 }:0b100000:{ 0 }:{ 3 }:{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 1 }:0b100000:{ 0 }:{ 3 }:{ 4 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "ceilingGrid", id: "{ 1 }:0b000010:{ 0 }:{ 3 }:{ 4 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 4 }, with id: { 1 }:0b000010:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 1 }:0b000010:{ 0 }:{ 4 }:{ 5 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 1 }:0b000010:{ 0 }:{ 4 }:{ 5 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 4 }, with id: { 1 }:0b001000:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 1 }:0b001000:{ 0 }:{ 4 }:{ 5 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 4 }, with id: { 1 }:0b010000:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 1 }:0b010000:{ 0 }:{ 4 }:{ 5 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 4 }, with id: { 1 }:0b100000:{ 0 }:{ 4 }:{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 1 }:0b100000:{ 0 }:{ 4 }:{ 5 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 0 }, with id: { 1 }:0b100000000:{ 0 }:{ 0 }:{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 1 }:0b100000000:{ 0 }:{ 0 }:{ 1 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "handLeft", id: "{ 1 }:0b000010:{ 0 }:{ 4 }:{ 5 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<GAME_ENTITY_OBJECTS>]	 Found free item at index: { 5 }, with id: { 1 }:0b000010:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<GAME_ENTITY_OBJECTS>]	 { 1 }:0b000010:{ 0 }:{ 5 }:{ 6 }
[Game][GameData][GameEntityObject]	 Using: {name: "NO_NAME_GAME_ENTITY_OBJECT", id: "{ 1 }:0b000010:{ 0 }:{ 5 }:{ 6 }", is std::type_index(typeid(GameEntityObject)): true.
[GameDataPool][GetFirstFree<TRANSFORM_COMPONENTS>]	 Found free item at index: { 5 }, with id: { 1 }:0b001000:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<TRANSFORM_COMPONENTS>]	 { 1 }:0b001000:{ 0 }:{ 5 }:{ 6 }
[GameDataPool][GetFirstFree<PARENT_COMPONENTS>]	 Found free item at index: { 5 }, with id: { 1 }:0b010000:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<PARENT_COMPONENTS>]	 { 1 }:0b010000:{ 0 }:{ 5 }:{ 6 }
[GameDataPool][GetFirstFree<CHILDREN_COMPONENTS>]	 Found free item at index: { 5 }, with id: { 1 }:0b100000:{ 0 }:{ 5 }:{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<CHILDREN_COMPONENTS>]	 { 1 }:0b100000:{ 0 }:{ 5 }:{ 6 }
[GameDataPool][GetFirstFree<BOUNDS_COMPONENTS>]	 Found free item at index: { 1 }, with id: { 1 }:0b100000000:{ 0 }:{ 1 }:{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<BOUNDS_COMPONENTS>]	 { 1 }:0b100000000:{ 0 }:{ 1 }:{ 2 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "handRight", id: "{ 1 }:0b000010:{ 0 }:{ 5 }:{ 6 }", is std::type_index(typeid(GameEntityObject)): true.

[Game][GameData][LoadPlayers]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadPlayers]		 Loading Players
[Game][GameData][LoadGameWorlds]		.........................................................................................................................
[Game][GameData][LoadGameWorlds]		 Loaded Game World(s).
[Scripting][SceneSetup] Scripted and scene objects setup. ~~~~~~~~~~~~~~~~~~~ 

~~~~[Scripting] setting ground size: 
~~~~[Scripting] setting floorGrid. 
~~~~[Scripting] setting ceilingGrid. 
[Scripting][SceneSetup] Done. ~~~~~~~~~~~~~~~~~~~ 


[Game][Renderer][SetUpRenderProcesses]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][Renderer][SetUpRenderProcesses]	 Setting up circular buffer of descriptor set pipeline data.

[Game][Renderer][SetUpRenderProcesses] maxPossibleNumEntities: { 106 }; maxPossibleNumMaterials: { 54 }
[RenderProcess][framesInFlight: { 2 }] Binded (bound) Descriptor Sets: total size for vertex & fragment data (and both static and dynamic data)
	aka uniformBufferSize: { 21696 };
	sizeof(StaticVertexUniformData): { 524 };
	sizeof(StaticFragmentUniformData): { 720 };
	sizeof(DynamicVertexUniformData): { 100 };
	sizeof(DynamicFragmentUniformData): { 48 };
	gameObjectCount: { 106 };
[RenderProcess] Finished Update Render process / descriptor sets.
[RenderProcess][framesInFlight: { 2 }] Binded (bound) Descriptor Sets: total size for vertex & fragment data (and both static and dynamic data)
	aka uniformBufferSize: { 21696 };
	sizeof(StaticVertexUniformData): { 524 };
	sizeof(StaticFragmentUniformData): { 720 };
	sizeof(DynamicVertexUniformData): { 100 };
	sizeof(DynamicFragmentUniformData): { 48 };
	gameObjectCount: { 106 };
[RenderProcess] Finished Update Render process / descriptor sets.
[Renderer] meshDataTotalSize: { 46632528 }
[Game][Renderer][SetUpRenderProcesses]	 done.
[Game][Renderer][SetUpRenderProcesses]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[Game][MirrorView][Connect]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][MirrorView][Connect]	 setting up game window
[Game][MirrorView][Connect]		 done.
[Game][MirrorView][Connect]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[Game][Main]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][Main]		 Starting Game Loop

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

[Game][Main]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][Main]		 Game Loop ended. Cleaning up.

[Game][GameData][UnLoadGameWorlds]                               .........................................................................................................................
[Game][GameData][UnLoadGameWorlds]       					Unloading Game World(s).
[Game][GameData][UnLoadGameWorlds]       Unloading entities and components, unhooking events, clearing any maps:
[GameDataPool][ClearItems<GAME_ENTITY_OBJECTS>]  Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<GAME_ENTITY_OBJECTS>]  Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<GAME_ENTITY_OBJECTS>] and all its heap items.
[~GameDataPool][Destructed<GAME_ENTITY_OBJECTS>] and all its heap items.

[GameDataPool][ClearItems<GAME_ENTITY_OBJECTS>]  Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<GAME_ENTITY_OBJECTS>]  Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<GAME_ENTITY_OBJECTS>] and all its heap items.
[~GameDataPool][Destructed<GAME_ENTITY_OBJECTS>] and all its heap items.

[GameDataPool][ClearItems<TRANSFORM_COMPONENTS>]         Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<TRANSFORM_COMPONENTS>]         Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<TRANSFORM_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<TRANSFORM_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<PARENT_COMPONENTS>]    Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<PARENT_COMPONENTS>]    Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<PARENT_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<PARENT_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<CHILDREN_COMPONENTS>]  Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<CHILDREN_COMPONENTS>]  Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<CHILDREN_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<CHILDREN_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<MODEL_COMPONENTS>]     Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<MODEL_COMPONENTS>]     Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<MODEL_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<MODEL_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<BOUNDS_COMPONENTS>]    Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<BOUNDS_COMPONENTS>]    Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<BOUNDS_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<BOUNDS_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 8 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 9 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 10 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 11 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 12 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 13 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 14 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 15 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 16 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 17 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 18 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 19 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 20 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 21 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 22 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 23 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 24 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 25 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 26 }:{ 0 }.
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Delete item only: already marked as cleared/unused in pool: { 0 }:0b1000000000:{ 0 }:{ 27 }:{ 0 }.
[~GameDataPool][Destructing<MATERIAL_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<MATERIAL_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<LIGHT_COMPONENTS>]     Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<LIGHT_COMPONENTS>]     Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<LIGHT_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<LIGHT_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<TRANSFORM_COMPONENTS>]         Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<TRANSFORM_COMPONENTS>]         Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<TRANSFORM_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<TRANSFORM_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<PARENT_COMPONENTS>]    Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<PARENT_COMPONENTS>]    Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<PARENT_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<PARENT_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<CHILDREN_COMPONENTS>]  Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<CHILDREN_COMPONENTS>]  Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<CHILDREN_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<CHILDREN_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<BOUNDS_COMPONENTS>]    Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<BOUNDS_COMPONENTS>]    Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<BOUNDS_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<BOUNDS_COMPONENTS>] and all its heap items.

[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<MATERIAL_COMPONENTS>]  Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<MATERIAL_COMPONENTS>] and all its heap items.
[~GameDataPool][Destructed<MATERIAL_COMPONENTS>] and all its heap items.

[Game][GameData][UnLoadGameWorlds]                               .........................................................................................................................
[Game][GameData][UnLoadGameWorlds]                               Unloaded Game World(s).

[Game][GameData][~GameData]                              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~       
[Game][GameData][~GameData]      Deleting Game Data: players, entity pools, component pools, worlds. These all should have been unloaded already with the world(s).
[Game][GameData][GameData]       Deleted Players.
[Game][GameData][GameData]       Deleted Entity Pools.
[Game][GameData][GameData]       Deleted Component Pools.
[Game][GameData][GameData]       Deleted Worlds.
[Game][~GameData][GameData]      Deleted Game Data.

[Game][Main][EXIT_SUCCESS]                               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
```
