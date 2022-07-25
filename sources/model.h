#ifndef __MODEL_H__
#define __MODEL_H__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

#include "geometry.h"

namespace wavefront {

class Model {
  public:
	using ModelPtr = std::shared_ptr<Model>;

  public:
	Model() = default;
	Model(Model&) = default;

  public:
    friend ModelPtr BuildModelFromObjFile(const std::string& filename);

	int64_t GetNumVertices() const;
	int64_t GetNumFaces() const;

	geometry::Vector3f GetVertexByIndex(int64_t i) const;
	std::vector<int64_t> GetFaceByIndex(int64_t idx) const;

  private:
	std::vector<geometry::Vector3f> verts_;
	std::vector<std::vector<int64_t>> faces_;
};

Model::ModelPtr BuildModelFromObjFile(const std::string& filename);

} // wavefront

#endif //__MODEL_H__