#pragma once

#include "MaterialLib.h"

/**
  * Class representing a obj model.
  */
class ObjModel {
public:
    struct Face {
        std::size_t vertices[3];
        std::size_t texcoords[3];
        std::size_t normals[3];
    };

    struct Group {
        std::string material_name;
        std::vector<Face> faces;
    };

    typedef std::vector<math::Vec3f> Vertices;
    typedef std::vector<math::Vec2f> TexCoords;
    typedef std::vector<math::Vec3f> Normals;
    typedef std::vector<Group> Groups;

private:
    Vertices vertices;
    TexCoords texcoords;
    Normals normals;
    Groups groups;
    MaterialLib material_lib;

public:
    /** Saves the obj model to an .obj file, its material lib and the materials with the given prefix. */
    void save_to_files(std::string const & prefix) const;
    ObjModel();

    MaterialLib & get_material_lib(void);
    Vertices & get_vertices(void);
    TexCoords & get_texcoords(void);
    Normals & get_normals(void);
    Groups & get_groups(void);

    static void save(ObjModel const & model, std::string const & prefix);
};

inline
MaterialLib &
ObjModel::get_material_lib(void) {
    return material_lib;
}

inline
ObjModel::Vertices &
ObjModel::get_vertices(void) {
    return vertices;
}

inline
ObjModel::TexCoords &
ObjModel::get_texcoords(void) {
    return texcoords;
}

inline
ObjModel::Normals &
ObjModel::get_normals(void) {
    return normals;
}

inline
ObjModel::Groups &
ObjModel::get_groups(void) {
    return groups;
}
