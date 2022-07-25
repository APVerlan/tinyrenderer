#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "model.h"

namespace wavefront {

Model::ModelPtr BuildModelFromObjFile(const std::string& filename) {
    Model result;

    std::ifstream in;
    in.open(filename, std::ifstream::in);

    if (in.fail()) {
        throw std::runtime_error("bad file");
    }

    std::string line;
    while (!in.eof()) {
        std::getline(in, line);

        std::istringstream iss(line.c_str());
        char trash;

        if (!line.compare(0, 2, "v ")) {
            iss >> trash;

            geometry::Vector3f v;
            for (int i = 0; i < 3; i++) {
                iss >> v.raw[i];
            }

            result.verts_.push_back(v);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<int64_t> face;
            int64_t itrash, idx;
            
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--; // in wavefront obj all indices start at 1, not zero
                face.push_back(idx);
            }

            result.faces_.push_back(face);
        }
    }
    std::cerr << "# v# " << result.verts_.size() << " f# "  << result.faces_.size() << std::endl;

    return std::make_shared<Model>(result);
}

int64_t Model::GetNumVertices() const {
    return verts_.size();
}

int64_t Model::GetNumFaces() const {
    return faces_.size();
}

std::vector<int64_t> Model::GetFaceByIndex(int64_t idx) const {
    return faces_[idx];
}

geometry::Vector3f Model::GetVertexByIndex(int64_t i) const {
    return verts_[i];
}

} // wavefront