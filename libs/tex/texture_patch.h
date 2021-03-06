/*
 * Copyright (C) 2015, Nils Moehrle
 * TU Darmstadt - Graphics, Capture and Massively Parallel Computing
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD 3-Clause license. See the LICENSE.txt file for details.
 */

#ifndef TEX_TEXTUREPATCH_HEADER
#define TEX_TEXTUREPATCH_HEADER

#include <vector>

#include <math/vector.h>
#include <mve/mesh.h>

#include "tri.h"
#include "texture_view.h"
#include "poisson_blending.h"

int const texture_patch_border = 1;

/**
  * Class representing a texture patch.
  * Contains additionaly to the rectangular part of the TextureView
  * the faces which it textures and their relative texture coordinates.
  */
class TexturePatch {
    public:
        typedef std::vector<std::size_t> Faces;
        typedef std::vector<math::Vec2f> Texcoords;

    private:
        int label;
        Faces faces;
        Texcoords texcoords;
        mve::FloatImage::Ptr image;
        mve::ByteImage::Ptr validity_mask;
        mve::ByteImage::Ptr blending_mask;

    public:
        /** Constructs a texture patch. */
        TexturePatch(int _label, std::vector<std::size_t> const & _faces,
            std::vector<math::Vec2f>  const & _texcoords, mve::ByteImage::Ptr _image);
        TexturePatch(TexturePatch const & texture_patch);

        /** Adjust the image colors and update validity mask. */
        void adjust_colors(std::vector<math::Vec3f> const & adjust_values);

        /** Compares texture patches image size. */
        bool operator<(TexturePatch const & texture_patch) const;

        math::Vec3f get_pixel_value(math::Vec2f pixel) const;
        void set_pixel_value(math::Vec2i pixel, math::Vec3f color);

        bool valid_pixel(math::Vec2i pixel) const;
        bool valid_pixel(math::Vec2f pixel) const;

        std::vector<std::size_t> & get_faces(void);
        std::vector<std::size_t> const & get_faces(void) const;
        std::vector<math::Vec2f> & get_texcoords(void);
        std::vector<math::Vec2f> const & get_texcoords(void) const;

        mve::FloatImage::ConstPtr get_image(void) const;
        mve::ByteImage::ConstPtr get_validity_mask(void) const;
        mve::ByteImage::ConstPtr get_blending_mask(void) const;

        std::pair<float, float> get_min_max(void) const;

        void release_blending_mask(void);
        void prepare_blending_mask(std::size_t strip_width);

        void erode_validity_mask(void);

        void blend(mve::FloatImage::ConstPtr orig);

        int get_label(void) const;
        int get_width(void) const;
        int get_height(void) const;
        int get_size(void) const;
};

inline int
TexturePatch::get_label(void) const {
    return label;
}

inline int
TexturePatch::get_width(void) const {
    return image->width();
}

inline int
TexturePatch::get_height(void) const {
    return image->height();
}

inline mve::FloatImage::ConstPtr
TexturePatch::get_image(void) const {
    return image;
}

inline mve::ByteImage::ConstPtr
TexturePatch::get_validity_mask(void) const {
    return validity_mask;
}

inline mve::ByteImage::ConstPtr
TexturePatch::get_blending_mask(void) const {
    assert(blending_mask != NULL);
    return blending_mask;
}

inline void
TexturePatch::release_blending_mask(void) {
    assert(blending_mask != NULL);
    blending_mask.reset();
}

inline std::vector<math::Vec2f> &
TexturePatch::get_texcoords(void) {
    return texcoords;
}

inline std::vector<std::size_t> &
TexturePatch::get_faces(void) {
    return faces;
}

inline std::vector<math::Vec2f> const &
TexturePatch::get_texcoords(void) const {
    return texcoords;
}

inline std::vector<std::size_t> const &
TexturePatch::get_faces(void) const {
    return faces;
}

inline int
TexturePatch::get_size(void) const {
    return get_width() * get_height();
}

inline bool
TexturePatch::operator<(TexturePatch const & other) const {
    return get_size() < other.get_size();
}

#endif /* TEX_TEXTUREPATCH_HEADER */
