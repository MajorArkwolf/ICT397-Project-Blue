
# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
    Main.cpp   

    # Controller
    Controller/Engine/QuaternionCamera.cpp
    Controller/Engine/InputManager.cpp
    Controller/Engine/Engine.cpp
    
    # Model
    Model/Models/Mesh.cpp
    Model/Models/Model.cpp
    Model/Models/ModelManager.cpp

    # View
    View/Renderer/Shader.cpp
    View/EulerCamera.cpp
    View/Renderer/Renderer.cpp
    View/Renderer/OpenGLProxy.cpp

    # Game
    Game/SceneManager.cpp
    Game/Prototype/PrototypeScene.cpp  
)

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})