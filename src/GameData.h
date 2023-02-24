#pragma once
#include <string>
#include <array>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

//#include <vulkan/vulkan.h>
#include "Pipeline.h"

// [tdbe] TODO: Default Material struct. Can treat as "uber material" data,
// or can make multiple versions of this.
struct Material 
{
	DynamicMaterialUniformData dynamicUniformData = {};
	// [tdbe] if you change any of the shaders, the renderer creates a new pipeline with the shaders.
	std::string vertShaderName = "shaders/Diffuse.vert.spv";
	std::string fragShaderName = "shaders/Diffuse.frag.spv";
	// [tdbe] if you change any pipeline data properties, the renderer creates a new pipeline for this shader.
	PipelineMaterialPayload pipelineData = {};
	// [tdbe] TODO: textures 🙃 set up per material descriptor sets, with descriptor layouts that support textures.
	// VkDescriptorSet descriptorSet;
	// and then use different pipelines for each pipeline layout here, as needed:
	Pipeline* pipeline = nullptr; //vkPipeline; right now it points to just 2 or 3 pipelines, not really one per material.
};

/*
 * The model struct holds all required information to orientate and render a model. It handles orientation with a world
 * transformation matrix and has its indexing information populated by the mesh data class. This struct represents a
 * single draw call and is used by the renderer class to know how and where to draw a model.
 */
struct Model final
{
  size_t firstIndex = 0u;
  size_t indexCount = 0u;
};

struct GameObject{
	std::string name = "game object";
	// [tdbe] isVisible means whether or not it will be rendered
	bool isVisible = true;
	// [tdbe] coordinate system: Y is up, Z is forward
	glm::mat4 worldMatrix = glm::mat4(1.0f);
	Model *model = nullptr;
	Material *material = nullptr;
	GameObject(Model *model_ = nullptr, Material *material_ = nullptr, bool isVisible_ = true, std::string name_ = "game object"){
		name = name_;
		model = model_;
		material = material_;
		isVisible = isVisible_;
	}
};

// [tdbe] Note: this is meant to be used in a list or a table of states.
//				because a player can be in locomotion and grabbing with each hand,
//				all at the same time.
// Use for example in a: std::array<bool, (int)PlayerStates::COUNT> playerStatesList;
// Used as flagging so other interactions scripts can know they shouldn't e.g. grab stuff while in inappropriate states. 
enum class PlayerStates{
	Idle = 0,
	LocomotionState = 1,
	GrabbingLeft = 2,
	GrabbingRight = 3,
	COUNT = 4
};

struct PlayerObject{
	std::string name = "player object";
	GameObject* head = nullptr;
	GameObject* handLeft = nullptr;
	GameObject* handRight = nullptr;
	// [tdbe] Please see PlayerStates definition for info.
	std::array<bool, (int)PlayerStates::COUNT> playerActiveStates = {true, false, false, false};
	PlayerObject(std::string name_ = "player object", GameObject* head_ = nullptr, GameObject* handLeft_ = nullptr, GameObject* handRight_ = nullptr){
		name = name_;
		head = head_;
		handLeft = handLeft_;
		handRight = handRight_;
	}
};