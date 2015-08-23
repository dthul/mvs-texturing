#pragma once

#include <vector>

#include "Material.h"

/**
  * Class representing a material lib of and obj model.
  */
class MaterialLib {
    private:
        std::vector<Material> materials;
        std::vector<std::string> material_names;
    public:
        MaterialLib();

        void add_material(std::string const & name, Material material);
        std::size_t size();

        /** Saves the material lib to an .mtl file and all textures of its
          * materials with the given prefix.
          */
        void save_to_files(std::string const & prefix) const;
};

inline std::size_t
MaterialLib::size() {
    return materials.size();
}
