set(ENGINE_BASE_DIR "${PROJECT_SOURCE_DIR}/engine")

set(INCLUDE_DIRS
    include
	${ENGINE_BASE_DIR}/include
)

set(SOURCES
	src/Main.cpp
)

include_directories(${INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries( ${PROJECT_NAME} engine)

if(EXISTS ${CMAKE_SOURCE_DIR}/content)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()
