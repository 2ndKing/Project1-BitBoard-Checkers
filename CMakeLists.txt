cmake_minimum_required(VERSION 3.10)

project(BitBoardCheckers
        VERSION 1.0
        DESCRIPTION "CS3503 Project 1 - BitBoard Checkers (C)"
        LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()


set(SOURCES
        main.c
        bitops.c
        board.c
        game.c
        bitops.c
)

set(HEADERS
        bitops.h
        board.h
        game.h
        bitops.c
)


add_executable(bitboard_checkers ${SOURCES} ${HEADERS}
        bitops.c)


set_target_properties(bitboard_checkers PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)


option(DEBUG_PRINT "Enable extra debug printing" OFF)

if (DEBUG_PRINT)
    target_compile_definitions(bitboard_checkers PRIVATE DEBUG_PRINT)
endif()

message(STATUS "----------------------------------------")
message(STATUS "BitBoard Checkers build configuration:")
message(STATUS "  Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C Standard: ${CMAKE_C_STANDARD}")
message(STATUS "  Output file: ${CMAKE_SOURCE_DIR}/bitboard_checkers")
message(STATUS "----------------------------------------")
