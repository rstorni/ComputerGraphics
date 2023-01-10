cmake_minimum_required(VERSION 3.22.4)

project(DrawVertex)

add_executable(${PROJECT_NAME} draw2Triangles.cc external/glad/src/glad.c)

add_subdirectory(
	external/glfw
)

target_include_directories(${PROJECT_NAME} 
	PUBLIC external/glfw/include
	PUBLIC external/glad/include
)

target_link_directories(${PROJECT_NAME}
	PRIVATE external/glfw/src
	PRIVATE external/glad/src
)

target_link_libraries(${PROJECT_NAME}
	glfw
)

