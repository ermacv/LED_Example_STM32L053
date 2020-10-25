###############################################################################
# Minimal CMake version that is needed to process current project
cmake_minimum_required(VERSION 3.6)
###############################################################################
###############################################################################
# Languages that are used in the project
enable_language(C)
###############################################################################
# Main project name
project(application)
###############################################################################
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/main.c)
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/stm32l0xx_it.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/inc)
target_link_libraries(${PROJECT_NAME} PRIVATE STM32_LL)
target_link_libraries(${PROJECT_NAME} PRIVATE CMSIS_STM32L053)
target_link_libraries(${PROJECT_NAME} PRIVATE LED_Control)
target_link_libraries(${PROJECT_NAME} PRIVATE Button_Control)
target_link_libraries(${PROJECT_NAME} PRIVATE Button_Driver)
###############################################################################
