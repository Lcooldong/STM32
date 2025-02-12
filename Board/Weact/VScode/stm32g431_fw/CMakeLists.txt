cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools")
include(arm-none-eabi-gcc)

set(PRJ_NAME stm32g431_fw)

project(${PRJ_NAME}
    LANGUAGES  ASM C CXX
)

set(EXECUTABLE ${PRJ_NAME}.elf)

file(GLOB SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
    src/bsp/*.c
    src/bsp/device/*.c
    
    
)

file(GLOB_RECURSE SRC_FILES_RECURSE CONFIGURE_DEPENDS
  src/ap/*.cpp
  src/ap/*.c
  src/bsp/*.s
  src/common/*.c
  src/hw/*.c
  src/lib/STM32H7xx_HAL_Driver/Src/*.c
)

# 특정 폴더를 빌드에서 제외한다.
#
set(EXCLUDE_PATHS 
  "src/ap/touch-gfx/build"
  "src/ap/touch-gfx/simulator"
  "src/ap/touch-gfx/generated/simulator"
)

foreach(TMP_PATH ${SRC_FILES_RECURSE}) 
  foreach(EXCLUDE_PATH ${EXCLUDE_PATHS}) 
    string(FIND ${TMP_PATH} ${EXCLUDE_PATH} RESULT) 
    if(NOT ${RESULT} EQUAL -1) 
      list(REMOVE_ITEM SRC_FILES_RECURSE ${TMP_PATH}) 
    endif() 
  endforeach(EXCLUDE_PATH) 
endforeach(TMP_PATH)







add_executable(${EXECUTABLE} 
  ${SRC_FILES}
  ${SRC_FILES_RECURSE}

  
)


target_include_directories(${EXECUTABLE} PRIVATE 
  src  
  src/ap
#   src/ap/thread
#   src/bsp
#   src/bsp/device
#   src/bsp/rtos
#   src/common 
#   src/common/core
#   src/common/hw/include 
#   src/hw
#   src/hw/driver
#   src/hw/driver/fatfs
#   src/hw/driver/usb
#   src/hw/driver/usb/usb_cdc
#   src/hw/driver/usb/usb_msc
#   src/lib

#   src/lib/CMSIS/Include
#   src/lib/CMSIS/Device/ST/STM32H7xx/Include
#   src/lib/CMSIS/DSP/Include
#   src/lib/STM32H7xx_HAL_Driver/Inc
#   src/lib/FatFs/src
#   src/lib/STM32_USB_Device_Library/Core/Inc

)

target_compile_definitions(${EXECUTABLE} PRIVATE
#   -DSTM32H723xx 
#   -DLFS_THREADSAFE
#   -D__PV_LANGUAGE_KOREAN__
  )

target_compile_options(${EXECUTABLE} PRIVATE
  -mcpu=cortex-g4
  -mthumb
  -mfpu=fpv5-d16 
  -mfloat-abi=hard

  -fdata-sections
  -ffunction-sections

  -Wall
  -g3
  -Og
  )

target_link_options(${EXECUTABLE} PRIVATE
   -T../src/bsp/ldscript/STM32G431CBUX_FLASH.ld
#   # -T../src/bsp/ldscript/STM32G431CBUX_BOOT.ld
   -mcpu=cortex-g4
   -mthumb
   -mfpu=fpv5-d16 
   -mfloat-abi=hard
   -specs=nano.specs
   -lc
   -lm
   -lstdc++
   -lsupc++
   -fno-rtti
   #-lnosys
   -Wl,-Map=${PRJ_NAME}.map,--cref
   -Wl,--gc-sections
   -Xlinker -print-memory-usage -Xlinker
  )


set (CMAKE_CXX_FLAGS "-fno-rtti")

target_link_libraries( ${EXECUTABLE} PRIVATE

  )



add_custom_command(TARGET ${EXECUTABLE} 
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
    COMMENT "Invoking: Make Binary"
    # COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE}.elf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex
    # COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE}.elf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin
)