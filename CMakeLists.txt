cmake_minimum_required(VERSION 3.22.4)

project(puppy)

add_executable(${PROJECT_NAME} firstOpenGL.cc)

add_subdirectory(
	external/glfw
	external/glew
)

target_include_directories(${PROJECT_NAME} 
	PUBLIC external/glfw/include
	PUBLIC external/glew/2.2.0_1/include
)

target_link_directories(${PROJECT_NAME}
	PRIVATE external/glfw/src
	PRIVATE external/glew/2.2.0_1
)

target_link_libraries(${PROJECT_NAME}
	glfw
	
)

