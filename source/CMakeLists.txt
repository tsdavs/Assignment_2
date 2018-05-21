# CMakeLists.txt from SILENT HILL 3 Redux by Palm Studios
# Copyright 2016-2018 Alexander Hirsch and Jesse Buhagiar

find_package(GLU REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories("../include")
include_directories(SYSTEM "${GLUT_INCLUDE_DIR}")
include_directories(SYSTEM "${OPENGL_INCLUDE_DIR}")


add_executable("${CMAKE_PROJECT_NAME}"

    "euclidean2/main.cpp"

	"euclidean2/system/engine.cpp"
	"euclidean2/system/window.cpp"
    "euclidean2/system/text.cpp"
    "euclidean2/system/light.cpp"
    "euclidean2/system/material.cpp"
    "euclidean2/system/texture.cpp"
    "euclidean2/system/skybox.cpp"

    "euclidean2/math/vec2.cpp"
    "euclidean2/math/vec3.cpp"
    "euclidean2/math/e_math.cpp"

    "euclidean2/camera/camera.cpp"

    "euclidean2/object/water.cpp"
	"euclidean2/object/boat.cpp"
)

target_link_libraries("${CMAKE_PROJECT_NAME}"

    PRIVATE "${OPENGL_LIBRARIES}"
    PRIVATE "${GLU_LIBRARIES}"
    PRIVATE "${GLUT_LIBRARIES}"
    PRIVATE "SOIL"
    PRIVATE "m"
)

