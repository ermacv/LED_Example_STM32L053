###############################################################################
# Common complier options
set(compiler_common_flags "")
set(compiler_common_flags "${compiler_common_flags} -fdata-sections")
set(compiler_common_flags "${compiler_common_flags} -ffunction-sections" CACHE INTERNAL "")
###############################################################################
# Common warnings
set(compiler_common_warnings "-Wall")
# set(compiler_common_warnings "${compiler_common_warnings} -pedantic")
set(compiler_common_warnings "${compiler_common_warnings} -Wfatal-errors" CACHE INTERNAL "")
###############################################################################
# C standard
set(PROJECT_C_STD "-std=c99" CACHE INTERNAL "")
###############################################################################
# CXX standard
set(PROJECT_CXX_STD "-std=c++14" CACHE INTERNAL "")
###############################################################################
# Setup C options
###############################################################################
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PROJECT_C_STD}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${compiler_common_flags}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${compiler_common_warnings}")
###############################################################################
# Setup CXX options
###############################################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROJECT_CXX_STD}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compiler_common_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compiler_common_warnings}")
###############################################################################
# Setup ASM options
###############################################################################
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${compiler_common_flags}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${compiler_common_warnings}")
###############################################################################
# Setup Linker options
###############################################################################
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nano.specs" )
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc -lm")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_CURRENT_SOURCE_DIR}/STM32L053C8Tx_FLASH.ld")
###############################################################################
