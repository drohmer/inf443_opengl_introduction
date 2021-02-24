project('01_minimal_window', 'cpp')
cxxflags = ['-O2','-g','-std=c++11','-Wall','-Wextra']
add_global_arguments(cxxflags, language : 'cpp')
glfwdep = dependency('glfw3')
executable('pgm', 'src/main.cpp', dependencies : glfwdep)

