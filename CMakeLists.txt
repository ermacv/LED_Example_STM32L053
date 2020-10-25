###############################################################################
# Minimal CMake version that is needed to process current project
cmake_minimum_required(VERSION 3.6)
###############################################################################
# CMake specific options that should be enabled before processing the project
# Must be enabled before project()
set(CMAKE_TOOLCHAIN_FILE ${PROJECT_SOURCE_DIR}/cmake/toolchain/GNU_Arm_Embedded_Toolchain.cmake)
###############################################################################
# Languages that are used in the project
enable_language(C)
###############################################################################
# Main project name
project(Woodenshark_Test)
###############################################################################
# Include CPU specific biuld options
include(${PROJECT_SOURCE_DIR}/cmake/cpu/arm_cortex_m0plus_gcc.cmake)
# Include build options for different build types (Debug, Release, etc.)
include(${PROJECT_SOURCE_DIR}/cmake/build_common/build_types.cmake)
# Include common build options that should ne used by all project modules and libraries
include(${PROJECT_SOURCE_DIR}/cmake/build_common/build_options.cmake)
###############################################################################
add_subdirectory(${PROJECT_SOURCE_DIR}/cmake/libs/cmsis)
add_subdirectory(${PROJECT_SOURCE_DIR}/cmake/libs/stm32_ll)
add_subdirectory(${PROJECT_SOURCE_DIR}/modules/system)
###############################################################################
add_executable(${CMAKE_PROJECT_NAME})
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/modules/application/src/main.c)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/modules/application/src/stm32l0xx_it.c)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/modules/application/inc)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE STM32_LL)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE CMSIS_STM32L053)
###############################################################################
