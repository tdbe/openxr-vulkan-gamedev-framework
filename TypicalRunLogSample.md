What a typical run log looks like, with `DEBUG` and `DEBUG_VERBOSE` turned on. Game world load, setup, updates & render loops, unload and exit.
```
[Game][Main][Starting]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[Game][Main][Starting]		 DEBUG flag enabled from CMakeLists.txt. For regular notification log messages for the Debug build.

[Game][Main][Starting]		 DEBUG_VERBOSE flag enabled from CMakeLists.txt. For messages triggered by objects/entities that might spam a lot, e.g. get pool item, parent/children changed, or item cleared.

[Game][Main][Starting]		 DEBUG_THREADS flag enabled from CMakeLists.txt. For messages printing the state of jobs / threads / taskflow graphs.



[Context][createDevice]	~~~~~~~~~~~~~~~~~~~
[Context][createDevice]	 DeviceName: Intel(R) Iris(R) Xe Graphics; DeviceType: { 1 }; MaxViewports: { 16 }; MaxViewportDimensions[0]: { 32768 }; MaxViewportDimensions[1]: { 32768 }
[Game][Main]		 [OO] XR System Name: AetherVR System. Note you can change your active xr system via each platform's apps' settings (e.g. steam or oculus).
[Game][GameData][Singleton]	 This is the source of all data pools. Singleton instanceId: "GameData_{ 0 }".

[Game][GameData][LoadGameWorlds]	.....................................................................................................................................
[Game][GameData][LoadGameWorlds]				 Loading Game World(s):
[Game][GameData][LoadGameWorlds]	 Loading, deserializing, creating pools for entities and components, hooking some events, creating some quick access maps:

[Game][GameData][LoadModels]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadModels]		 Loading Models

[GameDataPool][Constructed<struct Game::Model>] maxPossiblePoolSize: "{ 32 }", world: { 0 }, typeUID: "{ 64 }_struct Game::Model", firstEmptyIndex: { 0 }, T: struct Game::Model, tiles: { 1 }, tileSize: { 32 }, items.size(): { 1 }
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 0 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[MeshData] LoadModel: models/quad.obj; total meshData size so far: { 288 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 1 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[MeshData] LoadModel: models/ground_displaced_4096.obj; total meshData size so far: { 590112 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 2 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[MeshData] LoadModel: models/Ruins.obj; total meshData size so far: { 17245728 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 3 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[MeshData] LoadModel: models/Car.obj; total meshData size so far: { 18525888 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 4 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[MeshData] LoadModel: models/Beetle_glassless.obj; total meshData size so far: { 24642720 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 5 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[MeshData] LoadModel: models/Beetle_glass_only.obj; total meshData size so far: { 24903360 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 6 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }
[MeshData] LoadModel: models/Bike.obj; total meshData size so far: { 40369824 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 7 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }
[MeshData] LoadModel: models/Hand.obj; total meshData size so far: { 40708368 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 8 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }
[MeshData] LoadModel: models/cube.obj; total meshData size so far: { 40710096 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 9 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }
[MeshData] LoadModel: models/Logo_OpenXR_Vulkan.obj; total meshData size so far: { 41134032 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 10 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }
[MeshData] LoadModel: models/Logo_Framework.obj; total meshData size so far: { 41486544 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 11 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }
[MeshData] LoadModel: models/Text_Locomotion_Flat.obj; total meshData size so far: { 41797872 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 12 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }
[MeshData] LoadModel: models/Text_Suda_Beam_Flat.obj; total meshData size so far: { 42086448 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 13 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }
[MeshData] LoadModel: models/Text_See_Controls_md.obj; total meshData size so far: { 42286032 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 14 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }
[MeshData] LoadModel: models/icosphere_subdiv4_half_smooth.obj; total meshData size so far: { 42470352 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 15 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }
[MeshData] LoadModel: models/icosphere_subdiv4_smooth.obj; total meshData size so far: { 42654672 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 16 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }
[MeshData] LoadModel: models/icosphere_subdiv3_0.75_smooth.obj; total meshData size so far: { 42700752 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 17 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }
[MeshData] LoadModel: models/tube_light_1_03.obj; total meshData size so far: { 42880464 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 18 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }
[MeshData] LoadModel: models/SudaBeam.obj; total meshData size so far: { 43348752 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 19 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }
[MeshData] LoadModel: models/Squid_Happy_Grumpy.obj; total meshData size so far: { 43747344 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }", is std::type_index(typeid(Model)): true.
[GameDataPool][GetFirstFree<struct Game::Model>]	 Found free item at index: { 20 }, with id: world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[GameDataPool][GetFreeItem<struct Game::Model>]	 world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }
[MeshData] LoadModel: models/SuzanneHighQuality20k.obj; total meshData size so far: { 46632528 }
[Game][GameData][LoadGameWorlds][Component][Model]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }", is std::type_index(typeid(Model)): true.

[Game][GameData][LoadMaterials]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadMaterials]		 Loading Materials

[GameDataPool][Constructed<struct Game::Material>] maxPossiblePoolSize: "{ 50 }", world: { 0 }, typeUID: "{ 256 }_struct Game::Material", firstEmptyIndex: { 0 }, T: struct Game::Material, tiles: { 1 }, tileSize: { 50 }, items.size(): { 1 }

[GameDataPool][Constructed<struct Game::Material>] maxPossiblePoolSize: "{ 4 }", world: { 1 }, typeUID: "{ 256 }_struct Game::Material", firstEmptyIndex: { 0 }, T: struct Game::Material, tiles: { 1 }, tileSize: { 4 }, items.size(): { 1 }
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 0 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 1 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 2 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 3 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 4 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 5 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 6 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 7 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 28 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 28 }:version_{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 28 }:version_{ 9 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 28 }:version_{ 9 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 29 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 29 }:version_{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 29 }:version_{ 10 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 29 }:version_{ 10 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 30 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 30 }:version_{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 30 }:version_{ 11 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 30 }:version_{ 11 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 31 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 31 }:version_{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 31 }:version_{ 12 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 31 }:version_{ 12 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 32 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 32 }:version_{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 32 }:version_{ 13 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 32 }:version_{ 13 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 33 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 33 }:version_{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 33 }:version_{ 14 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 33 }:version_{ 14 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 34 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 34 }:version_{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 34 }:version_{ 15 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 34 }:version_{ 15 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 35 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 35 }:version_{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 35 }:version_{ 16 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 35 }:version_{ 16 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 36 }, with id: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 36 }:version_{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 36 }:version_{ 17 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 36 }:version_{ 17 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 0 }, with id: world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 1 }, with id: world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 2 }, with id: world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }", is std::type_index(typeid(Material)): true.
[GameDataPool][GetFirstFree<struct Game::Material>]	 Found free item at index: { 3 }, with id: world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<struct Game::Material>]	 world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[Game][GameData][LoadGameWorlds][Component][Material]	 Configured component with id: "world_{ 1 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }", is std::type_index(typeid(Material)): true.

[Game][GameData][LoadLights]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadLights]		 Loading Lights

[GameDataPool][Constructed<struct Game::Light>] maxPossiblePoolSize: "{ 10 }", world: { 0 }, typeUID: "{ 512 }_struct Game::Light", firstEmptyIndex: { 0 }, T: struct Game::Light, tiles: { 1 }, tileSize: { 10 }, items.size(): { 1 }
[GameDataPool][GetFirstFree<struct Game::Light>]	 Found free item at index: { 0 }, with id: world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[GameDataPool][GetFreeItem<struct Game::Light>]	 world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<struct Game::Light>]	 Found free item at index: { 1 }, with id: world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[GameDataPool][GetFreeItem<struct Game::Light>]	 world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<struct Game::Light>]	 Found free item at index: { 2 }, with id: world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[GameDataPool][GetFreeItem<struct Game::Light>]	 world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<struct Game::Light>]	 Found free item at index: { 3 }, with id: world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[GameDataPool][GetFreeItem<struct Game::Light>]	 world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<struct Game::Light>]	 Found free item at index: { 4 }, with id: world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[GameDataPool][GetFreeItem<struct Game::Light>]	 world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<struct Game::Light>]	 Found free item at index: { 5 }, with id: world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[GameDataPool][GetFreeItem<struct Game::Light>]	 world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<struct Game::Light>]	 Found free item at index: { 6 }, with id: world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[GameDataPool][GetFreeItem<struct Game::Light>]	 world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<struct Game::Light>]	 Found free item at index: { 7 }, with id: world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[GameDataPool][GetFreeItem<struct Game::Light>]	 world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<struct Game::Light>]	 Found free item at index: { 8 }, with id: world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[GameDataPool][GetFreeItem<struct Game::Light>]	 world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }", is std::type_index(typeid(Light)): true.
[GameDataPool][GetFirstFree<struct Game::Light>]	 Found free item at index: { 9 }, with id: world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[GameDataPool][GetFreeItem<struct Game::Light>]	 world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }
[Game][GameData][LoadGameWorlds][Component][Light]	 Configured component with id: "world_{ 0 }:type_{ 0b1000000000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }", is std::type_index(typeid(Light)): true.

[Game][GameData][LoadGameEntityObjects]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadGameEntityObjects]		 Loading Game Entity Objects (main entityObjectsWorld)
[ArchetypedGameDataPool][SubpoolTiledVector] Default Constructed.
[ArchetypedGameDataPool][SubpoolTiledVector] Default Constructed.
[ArchetypedGameDataPool][SubpoolTiledVector] Default Constructed.
[ArchetypedGameDataPool][SubpoolTiledVector] Default Constructed.
[ArchetypedGameDataPool][SubpoolTiledVector] Default Constructed.

[ArchetypedGameDataPool]	----------------------------------------------------
[ArchetypedGameDataPool]	 Constructing an Archetyped Pool - it's a variadic archetype of { 5 } subpools.
[ArchetypedGameDataPool][SubpoolTiledVector] Initialized. maxPossiblePoolSize: { 100 }, tileSize: { 128 }, typeUID: { 2 }, topTypeStr: struct Game::GameEntityObject, worldIndex: { 0 }
[ArchetypedGameDataPool][SubpoolTiledVector] Initialized. maxPossiblePoolSize: { 100 }, tileSize: { 128 }, typeUID: { 4 }, topTypeStr: struct Game::Transform, worldIndex: { 0 }
[ArchetypedGameDataPool][SubpoolTiledVector] Initialized. maxPossiblePoolSize: { 100 }, tileSize: { 128 }, typeUID: { 8 }, topTypeStr: struct Game::Parent, worldIndex: { 0 }
[ArchetypedGameDataPool][SubpoolTiledVector] Initialized. maxPossiblePoolSize: { 100 }, tileSize: { 128 }, typeUID: { 16 }, topTypeStr: struct Game::Children, worldIndex: { 0 }
[ArchetypedGameDataPool][SubpoolTiledVector] Initialized. maxPossiblePoolSize: { 100 }, tileSize: { 128 }, typeUID: { 128 }, topTypeStr: struct Game::Bounds, worldIndex: { 0 }

[ArchetypedGameDataPool][Constructed a SubpoolTiledVector<struct Game::GameEntityObject>] T: struct Game::GameEntityObject, maxPossiblePoolSize: { 100 }, world: { 0 }, typeUID: { 2 }_struct Game::GameEntityObject, firstEmptyIndex: { 0 }, tiles: { 1 }, tileSize: { 128 }, subpool.items.size(): { 1 }

[ArchetypedGameDataPool][Constructed a SubpoolTiledVector<struct Game::Transform>] T: struct Game::Transform, maxPossiblePoolSize: { 100 }, world: { 0 }, typeUID: { 4 }_struct Game::Transform, firstEmptyIndex: { 0 }, tiles: { 1 }, tileSize: { 128 }, subpool.items.size(): { 1 }

[ArchetypedGameDataPool][Constructed a SubpoolTiledVector<struct Game::Parent>] T: struct Game::Parent, maxPossiblePoolSize: { 100 }, world: { 0 }, typeUID: { 8 }_struct Game::Parent, firstEmptyIndex: { 0 }, tiles: { 1 }, tileSize: { 128 }, subpool.items.size(): { 1 }

[ArchetypedGameDataPool][Constructed a SubpoolTiledVector<struct Game::Children>] T: struct Game::Children, maxPossiblePoolSize: { 100 }, world: { 0 }, typeUID: { 16 }_struct Game::Children, firstEmptyIndex: { 0 }, tiles: { 1 }, tileSize: { 128 }, subpool.items.size(): { 1 }

[ArchetypedGameDataPool][Constructed a SubpoolTiledVector<struct Game::Bounds>] T: struct Game::Bounds, maxPossiblePoolSize: { 100 }, world: { 0 }, typeUID: { 128 }_struct Game::Bounds, firstEmptyIndex: { 0 }, tiles: { 1 }, tileSize: { 128 }, subpool.items.size(): { 1 }
[ArchetypedGameDataPool]	 Constructed Archetyped Pool 0b10011110 and all its subpools and heap items.

[ArchetypedGameDataPool]	----------------------------------------------------

[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 0 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 0 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 0 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 0 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "worldRoot", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 1 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 1 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 1 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 1 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "mainDirectionalLight", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 2 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 2 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 2 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 2 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 0 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle01", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 3 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 3 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 3 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 3 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 1 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle02", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 4 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 4 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 4 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 4 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 2 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle03", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 5 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 5 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 5 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 5 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 3 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle04", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 6 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 6 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 6 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 6 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 4 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle05", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 7 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 7 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 7 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 7 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 5 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "tentacle06", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 8 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 8 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 8 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 8 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 6 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }, validSize: { 7 }, currentVersion: { 7 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 6 }:version_{ 7 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "handLight01", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 9 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 9 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 9 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 9 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 7 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }, validSize: { 8 }, currentVersion: { 8 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 7 }:version_{ 8 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "handLight02", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 10 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 10 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 10 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 10 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "bikeLight", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 11 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 11 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 11 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 11 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "icosphereSkybox_world", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 12 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 12 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 12 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 12 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 8 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }, validSize: { 9 }, currentVersion: { 9 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 8 }:version_{ 9 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "ground", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 13 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 13 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 13 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 13 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 9 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }, validSize: { 10 }, currentVersion: { 10 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 9 }:version_{ 10 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "ruins", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 14 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 14 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 14 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 14 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 10 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }, validSize: { 11 }, currentVersion: { 11 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 10 }:version_{ 11 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "carLeft", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 15 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 15 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 15 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 15 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 11 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }, validSize: { 12 }, currentVersion: { 12 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 11 }:version_{ 12 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "carRight", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 16 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 16 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 16 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 16 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 12 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }, validSize: { 13 }, currentVersion: { 13 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 12 }:version_{ 13 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "beetle", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 17 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 17 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 17 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 17 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 13 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }, validSize: { 14 }, currentVersion: { 14 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 13 }:version_{ 14 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "beetleGlass", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 18 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 18 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 18 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 18 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 14 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }, validSize: { 15 }, currentVersion: { 15 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 14 }:version_{ 15 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "bike", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 19 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 19 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 19 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 19 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 15 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }, validSize: { 16 }, currentVersion: { 16 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 15 }:version_{ 16 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "logo1", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 20 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 20 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 20 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 20 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 16 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }, validSize: { 17 }, currentVersion: { 17 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 16 }:version_{ 17 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "logo2", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 21 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 21 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 21 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 21 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 17 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }, validSize: { 18 }, currentVersion: { 18 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 17 }:version_{ 18 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "textLocomotion", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 22 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 22 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 22 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 22 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 18 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }, validSize: { 19 }, currentVersion: { 19 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 18 }:version_{ 19 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "textSudaBeam", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 23 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 23 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 23 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 23 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 19 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }, validSize: { 20 }, currentVersion: { 20 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 19 }:version_{ 20 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "textSeeControlsMd", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 24 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 24 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 24 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 24 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 20 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }, validSize: { 21 }, currentVersion: { 21 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 20 }:version_{ 21 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "cube", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 25 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 25 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 25 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 25 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 21 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }, validSize: { 22 }, currentVersion: { 22 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 21 }:version_{ 22 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "icosphereSmoothTripInstancing", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 26 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 26 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 26 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 26 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 22 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }, validSize: { 23 }, currentVersion: { 23 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 22 }:version_{ 23 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "icosphereSmoothForInstancing", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 27 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 27 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 27 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 27 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 23 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }, validSize: { 24 }, currentVersion: { 24 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 23 }:version_{ 24 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "sudaBeam01", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 28 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 28 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 28 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 28 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 24 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }, validSize: { 25 }, currentVersion: { 25 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 24 }:version_{ 25 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "sudaBeam02", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 29 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 29 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 29 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 29 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 25 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }, validSize: { 26 }, currentVersion: { 26 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 25 }:version_{ 26 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "squid", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 30 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 30 }:version_{ 31 }, validSize: { 31 }, currentVersion: { 31 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 30 }:version_{ 31 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 30 }:version_{ 31 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 30 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 30 }:version_{ 31 }, validSize: { 31 }, currentVersion: { 31 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 30 }:version_{ 31 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 30 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 30 }:version_{ 31 }, validSize: { 31 }, currentVersion: { 31 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 30 }:version_{ 31 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 30 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 30 }:version_{ 31 }, validSize: { 31 }, currentVersion: { 31 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 30 }:version_{ 31 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 26 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }, validSize: { 27 }, currentVersion: { 27 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 26 }:version_{ 27 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "testSquid", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 30 }:version_{ 31 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 31 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 31 }:version_{ 32 }, validSize: { 32 }, currentVersion: { 32 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 31 }:version_{ 32 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 31 }:version_{ 32 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 31 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 31 }:version_{ 32 }, validSize: { 32 }, currentVersion: { 32 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 31 }:version_{ 32 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 31 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 31 }:version_{ 32 }, validSize: { 32 }, currentVersion: { 32 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 31 }:version_{ 32 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 31 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 31 }:version_{ 32 }, validSize: { 32 }, currentVersion: { 32 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 31 }:version_{ 32 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 27 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }, validSize: { 28 }, currentVersion: { 28 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 27 }:version_{ 28 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "monke", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 31 }:version_{ 32 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 32 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 32 }:version_{ 33 }, validSize: { 33 }, currentVersion: { 33 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 32 }:version_{ 33 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 32 }:version_{ 33 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 32 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 32 }:version_{ 33 }, validSize: { 33 }, currentVersion: { 33 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 32 }:version_{ 33 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 32 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 32 }:version_{ 33 }, validSize: { 33 }, currentVersion: { 33 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 32 }:version_{ 33 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 32 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 32 }:version_{ 33 }, validSize: { 33 }, currentVersion: { 33 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 32 }:version_{ 33 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 28 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }, validSize: { 29 }, currentVersion: { 29 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 28 }:version_{ 29 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "monkeEye1", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 32 }:version_{ 33 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 33 }, with id: world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 33 }:version_{ 34 }, validSize: { 34 }, currentVersion: { 34 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 33 }:version_{ 34 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 33 }:version_{ 34 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 33 }, with id: world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 33 }:version_{ 34 }, validSize: { 34 }, currentVersion: { 34 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 33 }:version_{ 34 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 33 }, with id: world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 33 }:version_{ 34 }, validSize: { 34 }, currentVersion: { 34 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 33 }:version_{ 34 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 33 }, with id: world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 33 }:version_{ 34 }, validSize: { 34 }, currentVersion: { 34 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 33 }:version_{ 34 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 29 }, with id: world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }, validSize: { 30 }, currentVersion: { 30 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 0 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 29 }:version_{ 30 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "monkeEye2", id: "world_{ 0 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 33 }:version_{ 34 }", is std::type_index(typeid(GameEntityObject)): true.

[Game][GameData][LoadVFXEntityObjects]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadVFXEntityObjects]		 Loading Game VFX Objects (vfxEntityObjectsWorld)
[ArchetypedGameDataPool][SubpoolTiledVector] Default Constructed.
[ArchetypedGameDataPool][SubpoolTiledVector] Default Constructed.
[ArchetypedGameDataPool][SubpoolTiledVector] Default Constructed.
[ArchetypedGameDataPool][SubpoolTiledVector] Default Constructed.
[ArchetypedGameDataPool][SubpoolTiledVector] Default Constructed.

[ArchetypedGameDataPool]	----------------------------------------------------
[ArchetypedGameDataPool]	 Constructing an Archetyped Pool - it's a variadic archetype of { 5 } subpools.
[ArchetypedGameDataPool][SubpoolTiledVector] Initialized. maxPossiblePoolSize: { 6 }, tileSize: { 128 }, typeUID: { 2 }, topTypeStr: struct Game::GameEntityObject, worldIndex: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector] Initialized. maxPossiblePoolSize: { 6 }, tileSize: { 128 }, typeUID: { 4 }, topTypeStr: struct Game::Transform, worldIndex: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector] Initialized. maxPossiblePoolSize: { 6 }, tileSize: { 128 }, typeUID: { 8 }, topTypeStr: struct Game::Parent, worldIndex: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector] Initialized. maxPossiblePoolSize: { 6 }, tileSize: { 128 }, typeUID: { 16 }, topTypeStr: struct Game::Children, worldIndex: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector] Initialized. maxPossiblePoolSize: { 6 }, tileSize: { 128 }, typeUID: { 128 }, topTypeStr: struct Game::Bounds, worldIndex: { 1 }

[ArchetypedGameDataPool][Constructed a SubpoolTiledVector<struct Game::GameEntityObject>] T: struct Game::GameEntityObject, maxPossiblePoolSize: { 6 }, world: { 1 }, typeUID: { 2 }_struct Game::GameEntityObject, firstEmptyIndex: { 0 }, tiles: { 1 }, tileSize: { 128 }, subpool.items.size(): { 1 }

[ArchetypedGameDataPool][Constructed a SubpoolTiledVector<struct Game::Transform>] T: struct Game::Transform, maxPossiblePoolSize: { 6 }, world: { 1 }, typeUID: { 4 }_struct Game::Transform, firstEmptyIndex: { 0 }, tiles: { 1 }, tileSize: { 128 }, subpool.items.size(): { 1 }

[ArchetypedGameDataPool][Constructed a SubpoolTiledVector<struct Game::Parent>] T: struct Game::Parent, maxPossiblePoolSize: { 6 }, world: { 1 }, typeUID: { 8 }_struct Game::Parent, firstEmptyIndex: { 0 }, tiles: { 1 }, tileSize: { 128 }, subpool.items.size(): { 1 }

[ArchetypedGameDataPool][Constructed a SubpoolTiledVector<struct Game::Children>] T: struct Game::Children, maxPossiblePoolSize: { 6 }, world: { 1 }, typeUID: { 16 }_struct Game::Children, firstEmptyIndex: { 0 }, tiles: { 1 }, tileSize: { 128 }, subpool.items.size(): { 1 }

[ArchetypedGameDataPool][Constructed a SubpoolTiledVector<struct Game::Bounds>] T: struct Game::Bounds, maxPossiblePoolSize: { 6 }, world: { 1 }, typeUID: { 128 }_struct Game::Bounds, firstEmptyIndex: { 0 }, tiles: { 1 }, tileSize: { 128 }, subpool.items.size(): { 1 }
[ArchetypedGameDataPool]	 Constructed Archetyped Pool 0b10011110 and all its subpools and heap items.

[ArchetypedGameDataPool]	----------------------------------------------------

[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 0 }, with id: world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 0 }, with id: world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 0 }, with id: world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 0 }, with id: world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 1 }, with id: world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 1 }, with id: world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 1 }, with id: world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 1 }, with id: world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "icosphereSkybox_chaperone", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 2 }, with id: world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 2 }, with id: world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 2 }, with id: world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 2 }, with id: world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }, validSize: { 3 }, currentVersion: { 3 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "floorGrid", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 2 }:version_{ 3 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 3 }, with id: world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 3 }, with id: world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 3 }, with id: world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 3 }, with id: world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }, validSize: { 4 }, currentVersion: { 4 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "ceilingGrid", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 3 }:version_{ 4 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 4 }, with id: world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 4 }, with id: world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 4 }, with id: world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 4 }, with id: world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }, validSize: { 5 }, currentVersion: { 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 0 }, with id: world_{ 1 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }, validSize: { 1 }, currentVersion: { 1 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 0 }:version_{ 1 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "handLeft", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 4 }:version_{ 5 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::GameEntityObject>]	 Found free item at index: { 5 }, with id: world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::GameEntityObject>][owner chunk id: { -1 }]	 world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[Game][GameData][GameEntityObject]	 Using: {name: "EMPTY_NAME_GAME_ENTITY_OBJECT", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }", is std::type_index(typeid(GameEntityObject)): true.
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Transform>]	 Found free item at index: { 5 }, with id: world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Transform>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b100 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Parent>]	 Found free item at index: { 5 }, with id: world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Parent>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b1000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Children>]	 Found free item at index: { 5 }, with id: world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }, validSize: { 6 }, currentVersion: { 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Children>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b10000 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFirstFree<struct Game::Bounds>]	 Found free item at index: { 1 }, with id: world_{ 1 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }, validSize: { 2 }, currentVersion: { 2 }
[ArchetypedGameDataPool][SubpoolTiledVector][GetFreeItem<struct Game::Bounds>][owner chunk id: { 0 }]	 world_{ 1 }:type_{ 0b10000000 }:chunk_{ 0 }:index_{ 1 }:version_{ 2 }
[Game][GameData][LoadGameWorlds][GameEntityObject]	 Configured {name: "handRight", id: "world_{ 1 }:type_{ 0b10 }:chunk_{ 0 }:index_{ 5 }:version_{ 6 }", is std::type_index(typeid(GameEntityObject)): true.

[Game][GameData][LoadPlayers]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][LoadPlayers]		 Loading Players:
[Game][GameData][LoadPlayers]		 Loaded Players.
[Game][GameData][LoadPlayers]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[Game][GameData][LoadGameWorlds]				 Loaded Game World(s).
[Game][GameData][LoadGameWorlds]	.....................................................................................................................................


[Scripting][SceneSetup]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Scripting][SceneSetup]	 🎥 Scripted / scene objects setup.
~~~~[Scripting] setting ground size: 
~~~~[Scripting] setting floorGrid. 
~~~~[Scripting] setting ceilingGrid. 
[Scripting][SceneSetup]	 🎥 Scripted / scene objects setup done.
[Scripting][SceneSetup]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[Game][Main]		 Offsetting initial world root because we're running a virtual headset. worldRootTrans: { 0.000000, 1.700000, 0.000000 }

[Game][Renderer][SetUpRenderProcesses]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][Renderer][SetUpRenderProcesses]		 Setting up circular buffer of descriptor set pipeline data.

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
[Game][Renderer][SetUpRenderProcesses]		 done.
[Game][Renderer][SetUpRenderProcesses]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[Game][MirrorView][Connect]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][MirrorView][Connect]		 setting up game window
[Game][MirrorView][Connect]		 done.
[Game][MirrorView][Connect]		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[Game][Main]		『⛬』🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞
[Game][Main]		 Starting Game Loop:

[Game][SystemTransformPropagation][OnUpdate][Taskflow Graph Structure]		frame: { 1 }; name: ; graph size:{ 1 } ╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦
[Game][SystemTransformPropagation][OnUpdate][Taskflow Graph Structure]		┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬
digraph Taskflow {
subgraph cluster_p0000000DC28FE510 {
label="Taskflow: p0000000DC28FE490";
p00000158E6CDA270[label="p00000158E6CDA270" ];
}
}

[Game][SystemTransformPropagation][OnUpdate][Taskflow Graph Structure]		┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴
[Game][SystemTransformPropagation][OnUpdate][Taskflow Graph Structure]		frame: { 1 }; name: ; graph size:{ 1 } ╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩

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

[Game][Main]		🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞🎞『⛬』
[Game][Main]		 Game Loop ended. Cleaning up.

[Game][GameData][UnLoadGameWorlds]	.....................................................................................................................................
[Game][GameData][UnLoadGameWorlds]				 Unloading Game World(s):
[Game][GameData][UnLoadGameWorlds]	 Unloading entities and components, unhooking events, clearing any maps:
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::GameEntityObject>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::GameEntityObject>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Transform>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Transform>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Parent>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Parent>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Children>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Children>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Bounds>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Bounds>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::GameEntityObject>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::GameEntityObject>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Transform>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Transform>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Parent>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Parent>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Children>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Children>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Bounds>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[ArchetypedGameDataPool][SubpoolTiledVector][ClearItems<struct Game::Bounds>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[GameDataPool][ClearItems<struct Game::Model>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<struct Game::Model>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<struct Game::Model>] and all its heap items.
[~GameDataPool][Destructed<struct Game::Model>] and all its heap items.

[GameDataPool][ClearItems<struct Game::Material>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<struct Game::Material>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 8 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 9 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 10 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 11 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 12 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 13 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 14 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 15 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 16 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 17 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 18 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 19 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 20 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 21 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 22 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 23 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 24 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 25 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 26 }:version_{ 0 }.
[GameDataPool][ClearItems<struct Game::Material>]	 Delete item only: already marked as cleared/unused in pool: world_{ 0 }:type_{ 0b100000000 }:chunk_{ 0 }:index_{ 27 }:version_{ 0 }.
[~GameDataPool][Destructing<struct Game::Material>] and all its heap items.
[~GameDataPool][Destructed<struct Game::Material>] and all its heap items.

[GameDataPool][ClearItems<struct Game::Light>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<struct Game::Light>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<struct Game::Light>] and all its heap items.
[~GameDataPool][Destructed<struct Game::Light>] and all its heap items.

[GameDataPool][ClearItems<struct Game::Material>]	 Clearing the used pool items, and alsoDestroy (deleting memory) of whole pool: true; (destroy both used and cleared items).
[GameDataPool][ClearItems<struct Game::Material>]	 Also unsafe: true; items you clear now won't automatically clear their owner(s) and/or children's owner(s) (from other pools) (or "dangling" children). So you can clear them yourself after this in a more efficient / cache coherent pass.
[~GameDataPool][Destructing<struct Game::Material>] and all its heap items.
[~GameDataPool][Destructed<struct Game::Material>] and all its heap items.

[Game][GameData][UnLoadGameWorlds]				 Unloaded Game World(s).
[Game][GameData][UnLoadGameWorlds]	.....................................................................................................................................


[Game][Main][EXIT_SUCCESS]			 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[Game][GameData][~GameData]			 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[Game][GameData][~GameData]	 Deleting Game Data: players, entity pools, component pools, worlds. These all should have been unloaded already with the world(s).
[Game][GameData][GameData]	 Deleted Players.
[Game][GameData][GameData]	 Deleted Entity Pools.
[Game][GameData][GameData]	 Deleted Component Pools.
[Game][GameData][GameData]	 Deleted Worlds.
[Game][GameData][~GameData]	 Deleted Game Data.
[Game][GameData][~GameData]			 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
```
