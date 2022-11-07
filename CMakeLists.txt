cmake_minimum_required(VERSION 3.10)

project(vaccelrt-plugin-template
	VERSION 0.1
	DESCRIPTION "vAccelRT plugin template"
	LANGUAGES C)

# Export json with compile commands
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
	EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
		${CMAKE_SOURCE_DIR}/compile_commands.json
	)
ENDIF()

set(VACCELRT_INCLUDE
	${CMAKE_SOURCE_DIR}/vaccelrt/src/include
	${CMAKE_SOURCE_DIR}/vaccelrt/third-party/slog/src
	CACHE STRING "Path to vAccel runtime headers")

set(SOURCES
    src/vaccel.c
)

# export rpath for libraries when installing
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_library(vaccel-template SHARED ${SOURCES})
target_compile_features(vaccel-template PUBLIC)
target_include_directories(vaccel-template PRIVATE ${VACCELRT_INCLUDE})
target_link_libraries(vaccel-template)

# Setup `make install`
include(GNUInstallDirs)
install(TARGETS vaccel-template DESTINATION "${CMAKE_INSTALL_LIBDIR}")
