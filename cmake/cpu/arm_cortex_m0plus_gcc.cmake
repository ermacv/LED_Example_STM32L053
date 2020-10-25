###############################################################################
# ARM Cortex-M0+ and soft float point ABI options for GCC compiler
###############################################################################
# Check the link below to get a description for ARM specific options:
# https://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html
###############################################################################
set(USER_CPU_OPTIONS "-march=armv6-m")
set(USER_CPU_OPTIONS "${USER_CPU_OPTIONS} -mlittle-endian")
set(USER_CPU_OPTIONS "${USER_CPU_OPTIONS} -mcpu=cortex-m0plus")
set(USER_CPU_OPTIONS "${USER_CPU_OPTIONS} -mthumb")
set(USER_CPU_OPTIONS "${USER_CPU_OPTIONS} -mfloat-abi=soft")
set(USER_CPU_OPTIONS "${USER_CPU_OPTIONS} -mapcs-frame" CACHE INTERNAL "")
###############################################################################
# By providing ISA, CPU architecture version, FPU HW version and FPU ABI type
# to the GCC it may include default C system libraries (newlib-nano) automatically
# by using milti-lib option (check arm-none-eabi-gcc --print-multi-lib)
###############################################################################
# Setup C options
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USER_CPU_OPTIONS}")
###############################################################################
# Setup CXX options
###############################################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USER_CPU_OPTIONS}")
###############################################################################
# Setup ASM options
###############################################################################
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${USER_CPU_OPTIONS}")
###############################################################################
# Setup Linker options
###############################################################################
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USER_CPU_OPTIONS}")
# We don't need to set linker flags explicitly because by default CMake uses
# GCC that invokes LD and all GCC flags will be set explicitly to LD
###############################################################################