cmake_minimum_required(VERSION 3.15...3.31)
project(secs)

set(CMAKE_CXX_STANDARD 20)

# slog is my own lightweight header only logging library used throughout this project
include(FetchContent)
FetchContent_Declare(
        slog
        GIT_REPOSITORY https://github.com/sleeepyskies/slog.git
        GIT_TAG main
)
FetchContent_MakeAvailable(slog)

add_library(secs INTERFACE
        # Core Data Classes
        secs/Entity.hpp
        secs/ComponentList.hpp

        # Core Logic Classes
        secs/EntityManager.hpp
        secs/ComponentManager.hpp
        secs/SystemManager.hpp
        secs/Scene.hpp

        # Interfaces
        secs/Component.hpp
        secs/System.hpp

        # Util
        secs/secsTypes.hpp
        secs/secsAssert.hpp
        secs/secs.hpp

        # header include file
        secs/secs.hpp
)

target_include_directories(secs INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/secs/include
)

target_include_directories(secs_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/secs/internal
        secs/util
        ${slog_SOURCE_DIR}
)

get_target_property(INCLUDE_DIRS secs INCLUDE_DIRECTORIES)
foreach(DIR ${INCLUDE_DIRS})
    message(STATUS "secs Include directory: ${DIR}")
endforeach()
