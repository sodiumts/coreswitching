# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 4.2)
# Generated Cmake Pico project file
set(PICO_PLATFORM rp2350)
set(PICO_BOARD pico2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(pico_sdk_import.cmake)

project(armside C CXX ASM)

pico_sdk_init()

add_executable(armside main.c )

target_link_libraries(armside
        pico_stdlib)

target_include_directories(armside PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_enable_stdio_usb(armside 1)
pico_enable_stdio_uart(armside 0)

pico_add_extra_outputs(armside)

