
# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
    main.cpp

    # Controller/Engine/QuaternionCamera.cpp Not used, needs to be updated
    Controller/Engine/Engine.cpp
    Controller/Engine/IDTracker.cpp
    Controller/Engine/LuaManager.cpp
    Controller/InputManager.cpp

    Controller/GUIManager.cpp
    Controller/ResourceManager.cpp
    Controller/TerrainManager.cpp
    Controller/Factory/GameAssetFactory.cpp
    Controller/Factory/TerrainFactory.cpp    
    Controller/PhysicsFacade/React/ReactRigidBody.cpp
    Controller/PhysicsFacade/React/ReactDynamicsWorld.cpp
    Controller/PhysicsFacade/React/ReactHelper.cpp
    Controller/PhysicsFacade/React/ReactShapes.cpp
    Controller/TextureManager.cpp
    Controller/PhysicsFacade/React/ReactCollisionShape.cpp
    Controller/PhysicsFacade/React/ReactCollisionBody.cpp
    Controller/PhysicsFacade/React/ReactCollisionWorld.cpp
    Controller/PhysicsManager.cpp
    Controller/Animator.cpp
    
    # Model
    Model/Models/Mesh.cpp
    Model/Models/Model.cpp
    Model/Models/ModelManager.cpp
    Model/TerrainModel.cpp
    Model/WaterModel.cpp
    Model/TextManager.cpp
    Model/TerrainModel.cpp
    Model/Models/Animation.cpp


        # Game Objects
    Model/GameObject/detail/Base.cpp
    Model/GameObject/detail/Static.cpp
    Model/GameObject/detail/Item.cpp
    Model/GameObject/detail/Character.cpp
    Model/GameObject/detail/Player.cpp
    Model/GameObject/detail/NPC.cpp
    Model/GameObject/detail/Manager.cpp
    Model/GameObject/detail/LuaAssist.cpp

    Model/GameState.cpp

    # View
    View/Renderer/Shader.cpp
    View/EulerCamera.cpp
    View/Renderer/OpenGL.cpp
    View/Renderer/Skybox.cpp

    # Game
    Game/Prototype/PrototypeScene.cpp
    Game/MainMenu/MainMenu.cpp
    Game/MainMenu/StaticModel.cpp



    #IMGUI
    View/ImGui/imgui_impl_glfw.cpp
    View/ImGui/imgui_impl_opengl3.cpp
)

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})