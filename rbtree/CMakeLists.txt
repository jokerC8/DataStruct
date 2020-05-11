project(rbtree)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

set(${PROJECT_NAME}_SOURCES
        rbtree.c
        rbtree_test.c
        )

set(${PROJECT_NAME}_HEADERS
        rbtree.h
        )

add_executable(rbtree
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS})

target_link_libraries(rbtree)

