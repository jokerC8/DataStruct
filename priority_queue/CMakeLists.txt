project(priority_queue)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

set(${PROJECT_NAME}_SOURCES
        priority_queue.c
        priority_queue_test.c
        )

set(${PROJECT_NAME}_HEADERS
        priority_queue.h
        )

add_executable(priority_queue
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS})

target_link_libraries(priority_queue)

