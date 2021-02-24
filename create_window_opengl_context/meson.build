project('02_minimal_window_opengl_context', 'cpp')

cxxflags = ['-O2','-g','-std=c++11','-Wall','-Wextra']

add_global_arguments(cxxflags, language : 'cpp')

glfwdep = dependency('glfw3')
dldep = meson.get_compiler('cpp').find_library('dl')

src = ['src/main.cpp','external/glad/src/glad.cpp']

executable('pgm', sources : src, dependencies : [glfwdep,dldep])

