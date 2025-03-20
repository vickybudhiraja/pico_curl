cmake_minimum_required(VERSION 3.13)

# Import Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_curl C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize Pico SDK
pico_sdk_init()

# Define the executable
add_executable(pico_curl hello.c)

# Define CYW43 architecture for Wi-Fi
# add_compile_definitions(PICO_CYW43_ARCH_THREADSAFE_BACKGROUND)
target_include_directories(pico_curl PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Link required libraries
target_link_libraries(pico_curl 
    pico_cyw43_arch_lwip_threadsafe_background
    pico_stdlib
    # pico_cyw43_arch_lwip_threadsafe_background
    # pico_lwip_lwip_default
    # pico_lwip_mbedtls
    # pico_lwip_http
    # hardware_i2c
    # hardware_uart
    # hardware_dma
)

# Include required directories
target_include_directories(pico_curl PRIVATE 
    # ${PICO_SDK_PATH}/src/rp2_common/pico_lwip/include
    # ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_arch/include
    # ${PICO_SDK_PATH}/lib/lwip/src/include
    # ${PICO_SDK_PATH}/lib/cyw43-driver/src
    ${PICO_SDK_PATH}/src/rp2_common/pico_async_context/include

    ${PICO_SDK_PATH}/src/rp2_common/pico_rand/include

    ${PICO_SDK_PATH}/src/rp2_common/pico_lwip/include

    ${PICO_SDK_PATH}/lib/lwip/src/include
    ${PICO_SDK_PATH}/lib/mbedtls/include

    ${PICO_SDK_PATH}/lib/cyw43-driver/src
    ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_driver/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_arch/include

)

# Generate output files
pico_add_extra_outputs(pico_curl)
pico_enable_stdio_usb(pico_curl 1)
pico_enable_stdio_uart(pico_curl 0)

# cmake_minimum_required(VERSION 3.13)

# include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
# # include(${PICO_SDK_PATH})
# include_directories(${PICO_SDK_PATH})
# # include_directories(${PICO_SDK_PATH}/src/common/pico_stdlib_headers/include)
# # include_directories(${PICO_SDK_PATH}/src/common/pico_base_headers/include)

# # include_directories(${CMAKE_SOURCE_DIR})
# # include_directories(${PICO_SDK_PATH}/lib/lwip/src/include)
# # include_directories(${PICO_SDK_PATH}/lib/lwip/src/include/arch)
# # include_directories(${PICO_SDK_PATH}/src/rp2_common/pico_lwip/include)

# # Enable CYW43 Wi-Fi support
# # set(PICO_CYW43_SUPPORTED 1)

# project(pico_curl C CXX ASM)
# set(CMAKE_C_STANDARD 11)
# set(CMAKE_CXX_STANDARD 17)

# # find_package(PkgConfig REQUIRED)
# # pkg_check_modules(CURL REQUIRED libcurl)
# # include_directories(${CURL_INCLUDE_DIRS})
# # link_directories(${CURL_LIBRARY_DIRS})


# add_executable(pico_curl hello.c)
# pico_sdk_init()

# # Define CYW43 architecture
# add_compile_definitions(PICO_CYW43_ARCH_THREADSAFE_BACKGROUND)

# target_include_directories(pico_curl PRIVATE ${CMAKE_CURRENT_LIST_DIR})
# # target_link_libraries(pico_curl pico_cyw43_arch_lwip_poll pico_stdlib )
# target_link_libraries(pico_curl 
#     pico_stdlib 
#     # cyw43_driver_base
#     hardware_i2c
#     pico_cyw43_arch_lwip_threadsafe_background
#     # pico_lwip_http
#     # hardware_adc
#     # freertos
# )
# # add_compile_definitions(PICO_CYW43_ARCH_THREADSAFE_BACKGROUND)

# target_include_directories(pico_curl PRIVATE 

#     ${PICO_SDK_PATH}/src/rp2_common/pico_async_context/include

#     ${PICO_SDK_PATH}/src/rp2_common/pico_rand/include

#     ${PICO_SDK_PATH}/src/rp2_common/pico_lwip/include

#     ${PICO_SDK_PATH}/lib/lwip/src/include
#     ${PICO_SDK_PATH}/lib/cyw43-driver/src
#     ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_driver/include
#     ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_arch/include
# )


# pico_add_extra_outputs(pico_curl)
