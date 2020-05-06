project(list)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

set(${PROJECT_NAME}_SOURCES
        list_test.c
        )

set(${PROJECT_NAME}_HEADERS
        list.h
        kfifo.h
        )

add_executable(list
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS})

target_link_libraries(list)

