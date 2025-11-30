cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)

project(
        secs
        DESCRIPTION "A simple ecs library written for c++20"
        HOMEPAGE_URL "https://github.com/sleeepyskies/secs"
        LANGUAGES CXX
)
include(GNUInstallDirs)

add_library(secs INTERFACE
        include/Assert.hpp)

target_include_directories(
        secs
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

option(SECS_INCLUDE_HEADERS "Include header files to target" ON)

# make IDE friendly (except clion urgh)
if (SECS_INCLUDE_HEADERS)
    message(STATUS "Including header files in the target")
    set(
            SECS_HEADERS

            include/Component.hpp
            include/ComponentBitMap.hpp
            include/ComponentList.hpp
            include/ComponentManager.hpp
            include/ECSProperties.hpp
            include/EntityHandle.hpp
            include/EntityManager.hpp
            include/Scene.hpp
            include/SingletonManager.hpp
            include/System.hpp
            include/SystemManager.hpp
            include/SystemPhase.hpp
    )

    target_sources(secs INTERFACE ${SECS_HEADERS})
endif ()

# todo: write tests
# tests
option(SECS_ENABLE_TESTS "Enable tests when building" ON)
if (SECS_ENABLE_TESTS)
    enable_testing()
    message(STATUS "Running secs tests")
    add_subdirectory(test)
endif ()

# examples
option(SECS_BUILD_EXAMPLES "Build examples" ON)
if (SECS_BUILD_EXAMPLES)
    message(STATUS "Building examples")
    add_subdirectory(example)
endif ()
