# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT components/wifi_connect)
set(EXTRA_COMPONENT components/ssd1306_driver)
set(EXTRA_COMPONENT components/timesync)
set(EXTRA_COMPONENT components/display_control)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(oled_clock)
