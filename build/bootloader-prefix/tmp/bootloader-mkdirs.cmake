# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/grigoriew/Applications/esp/esp-idf/components/bootloader/subproject"
  "/home/grigoriew/Programs/esp32_dev/oled_clock/build/bootloader"
  "/home/grigoriew/Programs/esp32_dev/oled_clock/build/bootloader-prefix"
  "/home/grigoriew/Programs/esp32_dev/oled_clock/build/bootloader-prefix/tmp"
  "/home/grigoriew/Programs/esp32_dev/oled_clock/build/bootloader-prefix/src/bootloader-stamp"
  "/home/grigoriew/Programs/esp32_dev/oled_clock/build/bootloader-prefix/src"
  "/home/grigoriew/Programs/esp32_dev/oled_clock/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/grigoriew/Programs/esp32_dev/oled_clock/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/grigoriew/Programs/esp32_dev/oled_clock/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
