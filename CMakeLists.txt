cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Stm32-Driver-Library)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
        Utils/Delay/Delay.c
        Utils/IIC/I2C.c
        Utils/Interrupt/Interrupt.c
        Utils/SPI/SPI.c
        Utils/USART/USART.c
        Utils/Timer/Timer.c
        Libs/AHT20/AHT20.c
        Libs/BH1750/BH1750.c
        Libs/BMP280/BMP280.h
        Libs/GP10/GP10.c
        Libs/MPU6050/MPU6050.c
        Libs/OLCD/OLED.c
        Libs/OLCD/OLED_Data.c
        Libs/OLCD/OLED_Menu.c
        Libs/W25Q64/W25Q64.c

        Libs/TFTLCD/Graphics/font.c
        Libs/TFTLCD/Driver/lcd_dma.c
        Libs/TFTLCD/Graphics/lcd_str.c
        Libs/TFTLCD/Graphics/lcd_graphics.c
        Libs/TFTLCD/Driver/lcd_cmd.c
        Libs/TFTLCD/Driver/lcd_gpio.c
        Demo/Src/demo.c
        Demo/Src/demo_lcd.c
        Utils/SPI/SPI1.c
        Libs/TFTLCD/UI/LCD_Box.c
        Libs/TFTLCD/UI/LCD_Box.h
        Libs/TFTLCD/UI/LCD_Draw.c
        Libs/TFTLCD/UI/LCD_Draw.h
        Libs/WS2812/WS2812.c
        Demo/Src/demo_ws2812.c
        Demo/Inc/demo_ws2812.h
)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
        Demo/Inc
        Utils/IIC
        Utils/SPI
        Utils/USART
        Utils/Interrupt
        Utils/Timer
        Utils/Delay
        Libs/GP10
        Libs/OLCD
        Libs/BH1750
        Libs/AHT20
        Libs/BMP280
        Libs/W25Q64
        Libs/MPU6050
        Libs/TFTLCD/Driver
        Libs/TFTLCD/Graphics
        Libs/TFTLCD/UI
        Libs/WS2812
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
