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
        secs/IComponentList.hpp

        # Core Logic Classes
        secs/EntityManager.hpp
        secs/ComponentManager.hpp
        secs/SystemManager.hpp
        secs/Scene.hpp

        # Components
        secs/components/Component.hpp
        secs/components/TextureComponent.hpp
        secs/components/TransformComponent.hpp

        # Systems
        secs/systems/RenderSystem.hpp

        # Util
        secs/util/secsTypes.hpp
        secs/util/secsAssert.hpp
)

target_include_directories(
        secs INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/secs
        ${CMAKE_CURRENT_SOURCE_DIR}/secs/components
        ${CMAKE_CURRENT_SOURCE_DIR}/secs/systems
        ${CMAKE_CURRENT_SOURCE_DIR}/secs/util
)

target_include_directories(secs INTERFACE ${slog_SOURCE_DIR})
