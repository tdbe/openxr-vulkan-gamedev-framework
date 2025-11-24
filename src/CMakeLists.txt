set(TARGET_NAME openxr-vulkan-framework)

# Define vert frag shader files (the "include" files will be found automatically)
set(SHADER_SRC  	
	Shaders/DiffuseTransparent.vert
	Shaders/DiffuseTransparent.frag

	Shaders/Diffuse.vert
	Shaders/Diffuse.frag	
	
	Shaders/Ground.vert
	Shaders/Ground.frag

	Shaders/TripShader.vert
	Shaders/TripShader.frag

	Shaders/EyeShader.vert
	Shaders/EyeShader.frag
	
	Shaders/Light.vert
	Shaders/Light.frag
	
	Shaders/LightTentacle.vert
	Shaders/LightTentacle.frag

	Shaders/GridGround.vert
	Shaders/GridGround.frag

	Shaders/GridSimple.vert
	Shaders/GridSimple.frag

	Shaders/Hands.vert
	Shaders/Hands.frag

	Shaders/Sky.vert
	Shaders/Sky.frag
	
	Shaders/SkyOfChaperone.vert
	Shaders/SkyOfChaperone.frag
)

set(SRC
	Main.cpp

	OpenXrAndVulkan/Context.cpp
	OpenXrAndVulkan/Context.h

	OpenXrInput/Input.cpp
	OpenXrInput/Input.h
	OpenXrInput/InputData.h

	OpenXrAndVulkan/DataBuffer.cpp
	OpenXrAndVulkan/DataBuffer.h

	OpenXrAndVulkan/Headset.cpp
	OpenXrAndVulkan/Headset.h

	OpenXrAndVulkan/ImageBuffer.cpp
	OpenXrAndVulkan/ImageBuffer.h

	OpenXrAndVulkan/MirrorView.cpp
	OpenXrAndVulkan/MirrorView.h
	
	GameMechanics/WorldObjectsMiscBehaviour.cpp
	GameMechanics/WorldObjectsMiscBehaviour.h
	GameMechanics/LocomotionBehaviour.cpp
	GameMechanics/LocomotionBehaviour.h
	GameMechanics/HandsBehaviour.cpp
	GameMechanics/HandsBehaviour.h
	GameMechanics/InputTesterBehaviour.cpp
	GameMechanics/InputTesterBehaviour.h
	GameMechanics/GameBehaviour.cpp
	GameMechanics/GameBehaviour.h
	
	GameData/GameDataId.h
	
	GameData/Entities/GameEntity.h
	GameData/Entities/GameEntity.cpp
	
	GameData/Components/GameComponent.h
	GameData/Components/GameComponent.cpp
		
	GameData/Components/Transform.h
	GameData/Components/Bounds.h
	GameData/Components/Material.h
	GameData/Components/Model.h

	GameData/Components/Light.h
	GameData/Components/Light.cpp

	GameData/PlayerObject.h

	GameData/GameDataPool.h
	GameData/GameDataPool.cpp
	
	GameData/MeshData.cpp
	GameData/MeshData.h
	
	GameData/Entities/GameEntityObject.cpp
	GameData/Entities/GameEntityObject.h
	
	GameData/GameData.h
	GameData/GameData.cpp

	OpenXrAndVulkan/Pipeline.cpp
	OpenXrAndVulkan/Pipeline.h

	OpenXrAndVulkan/Renderer.cpp
	OpenXrAndVulkan/Renderer.h

	OpenXrAndVulkan/RenderProcess.cpp
	OpenXrAndVulkan/RenderProcess.h

	OpenXrAndVulkan/RenderTarget.cpp
	OpenXrAndVulkan/RenderTarget.h

	Utils/Util.cpp
	Utils/Util.h
	
	Scripting/Scripting.hpp

	${SHADER_SRC}
)

set(ENV{VULKAN_SDK} "C:/VulkanSDK/1.4.309.0/Include/")

find_package(Vulkan REQUIRED)
#target_link_libraries(target ${Vulkan_LIBRARIES})

add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE ${SRC})
target_include_directories(${TARGET_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} PRIVATE boxer glfw glm openxr tinyobjloader ${Vulkan_LIBRARIES})

# [tdbe] this instead of #define DEBUG
#target_compile_definitions(${TARGET_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>) # Add a clean DEBUG prepocessor define if applicable
set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>") # For MSVC debugging

# Copy shared library binaries on Windows
if(WIN32)
	set (DLLS "${CMAKE_SOURCE_DIR}/external/glfw/lib/win/glfw3.dll")
	foreach (DLL ${DLLS})
		add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${DLL} "$<TARGET_FILE_DIR:${TARGET_NAME}>")
	endforeach()
endif()

# Copy models folder
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory "${CMAKE_SOURCE_DIR}/models" "$<TARGET_FILE_DIR:${TARGET_NAME}>/models")

# Create output folder for compiled Shaders
# Otherwise shader compilation fails
add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD 
	COMMAND ${CMAKE_COMMAND} ARGS -E make_directory "$<TARGET_FILE_DIR:${TARGET_NAME}>/Shaders"
)

# Compile Shaders into output folder
foreach(SHADER ${SHADER_SRC})
    set(SHADER_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/${SHADER}")
    add_custom_command(TARGET ${TARGET_NAME} DEPENDS ${SHADER_INPUT} COMMAND glslc ARGS --target-env=vulkan1.3 ${SHADER_INPUT} -std=450core -O -o "$<TARGET_FILE_DIR:${TARGET_NAME}>/${SHADER}.spv" $<$<NOT:$<CONFIG:DEBUG>>:-O> COMMENT ${SHADER})
endforeach()