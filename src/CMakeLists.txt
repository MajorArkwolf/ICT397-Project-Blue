
# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
    main.cpp

    # Controller/Engine/QuaternionCamera.cpp Not used, needs to be updated
    Controller/Engine/Engine.cpp
    Controller/Engine/IDTracker.cpp
    Controller/Engine/LuaManager.cpp
    Controller/InputManager.cpp

    Controller/Physics/BeCollisionWorld.cpp
    Controller/Physics/BeQuaternion.cpp
    Controller/Physics/BeTransform.cpp
    Controller/Physics/BeVector3.cpp
    Controller/Physics/BeBoxBody.cpp
    Controller/Physics/BeHeightBody.cpp
    Controller/Physics/BeRP3DFactory.cpp
    Controller/Physics/BePhysicsLibrary.cpp
    Controller/Physics/BeCapsuleBody.cpp
    Controller/Physics/BeSphereBody.cpp
    Controller/Physics/BeDynamicWorld.cpp
    Controller/Physics/BeBoxPhysics.cpp
    Controller/Physics/BeCapsulePhysics.cpp
    Controller/Physics/BeHeightPhysics.cpp
    Controller/Physics/BeSpherePhysics.cpp
    Controller/Physics/BeMaterial.cpp

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

    Model/GameObject/detail/Base.cpp
    Model/GameObject/detail/Static.cpp
    Model/GameObject/detail/Player.cpp
    Model/GameObject/detail/NPC.cpp
    Model/GameObject/detail/Manager.cpp
    Model/GameObject/detail/LuaHelper.cpp

    # View
    View/Renderer/Shader.cpp
    View/EulerCamera.cpp
    View/Renderer/OpenGL.cpp
    View/Renderer/Skybox.cpp

    # Game
    Game/Prototype/PrototypeScene.cpp



    #IMGUI
    View/ImGui/imgui_impl_glfw.cpp
    View/ImGui/imgui_impl_opengl3.cpp
)

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})