#define GLM_ENABLE_EXPERIMENTAL
#include <fstream>
#include <iostream>
#include <glm/gtx/string_cast.hpp> // glm::to_string
#include <cassert>
#include "materials.hpp"

namespace cream
{
    void Materials::load(const std::string path)
    {
        std::ifstream file(path);
        if(!file.is_open())
        {
            return;
        }

        Material material;
        std::string word;
        std::string word1;
        std::string word2;
        std::string word3;

        while(file >> word)
        {
            if(word == "newmtl")
            {
                if(material.name_ != "")
                {
                    add(material);
                    material = Material();
                }

                file >> word1;
                material.name_ = word1;
            }
            else if(word == "d")
            {
                file >> word1;
                material.d_ = std::stof(word1);
            }
            else if(word == "Tr")
            {
                file >> word1;
                material.d_ = 1.0 - std::stof(word1);
            }
            else if(word == "Ns")
            {
                file >> word1;
                material.ns_ = std::stof(word1);
            }
            else if(word == "Ka")
            {
                file >> word1 >> word2 >> word3;
                material.ka_ = glm::vec3(std::stof(word1), std::stof(word2), std::stof(word3));
            }
            else if(word == "Kd")
            {
                file >> word1 >> word2 >> word3;
                material.kd_ = glm::vec3(std::stof(word1), std::stof(word2), std::stof(word3));
            }
            else if(word == "Ks")
            {
                file >> word1 >> word2 >> word3;
                material.ks_ = glm::vec3(std::stof(word1), std::stof(word2), std::stof(word3));
            }
            else if(word == "Ke")
            {
                file >> word1 >> word2 >> word3;
                material.ke_ = glm::vec3(std::stof(word1), std::stof(word2), std::stof(word3));
            }
            else if(word == "Ni")
            {
                file >> word1;
                material.ni_ = std::stof(word1);
            }
            else if(word == "illum")
            {
                file >> word1;
                material.illum_ = std::stoi(word1);
            }
            else
            {
            }
        }

        if(material.name_ != "")
        {
            add(material);
            material = Material();
        }
    }

    void Materials::add(Material &material)
    {
        if(has(material.name_))
        {
            // TODO: Log a warning
            return;
        }
        materials_[material.name_] = material;
        assert(has(material.name_));
    }

    bool Materials::has(const std::string name)
    {
        return materials_.find(name) != materials_.end();
    }

    Material &Materials::find(const std::string name)
    {
        if(has(name))
        {
            return materials_[name];
        }

        // If we can't find the material specified, return the default
        return basic_;
    }

    void Materials::erase(const std::string name)
    {
        materials_.erase(name);
        assert(!has(name));
    }

    void Materials::print()
    {
        for(auto const &[key, material] : materials_)
        {
            std::cout << "Material: " << material.name_ << std::endl;
        }
    }
}
