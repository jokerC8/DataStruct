project(graph)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

set(${PROJECT_NAME}_SOURCES
        graph.c
        graph_test.c
        ../queue/queue.c
        )

set(${PROJECT_NAME}_HEADERS
        graph.h
        ../queue/queue.h
        )

add_executable(graph
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS})

target_link_libraries(graph)

