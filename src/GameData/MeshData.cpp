#pragma once
#include <tinyobjloader/tiny_obj_loader.h>
#include <cstring>

#include "../Utils/Util.h"
#include "MeshData.h"

using namespace Game;
using namespace util;

Game::MeshData::MeshData()
{
}

bool MeshData::LoadModel(const std::string& filename,
                         Color color, 
                         Model* model)
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  if (!tinyobj::LoadObj(&attrib, &shapes, nullptr, nullptr, nullptr, filename.c_str()))
  {
    util::LogError(Error::ModelLoadingFailure, filename);
    return false;
  }

  const size_t oldIndexCount = allLoadedGameIndexes.size();
  glm::vec3 startPt = { attrib.vertices[3 * shapes[0].mesh.indices[0].vertex_index + 0],
                        attrib.vertices[3 * shapes[0].mesh.indices[0].vertex_index + 1],
                        attrib.vertices[3 * shapes[0].mesh.indices[0].vertex_index + 2] };
  glm::vec3 minPoint = startPt;
  glm::vec3 maxPoint = startPt;

  for (const tinyobj::shape_t& shape : shapes)
  {
    for (const tinyobj::index_t& index : shape.mesh.indices)
    {
      Vertex vertex;

      vertex.position = { attrib.vertices[3 * index.vertex_index + 0], 
                          attrib.vertices[3 * index.vertex_index + 1],
                          attrib.vertices[3 * index.vertex_index + 2] };
      minPoint = glm::min(minPoint, vertex.position);
      maxPoint = glm::max(maxPoint, vertex.position);

      if (index.normal_index >= 0)
      {
        vertex.normal = { attrib.normals[3 * index.normal_index + 0], 
                          attrib.normals[3 * index.normal_index + 1],
                          attrib.normals[3 * index.normal_index + 2] };
      }
      else
      {
        vertex.normal = { 0.0f, 0.0f, 0.0f };
      }

      if (index.texcoord_index >= 0)
      {
          vertex.uv = { attrib.texcoords[2 * index.texcoord_index + 0], 
                        attrib.texcoords[2 * index.texcoord_index + 1],
                        //attrib.texcoord_ws[2 * index.texcoord_index + 0] 
                        };
      }
      else
      {
          vertex.uv = { 0.0f, 0.0f };
      }

      switch (color)
      {
      case Color::White:
        vertex.color = { 1.0f, 1.0f, 1.0f };
        break;
      case Color::FromNormals:
        vertex.color = vertex.normal;
        break;
      }

      allLoadedGameVertices.push_back(vertex);
      allLoadedGameIndexes.push_back(static_cast<uint32_t>(allLoadedGameIndexes.size()));
    }
  }

  model->firstIndex = oldIndexCount;
  model->indexCount = allLoadedGameIndexes.size() - oldIndexCount;
  model->minPointAABB = minPoint;
  model->maxPointAABB = maxPoint;

  util::DebugLog("[MeshData] LoadModel: " + filename + "; total meshData size so far: " + util::ToString(GetSize()));
  return true;
}

/// [tdbe] This is mostly here to draw attention to the <see cref="Model"/> --> <see cref="MeshData"/> --> <see cref="DataBuffer"/> relationship.
/// Not very useful: 
/// 1). We move all possible 3d models to the gpu on <see cref="LoadGameWorld"/>, and then never replace any parts of those vertex buffers (unless we unload/reload). 
/// 2). We'd need a better data streaming strategy than arbitrary recreation of the whole buffer.
bool Game::MeshData::UnLoadModelMesh(const Model* model)
{
    util::DebugLog("[MeshData][Model]\t ! completely deleting this model's mesh data !: " + model->id.PrintGlobalUID());

    allLoadedGameVertices.erase(allLoadedGameVertices.begin() + model->firstIndex,
                                allLoadedGameVertices.begin() + model->firstIndex + model->indexCount);
    return true;
}

size_t MeshData::GetSize() const
{
  return sizeof(allLoadedGameVertices.at(0u)) * allLoadedGameVertices.size() + sizeof(allLoadedGameIndexes.at(0u)) * allLoadedGameIndexes.size();
}

size_t MeshData::GetIndexOffset() const
{
  return sizeof(allLoadedGameVertices.at(0u)) * allLoadedGameVertices.size();
}

void MeshData::WriteTo(char* destination) const
{
  const size_t verticesSize = sizeof(allLoadedGameVertices.at(0u)) * allLoadedGameVertices.size();
  const size_t indicesSize = sizeof(allLoadedGameIndexes.at(0u)) * allLoadedGameIndexes.size();
  memcpy(destination, allLoadedGameVertices.data(), verticesSize);              // Vertex section first
  memcpy(destination + verticesSize, allLoadedGameIndexes.data(), indicesSize); // Index section next
}

Game::MeshData::~MeshData()
{
    allLoadedGameVertices.clear();
    allLoadedGameIndexes.clear();
}