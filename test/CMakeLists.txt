add_executable(secs_test secs.cpp)

target_include_directories(secs_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(secs_test PRIVATE secs)

add_test(NAME secs_test COMMAND secs_test)
