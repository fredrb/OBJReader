cmake_minimum_required( VERSION 2.8 )

file( GLOB SOURCES *.cpp )

set(D_LOG_TRACE 0)
set(D_LOG_WARN 1)
set(D_LOG_INFO 1)
set(D_LOG_ERROR 1)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG=1 -DLOG_TRACE=${D_LOG_TRACE} -DLOG_WARN=${D_LOG_WARN} -DLOG_ERROR=${D_LOG_ERROR} -DLOG_INFO=${D_LOG_INFO}")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(MAIN_SOURCES main.cpp File/FileReader.cpp
									GL/Context.cpp GL/ShaderProgram.cpp GL/Window.cpp
									Program/StaticCube.cpp Program/StaticTriangleIndexes.cpp)

set(MAIN_EXE_NAME run)

add_executable( ${MAIN_EXE_NAME} ${MAIN_SOURCES} ${SOURCES} )

find_package(GLEW REQUIRED)

if(GLEW_FOUND)
	target_link_libraries( ${MAIN_EXE_NAME} ${GLEW_LIBRARIES} )
else(GLFW_FOUND)
	message(SEND_ERROR "GLEW not found")
	return()
endif(GLEW_FOUND)

target_link_libraries( ${MAIN_EXE_NAME} glfw GL)
install( TARGETS ${MAIN_EXE_NAME} RUNTIME DESTINATION bin )
