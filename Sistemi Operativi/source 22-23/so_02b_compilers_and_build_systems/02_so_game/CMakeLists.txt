cmake_minimum_required (VERSION 2.8.11)
project (so_game)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(so_game helpers.c  image.c  so_game.c  surface.c  vec3.c  vehicle.c  world.c)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(so_game
  ${OPENGL_gl_LIBRARY}
  ${OPENGL_glu_LIBRARY}
  ${GLUT_glut_LIBRARY}
  m
  )


