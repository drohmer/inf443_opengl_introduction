project('04_minimal_opengl_triangle', 'cpp')

cxxflags = ['-O2','-g','-std=c++1y','-Wall','-Wextra']

add_global_arguments(cxxflags, language : 'cpp')

incdir = include_directories('external/glad/include')

glfwdep = dependency('glfw3')
dldep = meson.get_compiler('cpp').find_library('dl')

src = ['src/main.cpp','external/glad/src/glad.cpp']

executable('pgm', sources : src, dependencies : [glfwdep,dldep], include_directories : incdir)

