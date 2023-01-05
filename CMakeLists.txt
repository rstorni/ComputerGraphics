cmake_minimum_required(VERSION 3.22.4)

project(puppy)

add_executable(${PROJECT_NAME} firstOpenGL.cc)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
	PUBLIC external/glfw/include
)

target_link_directories(${PROJECT_NAME}
	PRIVATE external/glfw/src
)

target_link_libraries(${PROJECT_NAME}
	glfw
)

find_package(GLEW 2.0 REQUIRED)
target_link_libraries(Starting GLEW::GLEW)
