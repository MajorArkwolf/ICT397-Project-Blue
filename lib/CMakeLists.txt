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
add_subdirectory(lua)
add_subdirectory(luabridge)
add_subdirectory(react)
add_subdirectory(assimp)
add_subdirectory(glad)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(glfw)
add_subdirectory(imgui)

# DLL's were a mistake.
set_target_properties(reactphysics3d PROPERTIES ENABLE_EXPORTS ON)
set_target_properties(reactphysics3d PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Puts a stop to the endlessly irritating practise postfixing 'd' onto debug libraries.
set_target_properties(assimp PROPERTIES DEBUG_POSTFIX "")
set_target_properties(glad PROPERTIES DEBUG_POSTFIX "")
set_target_properties(reactphysics3d PROPERTIES DEBUG_POSTFIX "")
set_target_properties(glfw PROPERTIES DEBUG_POSTFIX "")


# Ignore warnings from library headers.
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    glfw/include
    glfw/src
    assimp/include
    react/src
    glad/include
    glad/src
    lua/src
    luabridge/Source
)