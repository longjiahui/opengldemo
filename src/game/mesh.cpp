#include "game/mesh.hpp"
#include "lib/assimp.hpp"
#include "lib/glm.hpp"

using namespace std;
using namespace huigl;
using namespace glm;

Mesh::Mesh(const char *path) {
  Object();
  // Load the mesh from the file
  Assimp::Importer importer;
  const auto scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    throw new runtime_error(string("ERROR::ASSIMP: ") +
                            importer.GetErrorString());
  }
}