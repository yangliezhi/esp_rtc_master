# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/ESP32_IDF/ESP32_5.2/v5.2.1/esp-idf/components/bootloader/subproject"
  "D:/git/door_bell/esp32-s3_rtc/adf_example/protocols/esp-rtc/build/bootloader"
  "D:/git/door_bell/esp32-s3_rtc/adf_example/protocols/esp-rtc/build/bootloader-prefix"
  "D:/git/door_bell/esp32-s3_rtc/adf_example/protocols/esp-rtc/build/bootloader-prefix/tmp"
  "D:/git/door_bell/esp32-s3_rtc/adf_example/protocols/esp-rtc/build/bootloader-prefix/src/bootloader-stamp"
  "D:/git/door_bell/esp32-s3_rtc/adf_example/protocols/esp-rtc/build/bootloader-prefix/src"
  "D:/git/door_bell/esp32-s3_rtc/adf_example/protocols/esp-rtc/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/git/door_bell/esp32-s3_rtc/adf_example/protocols/esp-rtc/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/git/door_bell/esp32-s3_rtc/adf_example/protocols/esp-rtc/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
