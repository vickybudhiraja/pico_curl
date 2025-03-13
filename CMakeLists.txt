cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
# include(${PICO_SDK_PATH})
include_directories(${PICO_SDK_PATH})
include_directories(${PICO_SDK_PATH}/src/common/pico_stdlib_headers/include)
include_directories(${PICO_SDK_PATH}/src/common/pico_base_headers/include)

include_directories(${CMAKE_SOURCE_DIR})
# include_directories(${PICO_SDK_PATH}/lib/lwip/src/include)
# include_directories(${PICO_SDK_PATH}/lib/lwip/src/include/arch)
# include_directories(${PICO_SDK_PATH}/src/rp2_common/pico_lwip/include)

# Enable CYW43 Wi-Fi support
# set(PICO_CYW43_SUPPORTED 1)

project(pico_curl C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# find_package(PkgConfig REQUIRED)
# pkg_check_modules(CURL REQUIRED libcurl)
# include_directories(${CURL_INCLUDE_DIRS})
# link_directories(${CURL_LIBRARY_DIRS})


add_executable(pico_curl hello.c)

target_link_libraries(pico_curl pico_cyw43_arch_none)

pico_sdk_init()

pico_add_extra_outputs(pico_curl)
