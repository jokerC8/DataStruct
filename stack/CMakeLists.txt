project(stack)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

set(${PROJECT_NAME}_SOURCES
        stack.c
        stack_test.c
        )

set(${PROJECT_NAME}_HEADERS
        stack.h
        )

add_executable(stack
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS})

target_link_libraries(stack)

