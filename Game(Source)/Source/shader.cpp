#include "shader.h"

namespace LumenAusf
{
    shader_gl_es20::shader_gl_es20 (std::string_view vertex_src, std::string_view fragment_src,
                                    const std::vector<std::tuple<GLuint, const GLchar*>>& attributes)
    {
        vert_shader = compile_shader (GL_VERTEX_SHADER, vertex_src);
        frag_shader = compile_shader (GL_FRAGMENT_SHADER, fragment_src);
        if (vert_shader == 0 || frag_shader == 0)
        {
            throw std::runtime_error ("can't compile shader");
        }
        program_id = link_shader_program (attributes);
        if (program_id == 0)
        {
            throw std::runtime_error ("can't link shader");
        }
    }

    void shader_gl_es20::use () const
    {
        glUseProgram (program_id);
        GL_ERROR_CHECK ();
    }

    void shader_gl_es20::set_uniform (std::string_view uniform_name, texture_gl_es20* texture)
    {
        assert (texture != nullptr);
        const int location = glGetUniformLocation (program_id, uniform_name.data ());
        GL_ERROR_CHECK ();
        if (location == -1)
        {
            std::cerr << "can't get uniform location from shader\n";
            throw std::runtime_error ("can't get uniform location");
        }
        unsigned int texture_unit = 0;
        glActiveTexture (GL_TEXTURE0 + texture_unit);
        GL_ERROR_CHECK ();

        texture->bind ();

        // http://www.khronos.org/opengles/sdk/docs/man/xhtml/glUniform.xml
        glUniform1i (location, static_cast<int> (0 + texture_unit));
        GL_ERROR_CHECK ();
    }

    void shader_gl_es20::set_uniform (std::string_view uniform_name, const Color& c)
    {
        const int location = glGetUniformLocation (program_id, uniform_name.data ());
        GL_ERROR_CHECK ();
        if (location == -1)
        {
            std::cerr << "can't get uniform location from shader\n";
            throw std::runtime_error ("can't get uniform location");
        }
        float values[4] = {c.get_r (), c.get_g (), c.get_b (), c.get_a ()};
        glUniform4fv (location, 1, &values[0]);
        GL_ERROR_CHECK ();
    }

    void shader_gl_es20::set_uniform (std::string_view uniform_name, const mat2x3& m)
    {
        const int location = glGetUniformLocation (program_id, uniform_name.data ());
        GL_ERROR_CHECK ();
        if (location == -1)
        {
            std::cerr << "can't get uniform location from shader\n";
            throw std::runtime_error ("can't get uniform location");
        }
        // OpenGL wants matrix in column major order
        // clang-format off
        float values[9] = { m.col0.x,  m.col0.y, m.delta.x,
                            m.col1.x, m.col1.y, m.delta.y,
                            0.f,      0.f,       1.f };
        // clang-format on
        glUniformMatrix3fv (location, 1, GL_FALSE, &values[0]);
        GL_ERROR_CHECK ();
    }

    GLuint shader_gl_es20::compile_shader (GLenum shader_type, std::string_view src)
    {
        GLuint shader_id = glCreateShader (shader_type);
        GL_ERROR_CHECK ();
        std::string_view vertex_shader_src = src;
        const char* source = vertex_shader_src.data ();
        glShaderSource (shader_id, 1, &source, nullptr);
        GL_ERROR_CHECK ();

        glCompileShader (shader_id);
        GL_ERROR_CHECK ();

        GLint compiled_status = 0;
        glGetShaderiv (shader_id, GL_COMPILE_STATUS, &compiled_status);
        GL_ERROR_CHECK ();
        if (compiled_status == 0)
        {
            GLint info_len = 0;
            glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_len);
            GL_ERROR_CHECK ();
            std::vector<char> info_chars (static_cast<size_t> (info_len));
            glGetShaderInfoLog (shader_id, info_len, NULL, info_chars.data ());
            GL_ERROR_CHECK ();
            glDeleteShader (shader_id);
            GL_ERROR_CHECK ();

            std::string shader_type_name = shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment";
            std::cerr << "Error compiling shader(vertex)\n" << vertex_shader_src << "\n" << info_chars.data ();
            return 0;
        }
        return shader_id;
    }
    GLuint shader_gl_es20::link_shader_program (const std::vector<std::tuple<GLuint, const GLchar*>>& attributes)
    {
        GLuint program_id_ = glCreateProgram ();
        GL_ERROR_CHECK ();
        if (0 == program_id_)
        {
            std::cerr << "failed to create gl program";
            throw std::runtime_error ("can't link shader");
        }

        glAttachShader (program_id_, vert_shader);
        GL_ERROR_CHECK ();
        glAttachShader (program_id_, frag_shader);
        GL_ERROR_CHECK ();

        // bind attribute location
        for (const auto& attr : attributes)
        {
            GLuint loc = std::get<0> (attr);
            const GLchar* name = std::get<1> (attr);
            glBindAttribLocation (program_id_, loc, name);
            GL_ERROR_CHECK ();
        }

        // link program after binding attribute locations
        glLinkProgram (program_id_);
        GL_ERROR_CHECK ();
        // Check the link status
        GLint linked_status = 0;
        glGetProgramiv (program_id_, GL_LINK_STATUS, &linked_status);
        GL_ERROR_CHECK ();
        if (linked_status == 0)
        {

        }
        return program_id_;
    }
}
