#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "color.h"
#include "matrix.h"
#include "texturefinal.h"

namespace LumenAusf
{
    class texture_gl_es20;

    class shader_gl_es20
    {
       public:
        shader_gl_es20 (std::string_view vertex_src, std::string_view fragment_src, const std::vector<std::tuple<GLuint, const GLchar*>>& attributes);
        void use () const;
        void set_uniform (std::string_view uniform_name, texture_gl_es20* texture);
        void set_uniform (std::string_view uniform_name, const Color& c);
        void set_uniform (std::string_view uniform_name, const glm::mat4& m);

       private:
        GLuint compile_shader (GLenum shader_type, std::string_view src);
        GLuint link_shader_program (const std::vector<std::tuple<GLuint, const GLchar*>>& attributes);

        GLuint vert_shader = 0;
        GLuint frag_shader = 0;
        GLuint program_id = 0;
    };
}

#endif    // SHADER_H
