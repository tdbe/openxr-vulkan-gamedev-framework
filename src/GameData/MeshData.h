#pragma once
#include <glm/vec3.hpp>
#include <map>
#include <string>
#include <vector>

#include "Components/Model.h"

namespace Game
{
    struct Model;

    /*
     * The vertex struct provides the vertex definition used for all geometry in the project.
     */
    struct Vertex final
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 uv;
    };

    /*
     * The mesh data consists of a vertex and index collection for geometric data. It is not intended to stay alive in
     * memory after loading is done. It's purpose is rather to serve as a container for geometry data read in from OBJ model
     * files until that gets uploaded to a Vulkan vertex/index buffer on the GPU. Note that the models in the mesh data
     * class should be unique, a model that is rendered several times only needs to be loaded once. As many model structs as
     * required can then be derived from the same data.
     */
    /// [tdbe] TODO: get a proper GLTF library with animation and scene support etc.
    /// Todo: use a GameDataPool or equivalent for storing the various data, so we can add and remove objects 
    /// without tons of actual creations & deletions (although we also need to support asset-streaming style actual deletions to clear cpu-side RAM)
    struct MeshData final
    {
      public:
        enum class Color
        {
            White,
            FromNormals
        };
        bool LoadModel(const std::string& filename,
                       Color color,
                       Model* model);
        bool UnLoadModelMesh(const Model* model);

        size_t GetSize() const;
        size_t GetIndexOffset() const;

        void WriteTo(char* destination) const;

        MeshData();
        ~MeshData();

      private:
        std::vector<Vertex> allLoadedGameVertices;
        std::vector<uint32_t> allLoadedGameIndexes;
    };
} // namespace Game