project(queue)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

set(${PROJECT_NAME}_SOURCES
        queue.c
        queue_test.c
        )

set(${PROJECT_NAME}_HEADERS
        queue.h
        )

add_executable(queue
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS})

target_link_libraries(queue)

