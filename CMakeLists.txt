# Set cmake minimum version.
cmake_minimum_required(VERSION 3.12)

# Set the project details.
set(PROJECT_NAME Project-Blue)
project(${PROJECT_NAME} LANGUAGES CXX)

# If enabled, the post build symlink will copy instead.
option(CopyResources "CopyResources" OFF)
# Disables any post build steps.
option(DisablePostBuild "DisablePostBuild" OFF)
# Treat warnings as errors.
option(WarningsAsErrors "WarningsAsErrors" OFF)

# Disable in-source builds.
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

# Set the cmake module paths.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)


# Set build type to debug by default.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# Define source files.
set (SOURCES
    src/Main.cpp
    

    # Controller
    src/Controller/Engine/QuaternionCamera.cpp
    src/Controller/Engine/InputManager.cpp
    src/Controller/Engine/Engine.cpp
    src/Controller/Engine/CollisionBody.cpp
    src/Controller/Engine/CollisionWorld.cpp
    src/Controller/Engine/Quaternion.cpp
    src/Controller/Engine/Vector3.cpp
    src/Controller/Engine/Transform.cpp
    
    # Model
    src/Model/Models/Mesh.cpp
    src/Model/Models/Model.cpp
    src/Model/Models/ModelManager.cpp

    # View
    src/View/Renderer/Shader.cpp
    src/View/EulerCamera.cpp
    src/View/Renderer/Renderer.cpp
    src/View/Renderer/OpenGLProxy.cpp

    # Game
    src/Game/SceneManager.cpp
    src/Game/Prototype/PrototypeScene.cpp    
    )


# Define the executable.
add_executable(${PROJECT_NAME} ${SOURCES})

# Set C++ standard.
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        )

# Remove the default warning level from MSVC.
if (MSVC)
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif ()

# Set Clang compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Weverything -fcolor-diagnostics
        # These warnings are not useful.
        -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
        -Wno-deprecated-declarations -Wno-exit-time-destructors -Wno-switch-enum
        -Wno-weak-vtables>)
# Set GCC compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:GNU>:
        -Wall -Wextra -Wpedantic -fdiagnostics-color=always>)
# Set MSVC compile flags.
target_compile_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/W4>)

# Enable Clang's address and memory sanitizers.
if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC
            $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address,undefined,leak>)
    target_link_libraries(${PROJECT_NAME} PUBLIC
            $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address,undefined,leak>)
endif ()
# Treat warnings as errors if enabled.
if (WarningsAsErrors)
    target_compile_options(${PROJECT_NAME} PUBLIC
            $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
            -Werror>)
    target_compile_options(${PROJECT_NAME} PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/WX>)
endif ()

# Fix an MSVC linker warning.
if (MSVC)
    #set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:msvcrt.lib")
endif ()

# Find dependencies.
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(glm REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(bullet CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

# Build 3rd Party Liberaries
add_subdirectory(lib)


# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE src)

# DLL's were a mistake.
set_target_properties(reactphysics3d PROPERTIES ENABLE_EXPORTS ON)
set_target_properties(reactphysics3d PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Include and link against dependencies.
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL OpenGL::GLU
        SDL2::SDL2 SDL2::Image SDL2::TTF SDL2::Mixer glm glad::glad assimp::assimp LuaBridge reactphysics3d ImGui lua)


# Symlink or copy the resources to the binary location.
if (NOT DisablePostBuild)
if (NOT CopyResources)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E create_symlink
${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
else()
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
endif()
endif()