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

add_library(secs STATIC
        src/ComponentManager.hpp
        src/ecs.hpp
        src/Entity.hpp
        src/EntityManager.cpp
        src/EntityManager.hpp
        src/IComponentList.hpp
        src/Scene.hpp
        src/SystemManager.hpp
        src/systems/RenderSystem.hpp
        src/components/IComponent.hpp
        src/components/TextureComponent.hpp
        src/components/TransformComponent.hpp
        src/util/types.hpp
        src/util/types.hpp
)

target_include_directories(secs PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/components
        ${CMAKE_CURRENT_SOURCE_DIR}/src/systems
        ${CMAKE_CURRENT_SOURCE_DIR}/src/util
)

target_include_directories(secs PRIVATE ${slog_SOURCE_DIR})
