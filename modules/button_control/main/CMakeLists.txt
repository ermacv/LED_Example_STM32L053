###############################################################################
# Minimal CMake version that is needed to process current project
cmake_minimum_required(VERSION 3.6)
###############################################################################
###############################################################################
# Languages that are used in the project
enable_language(C)
###############################################################################
# Main project name
project(Button_Control)
###############################################################################

add_library(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/button_control.c)
target_link_libraries(${PROJECT_NAME} PRIVATE STM32_LL)
target_link_libraries(${PROJECT_NAME} PRIVATE Button_Driver)
target_link_libraries(${PROJECT_NAME} PRIVATE LED_Control)
###############################################################################
