set(INCLUDE_DIRS
    include
)

set(SOURCES
	src/Board.cpp
	src/SolveResult.cpp
)

include_directories(${INCLUDE_DIRS})

add_library(engine ${SOURCES})