###############################################################################
# Minimal CMake version that is needed to process current project
cmake_minimum_required(VERSION 3.6)
###############################################################################
###############################################################################
# Languages that are used in the project
enable_language(ASM)
enable_language(C)
###############################################################################
# Main project name
project(CMSIS)
###############################################################################

add_library(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32L0xx/Include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include)
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Core/Src/system_stm32l0xx.c)
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/startup_stm32l053xx.s)
target_compile_definitions(${PROJECT_NAME} PUBLIC
    STM32L053xx
    USE_FULL_LL_DRIVER
    HSE_VALUE=8000000
    LSE_VALUE=32768
    MSI_VALUE=2097000
    HSI_VALUE=16000000
    LSI_VALUE=37000
)
###############################################################################
