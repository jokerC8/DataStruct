project(avltree)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

set(${PROJECT_NAME}_SOURCES
        avltree.c
        avltree_test.c
        )

set(${PROJECT_NAME}_HEADERS
        avltree.h
        )

add_executable(avltree
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS})

target_link_libraries(avltree)

