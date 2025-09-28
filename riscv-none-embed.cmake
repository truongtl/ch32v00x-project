set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv32)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Toolchain
set(TRIPLET riscv-none-embed)
set(CMAKE_C_COMPILER   ${TRIPLET}-gcc)
set(CMAKE_ASM_COMPILER ${TRIPLET}-gcc)
set(CMAKE_AR           ${TRIPLET}-ar)
set(CMAKE_OBJCOPY      ${TRIPLET}-objcopy)
set(CMAKE_OBJDUMP      ${TRIPLET}-objdump)
set(CMAKE_SIZE         ${TRIPLET}-size)

# CPU flags
set(CPU_FLAGS "-march=rv32ec -mabi=ilp32e -mcmodel=medlow")

# Compile flags
set(CMAKE_C_FLAGS_INIT   "${CPU_FLAGS} -ffunction-sections -fdata-sections -fno-builtin -fno-common -Os")
set(CMAKE_ASM_FLAGS_INIT "${CPU_FLAGS} -x assembler-with-cpp")

# Linker flags init
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CPU_FLAGS}")

# set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -specs=nosys.specs")
