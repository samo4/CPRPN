cmake_minimum_required(VERSION 3.16)
project(cprpn_mockup LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# ---------------------------------------------------------------------------
# u8g2 — display library with built-in SDL2 simulation port
# ---------------------------------------------------------------------------
FetchContent_Declare(
    u8g2
    GIT_REPOSITORY https://github.com/olikraus/u8g2.git
    GIT_TAG master
)
FetchContent_MakeAvailable(u8g2)

file(GLOB U8G2_SRCS ${u8g2_SOURCE_DIR}/csrc/*.c)
list(APPEND U8G2_SRCS
    ${u8g2_SOURCE_DIR}/sys/sdl/common/u8x8_d_sdl_128x64.c
    ${u8g2_SOURCE_DIR}/sys/sdl/common/u8x8_sdl_key.c
)

# ---------------------------------------------------------------------------
# SDL2 (via vcpkg)
# ---------------------------------------------------------------------------
find_package(SDL2 CONFIG REQUIRED)

# ---------------------------------------------------------------------------
# Executable
# ---------------------------------------------------------------------------
add_executable(cprpn_mockup main.c ${U8G2_SRCS})

target_include_directories(cprpn_mockup PRIVATE
    ${u8g2_SOURCE_DIR}/csrc
    ${u8g2_SOURCE_DIR}/sys/sdl/common
)

target_link_libraries(cprpn_mockup PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

# ---------------------------------------------------------------------------
# IBM decNumber library (local copy in firmware/lib/decNumberICU)
# ---------------------------------------------------------------------------
# decBasic.c and decCommon.c are #included internally by decDouble/Quad/Single — do NOT compile them directly
file(GLOB DECNUMBER_SRCS ${CMAKE_SOURCE_DIR}/../lib/decNumberICU/*.c)
list(REMOVE_ITEM DECNUMBER_SRCS
    ${CMAKE_SOURCE_DIR}/../lib/decNumberICU/decBasic.c
    ${CMAKE_SOURCE_DIR}/../lib/decNumberICU/decCommon.c
)
target_sources(cprpn_mockup PRIVATE ${DECNUMBER_SRCS})
target_include_directories(cprpn_mockup PRIVATE ${CMAKE_SOURCE_DIR}/../lib/decNumberICU)

# ---------------------------------------------------------------------------
# GMP (via vcpkg — headers+lib have no CMake config, link directly)
# ---------------------------------------------------------------------------
find_path(GMP_INCLUDE_DIR gmp.h REQUIRED)
find_library(GMP_LIBRARY NAMES gmp REQUIRED)
target_include_directories(cprpn_mockup PRIVATE ${GMP_INCLUDE_DIR})
target_link_libraries(cprpn_mockup PRIVATE ${GMP_LIBRARY})

# ---------------------------------------------------------------------------
# C47 sources
# ---------------------------------------------------------------------------
file(GLOB_RECURSE C47_SRCS ${CMAKE_SOURCE_DIR}/../src/c47/*.c)
target_sources(cprpn_mockup PRIVATE ${C47_SRCS})
target_include_directories(cprpn_mockup PRIVATE ${CMAKE_SOURCE_DIR}/../src/c47)

# Simulation build defines
# definetly not PC_BUILD: it has inclusions for GTK all over the place. we need to make it work with DMCP_BUILD
target_compile_definitions(cprpn_mockup PRIVATE
    DMCP_BUILD
    OS64BIT
)
