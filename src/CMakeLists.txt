
# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
    main.cpp

    # Controller/Engine/QuaternionCamera.cpp Not used, needs to be updated
    Controller/Engine/LuaManager.cpp
    Controller/InputManager.cpp
    Controller/Engine/Engine.cpp
    Controller/GUIManager.cpp
    Controller/ResourceManager.cpp
    Controller/TerrainManager.cpp
    Controller/Factory/GameAssetFactory.cpp
    Controller/Factory/TerrainFactory.cpp    
    Controller/TextureManager.cpp
    
    # Model
    Model/Models/Mesh.cpp
    Model/Models/Model.cpp
    Model/Models/ModelManager.cpp
    Model/TerrainModel.cpp
    Model/WaterModel.cpp
    Model/TextManager.cpp
    Model/Texture.cpp

    # View
    View/Renderer/Shader.cpp
    View/EulerCamera.cpp
    View/Renderer/Renderer.cpp
    View/Renderer/OpenGLProxy.cpp

    # Game
    Game/SceneManager.cpp
    Game/Prototype/PrototypeScene.cpp



    #IMGUI
    View/ImGui/imgui_impl_glfw.cpp
    View/ImGui/imgui_impl_opengl3.cpp
)

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})