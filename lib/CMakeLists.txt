# Library build options.
option(ASSIMP_BUILD_TESTS OFF)
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(OPTION_BUILD_TESTS OFF)

# Build libraries.
string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Disable compiler warnings.
add_compile_options(
    # Clang
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Wno-everything>
    # GCC
    $<$<CXX_COMPILER_ID:GNU>:-w>
    # Visual Studio
    $<$<CXX_COMPILER_ID:MSVC>:/W0>
)


add_subdirectory(glm)
add_subdirectory(glad)
add_subdirectory(luabridge)
add_subdirectory(react)
set(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(assimp)
# add_subdirectory(imgui)
add_subdirectory(lua)
set(SDL_STATIC OFF)
set(SDL_DYNAMIC ON)
set(SDL_SHARED ON)
set(BUILD_SHARED_LIBS ON)
add_subdirectory(sdl2)
add_subdirectory(imgui)

# DLL's were a mistake.
set_target_properties(reactphysics3d PROPERTIES ENABLE_EXPORTS ON)
set_target_properties(reactphysics3d PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Puts a stop to the endlessly irritating practise postfixing 'd' onto debug libraries.
set_target_properties(assimp PROPERTIES DEBUG_POSTFIX "")
set_target_properties(glad PROPERTIES DEBUG_POSTFIX "")
set_target_properties(reactphysics3d PROPERTIES DEBUG_POSTFIX "")
set_target_properties(SDL2 PROPERTIES DEBUG_POSTFIX "")
set_target_properties(SDL2main PROPERTIES DEBUG_POSTFIX "")

# Ignore warnings from library headers.
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    sdl2/include
    sdl2/src
    assimp/include
    react/src
    glad/include
    lua/src
    luabridge/Source
)

#target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES})

# Libraries for Win32 native and MinGW
# list(APPEND EXTRA_LIBS user32 gdi32 winmm imm32 ole32 oleaut32 version uuid advapi32 shell32)