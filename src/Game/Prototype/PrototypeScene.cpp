#include "PrototypeScene.hpp"
#include "Controller/Factory/GameAssetFactory.hpp"
#include "Controller/PhysicsManager.hpp"
#include "Controller/AI/Manager.hpp"
#include "Model/GameObject/Manager.hpp"
#include "Model/GameState.hpp"

using Controller::Input::BLUE_InputAction;
using Controller::Input::BLUE_InputType;

View::Camera *getCamera() {
    return &(BlueEngine::Engine::get().gameStack.getTop()->camera);
}

void toggleWireframe() {
    auto &render = BlueEngine::Engine::get().renderer;
    render.ToggleWireFrame();
}

void EndGame() {
    BlueEngine::Engine::get().endEngine();
}

PrototypeScene::PrototypeScene() {
    luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
        .addFunction("getCamera", &getCamera)
        .addFunction("toggleWireframe", &toggleWireframe)
        .addFunction("getHeightAt", &Controller::TerrainFactory::LuaBLHeight)
        .addFunction("getMapSize", &Controller::TerrainFactory::LuaMapSize)
        .addFunction("getDifficulty", &Model::GameState::gameDifficulty)
        .addFunction("EndGame", &EndGame);


    PrototypeScene::Init();
    View::Camera::LuaInit();
    auto &window = BlueEngine::Engine::get().window;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

PrototypeScene::~PrototypeScene() {
    /*terrain.DeInit();
    GameObj_Manager::clear();
    BlueEngine::IDTracker::getInstance().clear();
    Physics::PhysicsManager::GetInstance().clear();*/
}

auto PrototypeScene::update(double t, double dt) -> void {
    // Update the terrain
    terrain.Update(camera.getLocation());
    
    // Update the GameObject animations
    //GameObj_Manager::animation_update(t, dt);

    // Read and call the lua update function, this allows runtime change of the script
    try {
        // Run the script, and catch and Lua errors that are thrown
        luaL_dofile(LuaManager::getInstance().getLuaState(), "./res/scripts/luaFunctions.lua");
    }
    catch (luabridge::LuaException const& err) {
        // Print out the error that had occured when running the script
        std::cerr << "Scene Update Lua Functions Script Error: \"" << err.what() << "\"\n";
    }
    luabridge::LuaRef Update =
        luabridge::LuaRef::getGlobal(LuaManager::getInstance().getLuaState(), "Update");

    // Catch if an Lua scripted update function has been provided
    if (!Update.isNil()) {
        // Catch any errors thrown when running the Lua scripted Update() function
        try {
            Update(dt);
        }
        catch (luabridge::LuaException const& err) {
            // Print out the error that had occured when running the Lua function
            std::cerr << "Scene Lua Update Function Error: \"" << err.what() << "\"\n";
        }
    }
    else {
        // Report no scripted update function has been provided
        std::cerr << "No scripted Update() function was provided to call!\n";
    }

    // Call the AI System's update function
    FSM_Manager::update(t, dt);

    // Update the Dynamic Physics world
    Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->Update(dt);

    // Sync the GameObject physics bodies
    GameObj_Manager::syncPhys();
}

void PrototypeScene::Init() {
    auto &engine = BlueEngine::Engine::get();
    camera       = View::Camera(glm::vec3(0.0f, 150.0f, 3.0f));

    // Initialise the Physics system
    auto phys_sys = &(Physics::PhysicsManager::GetInstance());
    phys_sys->InitialiseCollisionWorld();
    phys_sys->InitialiseDynamicsWorld();
    phys_sys->InitialiseShapeFactory();

    // Initialise the GameObject system
    GameObj_Manager::init();

    // Initialise the FSM AI system
    FSM_Manager::lua_init();

    // Run the GameObject initialisation script
    try {
        // Run the script, and catch and Lua errors that are thrown
        if (luaL_dofile(LuaManager::getInstance().getLuaState(), "./res/scripts/gameObjsInit.lua")) {
            printf("Scene Initialisation Script (Non-Thrown) Error: ");
            printf("\"%s\"\n", lua_tostring(LuaManager::getInstance().getLuaState(), -1));
        }
    }
    catch (luabridge::LuaException const& err) {
        // Print out the error that had occured when running the script
        std::cerr << "Scene Initialisation Script Error: \"" << err.what() << "\"\n";
    }

    auto *phys_world_dynamics = phys_sys->GetDynamicsWorld();
    auto *phys_world_collision = phys_sys->GetCollisionWorld();

    Blue::HeightMap heightMap;
    auto id_assigner = BlueEngine::IDTracker::getInstance();
    terrain.GenerateHeightMap(heightMap);
    const auto terrainID = phys_sys->GetShapeFactory()->createHeightField(
        heightMap.width, heightMap.height, heightMap.heightRange.min, heightMap.heightRange.max,
        heightMap.terrain);
    const auto terrainPhysID = 9999999;


    phys_world_dynamics->CreateRigidBody(heightMap.position, heightMap.rotation, terrainPhysID);
    auto *reactBodyHeights =
        dynamic_cast<Physics::ReactRigidBody *>(phys_world_dynamics->GetRigidBody(terrainPhysID));
    reactBodyHeights->AddCollisionShape(
        dynamic_cast<Physics::ReactShapes *>(phys_sys->GetShapeFactory())->GetShape(terrainID),
        glm::vec3{0, 0, 0}, glm::quat(1, 0, 0, 0), 1.f);
    reactBodyHeights->SetBodyType(Physics::ReactRigidBody::RigidBodyType::STATIC);

    phys_world_collision->CreateCollisionBody(heightMap.position, heightMap.rotation, terrainPhysID);
    auto *reactCollisionBodyHeights =
        dynamic_cast<Physics::ReactCollisionBody *>(phys_world_collision->GetCollisionBody(terrainPhysID));
    reactCollisionBodyHeights->AddCollisionShape(
        dynamic_cast<Physics::ReactShapes *>(phys_sys->GetShapeFactory())->GetShape(terrainID),
        glm::vec3{0, 0, 0}, glm::quat(1, 0, 0, 0));

    engine.getGuiManager().setTerrainManager(&terrain);
}

void PrototypeScene::handleWindowEvent() {
    auto &engine = BlueEngine::Engine::get();
    engine.renderer.ResizeWindow();
}

void PrototypeScene::handleInputData(Controller::Input::InputData inputData, double deltaTime) {

    if (luaL_dofile(LuaManager::getInstance().getLuaState(), "./res/scripts/luaFunctions.lua")) {
        printf("%s\n", lua_tostring(LuaManager::getInstance().getLuaState(), -1));
    }
    luabridge::LuaRef luaInput =
        luabridge::LuaRef::getGlobal(LuaManager::getInstance().getLuaState(), "handleInput");
    if (!luaInput.isNil()) {
        luaInput(inputData, deltaTime);
    }

    auto &engine      = BlueEngine::Engine::get();
    auto &guiManager  = engine.getGuiManager();
    auto handledMouse = false;

    switch (inputData.inputType) {
        case BLUE_InputType::KEY_PRESS: { //  Key Press events

            switch (inputData.inputAction) {
                case BLUE_InputAction::INPUT_MOVE_FORWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_LEFT: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_RIGHT: {
                } break;
                default: break;
            }
        } break;
        case BLUE_InputType::KEY_RELEASE: { // Key Release events
            switch (inputData.inputAction) {
                case BLUE_InputAction::INPUT_MOVE_FORWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_LEFT: {
                } break;
                case BLUE_InputAction::INPUT_MOVE_RIGHT: {
                } break;
                case BLUE_InputAction::INPUT_JUMP: {
                } break;
                case BLUE_InputAction::INPUT_CROUCH: {
                } break;
                case BLUE_InputAction::INPUT_ACTION_2: {
                } break;
                case BLUE_InputAction::INPUT_ACTION_3: {
                } break;
                case BLUE_InputAction::INPUT_ACTION_4: {
                } break;
                default: break;
            }
        } break;
        case BLUE_InputType::MOUSE_MOTION: { // Mouse motion event
            if (!engine.getMouseMode()) {
                /* auto x = static_cast<double>(inputData.mouseMotionRelative.x);
                 auto y = static_cast<double>(inputData.mouseMotionRelative.y);
                 y      = y * -1.0;
                 camera.ProcessMouseMovement(x, y);
                 handledMouse = true;*/
            }
        } break;
        case BLUE_InputType::MOUSE_WHEEL: { // Mouse Wheel event
            double amountScrolledY = static_cast<double>(inputData.mouseWheelMotion);
            camera.ProcessMouseScroll(amountScrolledY);
        } break;
        case BLUE_InputType::WINDOW_RESIZE: {
            this->handleWindowEvent();
        } break;
        default: break;
    }
    if (!handledMouse) {
        engine.mouse = {0.0f, 0.0f};
    }
}

float PrototypeScene::GetHeightAt(glm::vec2 coord) {
    return terrain.GetBLHeight(coord);
}

auto PrototypeScene::display() -> void {
    auto &engine   = BlueEngine::Engine::get();
    auto &renderer = BlueEngine::Engine::get().renderer;
    renderer.SetCameraOnRender(camera);
    terrain.AddToDraw();
    // Update the GameObject animations
    GameObj_Manager::animation_update(0.0, engine.getFrameTime());
    GameObj_Manager::addAllToDraw();
}

void PrototypeScene::unInit() {
    //terrain.DeInit();
}

void PrototypeScene::GUIStart() {
    auto &engine = BlueEngine::Engine::get();
    auto& guiManager = engine.getGuiManager();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    GUIManager::startWindowFrame();
    guiManager.displayInputRebindWindow();
    guiManager.displayEscapeMenu();
    guiManager.displayInstructionMenu();
    guiManager.displayQuitScreen();
    guiManager.displayDevScreen(camera);
    guiManager.displayTextureManager();
    guiManager.displayTerrainSettings();
    if (engine.showSettingsMenu) {
        engine.SettingMenu();
    }
    if (luaL_dofile(LuaManager::getInstance().getLuaState(), "./res/scripts/luaFunctions.lua")) {
        printf("%s\n", lua_tostring(LuaManager::getInstance().getLuaState(), -1));
    }
    luabridge::LuaRef LuaGui =
        luabridge::LuaRef::getGlobal(LuaManager::getInstance().getLuaState(), "GUI");
    if (!LuaGui.isNil()) {
        LuaGui();
    }
}

void PrototypeScene::GUIEnd() {
    GUIManager::endWindowFrame();
}

