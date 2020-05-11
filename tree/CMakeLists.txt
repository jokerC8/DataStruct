project(tree)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

set(${PROJECT_NAME}_SOURCES
        tree.c
        tree_test.c
        )

set(${PROJECT_NAME}_HEADERS
        tree.h
        )

add_executable(tree
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS})

target_link_libraries(tree)

