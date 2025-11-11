cmake_minimum_required(VERSION 3.20)
project(ch32v00x_projects C ASM)

set(PROJECT "" CACHE STRING "Project to build (subdir of projects)")
if(PROJECT STREQUAL "")
  message(FATAL_ERROR "Set -DPROJECT=<name>, ex: -DPROJECT=gpio")
endif()

# Output per-example
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# Toolchain
if(NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/riscv-none-embed.cmake" CACHE FILEPATH "" FORCE)
endif()

# ----- Sources -----
set(SRC_CORE        ${CMAKE_SOURCE_DIR}/drivers/core/core_riscv.c)
set(SRC_DEBUG       ${CMAKE_SOURCE_DIR}/debug/debug.c)
file(GLOB SRC_HAL   ${CMAKE_SOURCE_DIR}/drivers/ch32v00x-hal/src/*.c)

set(PRJ_DIR ${CMAKE_SOURCE_DIR}/projects/${PROJECT})
if(NOT EXISTS "${PRJ_DIR}/main.c")
  message(FATAL_ERROR "Not found projects/${PROJECT}/main.c")
endif()
file(GLOB SRC_PROJECT CONFIGURE_DEPENDS
    "${PRJ_DIR}/*.c"
)

set(SRC_STARTUP ${CMAKE_SOURCE_DIR}/drivers/device/startup/startup_ch32v00x.S)

set(TARGET_NAME ${PROJECT})
add_executable(${TARGET_NAME}
  ${SRC_CORE}
  ${SRC_DEBUG}
  ${SRC_HAL}
  ${SRC_PROJECT}
  ${SRC_STARTUP}
)

option(USE_BOOT_APP_LD "Use split boot/app linker scripts" OFF)

set(LD_DEFAULT ${CMAKE_SOURCE_DIR}/drivers/device/ld/default.ld)
set(LD_BOOT    ${CMAKE_SOURCE_DIR}/drivers/device/ld/boot.ld)
set(LD_APP     ${CMAKE_SOURCE_DIR}/drivers/device/ld/app.ld)

set(LINKER_SCRIPT ${LD_DEFAULT})

if(USE_BOOT_APP_LD)
  if(PROJECT STREQUAL "bootloader")
    set(LINKER_SCRIPT ${LD_BOOT})
    add_compile_definitions(BUILD_BL)
  else()
    set(LINKER_SCRIPT ${LD_APP})
    add_compile_definitions(BUILD_APP)
  endif()
endif()
message(STATUS "Using linker script: ${LINKER_SCRIPT}")

target_include_directories(${TARGET_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/debug
  ${CMAKE_SOURCE_DIR}/drivers/core
  ${CMAKE_SOURCE_DIR}/drivers/device
  ${CMAKE_SOURCE_DIR}/drivers/ch32v00x-hal/inc
  ${PRJ_DIR}
)

target_compile_definitions(${TARGET_NAME} PRIVATE
  HAL_USE_FULL_ASSERT
)

target_link_options(${TARGET_NAME} PRIVATE
  -Wl,--gc-sections
  -Wl,-Map,$<TARGET_FILE_DIR:${TARGET_NAME}>/${TARGET_NAME}.map
  -T${LINKER_SCRIPT}
  -nostartfiles
  -nostdlib
  -specs=nano.specs
)

target_link_libraries(${TARGET_NAME} PRIVATE
  -Wl,--start-group
  c m gcc nosys
  -Wl,--end-group
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O ihex  $<TARGET_FILE:${TARGET_NAME}> $<TARGET_FILE_DIR:${TARGET_NAME}>/${TARGET_NAME}.hex
  COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${TARGET_NAME}> $<TARGET_FILE_DIR:${TARGET_NAME}>/${TARGET_NAME}.bin
  COMMENT "Generating HEX and BIN"
)
