###############################################################################
#CPU setup
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
# There is a CMAKE_CROSSCOMPILING variable. Checking this variable CMake can
# understand what compiler is used and what is a target platform
# You don't need to set this variable you set CMAKE_SYSTEM_NAME and CMAKE_SYSTEM_PROCESSOR
# that are differs from a current host system (it sets automatically)
###############################################################################
# Project preconditions
include(${CMAKE_CURRENT_LIST_DIR}/GNU_Arm_Embedded_Toolchain_conf.cmake)
###############################################################################
# Set compiler binutils
set(CMAKE_C_COMPILER "${COMPILER_BIN}${TARGET_TRIPLET}-gcc${COMPILER_EXE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_ASM_COMPILER "${COMPILER_BIN}${TARGET_TRIPLET}-gcc${COMPILER_EXE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER "${COMPILER_BIN}${TARGET_TRIPLET}-g++${COMPILER_EXE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_OBJCOPY "${COMPILER_BIN}${TARGET_TRIPLET}-objcopy${COMPILER_EXE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_SIZE "${COMPILER_BIN}${TARGET_TRIPLET}-size${COMPILER_EXE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_OBJDUMP "${COMPILER_BIN}${TARGET_TRIPLET}-objdump${COMPILER_EXE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_LINKER "${COMPILER_BIN}${TARGET_TRIPLET}-ld${COMPILER_EXE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_RANLIB "${COMPILER_BIN}${TARGET_TRIPLET}-ranlib${COMPILER_EXE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_AR "${COMPILER_BIN}${TARGET_TRIPLET}-ar${COMPILER_EXE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_NM "${COMPILER_BIN}${TARGET_TRIPLET}-nm${COMPILER_EXE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_STRIP "${COMPILER_BIN}${TARGET_TRIPLET}-strip${COMPILER_EXE_EXTENSION}" CACHE INTERNAL "")
###############################################################################
# CMake compiles a lib before building a project
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
###############################################################################