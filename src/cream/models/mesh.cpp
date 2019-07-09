#define GLM_ENABLE_EXPERIMENTAL
#include "mesh.hpp"
#include <fstream>
#include <glm/gtx/string_cast.hpp>  // glm::to_string
#include <iostream>
#include <sstream>
#include "clog/clog.hpp"
#include "materials.hpp"

namespace cream {

Mesh::Mesh() {
}

Mesh::~Mesh() {
}

void Mesh::print() {
    std::cout << "Vertices: " << num_vertices_ << std::endl;
    for (const auto &v : vertices_) {
        std::cout << "v " << glm::to_string(v) << std::endl;
    }
    for (const auto &c : colours_) {
        std::cout << "c " << glm::to_string(c) << std::endl;
    }
    for (const auto &n : normals_) {
        std::cout << "n " << glm::to_string(n) << std::endl;
    }
}

void Mesh::clear() {
    num_vertices_ = 0;
    vertices_.clear();
    colours_.clear();
    normals_.clear();
}

void Mesh::load_obj(const std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        clog::Log::get()->warn(".obj file ", path, " not found.");
        return;
    }
    clog::Log::get()->info(".obj file ", path, " found.");

    std::string line;
    std::string word;
    std::string word1;
    std::string word2;
    std::string word3;

    // Temp
    std::vector<glm::vec3> v;
    std::vector<glm::vec3> vt;
    std::vector<glm::vec3> vn;

    Materials materials;
    Material material;

    while (getline(file, line)) {
        std::stringstream iss(line);
        iss >> word;

        if (word == "mtllib") {
            iss >> word1;
            materials.load("./models/" + word1);
            materials.print();
        } else if (word == "usemtl") {
            iss >> word1;
            material = materials.find(word1);
        } else if (word == "v") {
            iss >> word1 >> word2 >> word3;
            v.push_back(glm::vec3(std::stof(word1), std::stof(word2), std::stof(word3)));
        } else if (word == "vt") {
            iss >> word1 >> word2 >> word3;
            vt.push_back(glm::vec3(std::stof(word1), std::stof(word2), std::stof(word3)));
        } else if (word == "vn") {
            iss >> word1 >> word2 >> word3;
            vn.push_back(glm::vec3(std::stof(word1), std::stof(word2), std::stof(word3)));
        }
        // f v/vt/vn v/vt/vn v/vt/vn ...
        else if (word == "f") {
            bool first = false;
            bool second = false;
            // Track three vertices to draw our triangle
            int v_index[3] = {0, 0, 0};
            int vt_index[3] = {0, 0, 0};
            int vn_index[3] = {0, 0, 0};

            // v/vt/vn
            while (iss >> word) {
                std::string part;
                std::stringstream iss_word(word);
                int indices[3] = {0, 0, 0};

                int i = 0;
                while (getline(iss_word, part, '/')) {
                    if (part != "") {
                        indices[i] = std::stoi(part);
                    }

                    i++;
                }

                if (indices[0] < 0) {
                    indices[0] = v.size() + indices[0];
                }
                if (indices[1] < 0) {
                    indices[1] = vt.size() + indices[1];
                }
                if (indices[2] < 0) {
                    indices[2] = vn.size() + indices[2];
                }

                if (!first) {
                    v_index[0] = indices[0];
                    vt_index[0] = indices[1];
                    vn_index[0] = indices[2];
                    first = true;
                } else if (!second) {
                    v_index[1] = indices[0];
                    vt_index[1] = indices[1];
                    vn_index[1] = indices[2];
                    second = true;
                } else {
                    v_index[2] = indices[0];
                    vt_index[2] = indices[1];
                    vn_index[2] = indices[2];

                    const glm::vec3 a = v[v_index[1]] - v[v_index[0]];
                    const glm::vec3 b = v[v_index[2]] - v[v_index[0]];
                    const glm::vec3 c = glm::cross(a, b);

                    for (int j = 0; j < 3; ++j) {
                        assert(v_index[j] >= 0);
                        assert(vt_index[j] >= 0);
                        assert(vn_index[j] >= 0);

                        vertices_.push_back(v[v_index[j] - 1]);
                        colours_.push_back(material.kd_);

                        if (vn_index[j] > 0) {
                            normals_.push_back(vn[vn_index[j] - 1]);
                        } else {
                            normals_.push_back(c);
                        }
                    }

                    v_index[1] = v_index[2];
                    vt_index[1] = vt_index[2];
                    vn_index[1] = vn_index[2];
                }
            }
        } else {
        }
    }

    num_vertices_ = vertices_.size();
    v.clear();
    vt.clear();
    vn.clear();

    clog::Log::get()->info(num_vertices_, " vertices loaded.");
}

}  // namespace cream
