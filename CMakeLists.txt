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
        secs/include/secs/Entity.hpp
        secs/internal/IComponentList.hpp

        # Core Logic Classes
        secs/internal/EntityManager.hpp
        secs/internal/ComponentManager.hpp
        secs/internal/SystemManager.hpp
        secs/include/secs/Scene.hpp

        # Interfaces
        secs/include/secs/Component.hpp
        secs/include/secs/System.hpp

        # Util
        secs/internal/util/secsTypes.hpp
        secs/internal/util/secsAssert.hpp
        secs/include/secs/InputData.hpp
)

target_include_directories(
        secs INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/secs
        ${CMAKE_CURRENT_SOURCE_DIR}/secs/components
        ${CMAKE_CURRENT_SOURCE_DIR}/secs/systems
        secs/internal/util
)

target_include_directories(secs INTERFACE ${slog_SOURCE_DIR})
