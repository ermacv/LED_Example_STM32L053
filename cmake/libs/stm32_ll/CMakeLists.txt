###############################################################################
# Minimal CMake version that is needed to process current project
cmake_minimum_required(VERSION 3.6)
###############################################################################
###############################################################################
# Languages that are used in the project
enable_language(C)
###############################################################################
# Main project name
project(STM32_LL)
###############################################################################

add_library(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Inc)
target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_adc.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_comp.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_crc.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_crs.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dac.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_i2c.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lptim.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lpuart.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rng.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rtc.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_spi.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_tim.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_usart.c
    # ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_usb.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.c
)
target_link_libraries(${PROJECT_NAME} PUBLIC CMSIS_STM32L053)

###############################################################################
