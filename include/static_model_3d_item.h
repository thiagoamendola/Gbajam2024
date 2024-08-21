
#ifndef STATIC_MODEL_3D_ITEM_H
#define STATIC_MODEL_3D_ITEM_H

#include "bn_color.h"
#include "bn_span.h"

#include "fr_model_3d.h"
#include "fr_point_3d.h"

template <const fr::model_3d_item &model_3d_item_ref> class static_model_3d_item
{
  public:
    constexpr static_model_3d_item(fr::point_3d position, bn::fixed theta)
        : static_model_3d_item(position, theta, nullptr) {};

    // x, y (back/forward), z (down/up)
    constexpr static_model_3d_item(fr::point_3d position, bn::fixed theta,
                                   const bn::color *palette)
        : _vertices(_create_array<fr::vertex_3d, vertices_count>(
              model_3d_item_ref.vertices()[0])),
          _faces(_create_array<fr::face_3d, faces_count>(
              model_3d_item_ref.faces()[0])),
          _palette(palette)
    {
        const bn::span<const fr::vertex_3d> &input_vertices =
            model_3d_item_ref.vertices();

        // bn::fixed minimum_y = input_vertices[0].point().y();
        int max_cylinder_squared_radius = 0;

        for (int index = 0; index < vertices_count; ++index)
        {
            const fr::point_3d &input_point = input_vertices[index].point();
            int abs_x = bn::abs(input_point.x()).ceil_integer();
            int abs_z = bn::abs(input_point.z()).ceil_integer();
            int cylinder_squared_radius = (abs_x * abs_x) + (abs_z * abs_z);
            max_cylinder_squared_radius =
                bn::max(max_cylinder_squared_radius, cylinder_squared_radius);
            // minimum_y = bn::min(minimum_y, input_point.y());
        }

        fr::model_3d model(model_3d_item_ref);
        model.set_position(position);
        model.set_theta(theta);
        model.update();

        int cylinder_radius = bn::sqrt(max_cylinder_squared_radius);
        _vertical_cylinder = fr::model_3d_vertical_cylinder(
            position.x(), position.z(), cylinder_radius);

        for (int index = 0; index < vertices_count; ++index)
        {
            fr::vertex_3d transformed_vertex(
                model.transform(input_vertices[index]));
            _vertices[index] = transformed_vertex;
        }

        const bn::span<const fr::face_3d> &input_faces =
            model_3d_item_ref.faces();

        for (int index = 0; index < faces_count; ++index)
        {
            const fr::face_3d &input_face = input_faces[index];
            fr::vertex_3d rotated_normal(model.rotate(input_face.normal()));

            if (input_face.triangle())
            {
                _faces[index] = fr::face_3d(
                    _vertices, rotated_normal, input_face.first_vertex_index(),
                    input_face.second_vertex_index(),
                    input_face.third_vertex_index(),
                    input_face
                        .color_index(), // <-- HERE for static models likely
                    input_face.shading());
            }
            else
            {
                _faces[index] = fr::face_3d(
                    _vertices, rotated_normal, input_face.first_vertex_index(),
                    input_face.second_vertex_index(),
                    input_face.third_vertex_index(),
                    input_face.fourth_vertex_index(), input_face.color_index(),
                    input_face.shading());
            }
        }
    }

    [[nodiscard]] constexpr fr::model_3d_item item() const
    {
        const bn::color *color_palette =
            !!_palette ? _palette : model_3d_item_ref.palette();
        return fr::model_3d_item(_vertices, _faces,
                                 model_3d_item_ref.collision_face(),
                                 &_vertical_cylinder, color_palette);
    }

  private:
    static constexpr int vertices_count = model_3d_item_ref.vertices().size();
    static constexpr int faces_count = model_3d_item_ref.faces().size();

    bn::array<fr::vertex_3d, vertices_count> _vertices;
    bn::array<fr::face_3d, faces_count> _faces;
    fr::model_3d_vertical_cylinder _vertical_cylinder;
    const bn::color *_palette;

    template <typename Type, unsigned Size>
    [[nodiscard]] static constexpr bn::array<Type, Size> _create_array(
        const Type &value)
    {
        return _create_array_impl(value, bn::make_index_sequence<Size>());
    }

    template <typename Type, unsigned... IndexSequence>
    [[nodiscard]] static constexpr bn::array<Type, sizeof...(IndexSequence)>
    _create_array_impl(Type value, bn::index_sequence<IndexSequence...>)
    {
        return {{(static_cast<void>(IndexSequence), value)...}};
    }
};

#endif
