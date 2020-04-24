#include "PrototypeScene.hpp"

#include <glm/glm.hpp>

#include "Controller/Engine/Engine.hpp"
#include "Controller/TextureManager.hpp"
#include "Model/Models/Model.hpp"
#include "Model/Models/ModelManager.hpp"
#include "View/Renderer/OpenGL.hpp"
#include "View/Renderer/Renderer.hpp"

using Controller::Input::BLUE_InputAction;
using Controller::Input::BLUE_InputType;

PrototypeScene::PrototypeScene() {
    Init();
}

PrototypeScene::~PrototypeScene() {
    world->DestroyRigidBody(cam->GetBody());
    // world->DestroyRigidBody(body->GetBody());
    world->DestroyRigidBody(testy->GetBody());
    world->DestroyRigidBody(testx->GetBody());
    delete cam;
    // delete body;
    delete testy;
    delete testx;
    delete factory;
    delete physics;
    delete world;
    delete blah;
}

auto PrototypeScene::update([[maybe_unused]] double t, double dt) -> void {

    if (moveForward) {
        // camera.ProcessKeyboard(FORWARD, dt);
        cam->ApplyForceToCentre(glm::vec3(0, 0, 1));
    }
    if (moveBackward) {
        // camera.ProcessKeyboard(BACKWARD, dt);
        cam->ApplyForceToCentre(glm::vec3(0, 0, -1));
    }
    if (moveLeft) {
        // camera.ProcessKeyboard(LEFT, dt);
        cam->ApplyForceToCentre(glm::vec3(-1, 0, 0));
    }
    if (moveRight) {
        // wcamera.ProcessKeyboard(RIGHT, dt);
        cam->ApplyForceToCentre(glm::vec3(1, 0, 0));
    }

    terrain.Update(camera.getLocation());

    camera.Position.x = cam->GetTransform().GetPosition().x;
    camera.Position.y = cam->GetTransform().GetPosition().y;
    camera.Position.z = cam->GetTransform().GetPosition().z;

    std::cout << "Camera position x:" << cam->GetTransform().GetPosition().x
              << " y: " << cam->GetTransform().GetPosition().y
              << " z: " << cam->GetTransform().GetPosition().z << std::endl;
}

void PrototypeScene::updateWorld(double ts) {
    if (world != nullptr) {
        world->Update(ts);
    } else {
        std::cout << "World not created" << std::endl;
    }
}

void PrototypeScene::updatePhysics(double f) {

    BeTransform currentXTransform = testx->GetTransform();

    BeTransform newXPosition =
        BeTransform::InterPolateTransform(previousXTransform, currentXTransform, f);

    previousXTransform = currentXTransform;

    BeTransform currentYTransform = testy->GetTransform();

    BeTransform newYPosition =
        BeTransform::InterPolateTransform(previousYTransform, currentYTransform, f);

    previousYTransform = currentYTransform;

    // cam->SetTransform(camera.Position, glm::quat(1, 0, 0, 0));
    bool test    = world->TestAABBOverlap(testx->GetBody(), testy->GetBody());
    bool testcam = world->TestAABBOverlap(cam->GetBody(), testy->GetBody());

    std::cout << "Collision test: " << test << " testcam: " << testcam << std::endl;

    //    std::cout << "Terrain position x: " << body->GetTransform().GetPosition().x << " y: " << body->GetTransform().GetPosition().y
    //                                    << " z: " << body->GetTransform().GetPosition().z << std::endl;

    std::cout << "Testx Position x: " << testx->GetTransform().GetPosition().x
              << " y: " << testx->GetTransform().GetPosition().y
              << " z: " << testx->GetTransform().GetPosition().z << std::endl;
    std::cout << "Testy Position x: " << testy->GetTransform().GetPosition().x
              << " y: " << testy->GetTransform().GetPosition().y
              << " z: " << testy->GetTransform().GetPosition().z << std::endl;
}

void PrototypeScene::Init() {
    auto &resManager = ResourceManager::getInstance();
    // terrain.Init();
    // camera.Position.y = 100.0;
    camera = Camera(glm::vec3(10.0f, 10.0f, 10.0f));
    models.emplace_back("res/model/nanosuit/nanosuit.obj", false);

    // models.push_back(resManager.getModelID("res/model/player_male.obj"));

    terrain.GenerateHeightMap(map);

    if (map.terrain == nullptr) {
        std::cout << "empty terrain pointer!!!" << std::endl;
    } else {
        std::cout << "Terrain filled" << std::endl;
    }

    settings.beSettings.isSleepingEnabled = true;
    // settings.beSettings.defaultVelocitySolverNbIterations = 20;
    grav = glm::vec3(0, -9.81, 0);
    blah = new float[100];
    for (int ii = 0; ii < 100; ii += 1) {
        blah[ii] = 0;
    }

    // constructing world
    world = new BeDynamicWorld(grav, settings);
    std::cout << " world gravity x: " << world->GetWorld()->getGravity().x
              << " y: " << world->GetWorld()->getGravity().y
              << " z: " << world->GetWorld()->getGravity().z << std::endl;

    world->EnableGravity(true);
    world->SetGravity(grav);
    world->EnableSleeping(settings.beSettings.isSleepingEnabled);
    world->SetSleepLinearVelocity(settings.beSettings.defaultSleepLinearVelocity);
    world->SetSleepAngularVelocity(settings.beSettings.defaultSleepAngularVelocity);
    world->SetNumIterationPositionSolver(settings.beSettings.defaultPositionSolverNbIterations);
    world->SetNumIterationVelocitySolver(settings.beSettings.defaultVelocitySolverNbIterations);
    world->SetTimeBeforeSleep(settings.beSettings.defaultTimeBeforeSleep);

    std::cout << "gravity enabled: " << world->GetWorld()->isGravityEnabled() << std::endl;
    std::cout << "sleep enabled: " << world->GetSleepToggle() << std::endl;

    factory = new BeRP3DFactory();
    physics = new BePhysicsLibrary(factory);

    // constructing camera body
    cam = physics->CreateBody(camera.Position, glm::quat(1, 0, 0, -1), glm::vec3(1, 1, 1), 1, 0, 0,
                              0, 0, world, blah, ShapeType::Box, 1);
    cam->EnableGravity(false);
    cam->SetType(BeBodyType::DYNAMIC);
    //    auto camMat = cam->GetMaterial();
    //    camMat->SetBounciness(0.2);
    bodies.emplace_back(cam);

    // constructing height shape
    //    glm::vec3 initPosition(-map.position.x * 2, map.position.y, -map.position.z * 2);
    //    body = physics->CreateBody(initPosition, map.rotation, glm::vec3(0, 0, 0), map.mass, map.width,
    //                               map.height, 0, 0, world, map.terrain, ShapeType::Height, map.targetId);
    //    body->SetType(BeBodyType::STATIC);
    //    bodies.emplace_back(body);

    // constructing test body y
    testy = physics->CreateBody(glm::vec3(0, 20000, 0), glm::quat(1, 0, 0, 0),
                                glm::vec3(1000, 100, 1000), 100, 10, 10, 0, 0, world, blah,
                                ShapeType::Box, 2);
    //    testy->EnableGravity(true);
    testy->SetType(BeBodyType::STATIC);
    BeMaterial &testyMat = testy->GetMaterial();
    testyMat.SetBounciness(0.2);
    bodies.emplace_back(testy);
    previousYTransform.SetToIdentity();

    // constructing test body x
    testx = physics->CreateBody(glm::vec3(10, 21000, 10), glm::quat(1, 0, 0, 0), glm::vec3(1, 1, 1),
                                1, 0, 0, 0, 0, world, blah, ShapeType::Box, 3);
    //    testx->EnableGravity(true);
    // testx->SetSleep(true);
    std::cout << "obj sleep: " << testx->IsSleepEnabled() << std::endl;
    BeMaterial &testxMat = testx->GetMaterial();
    testxMat.SetBounciness(0.2);
    testx->SetType(BeBodyType::DYNAMIC);
    bodies.emplace_back(testx);
    previousXTransform.SetToIdentity();

    // checking for location of the terrain shape
    //    for(int ii = 0; ii < 4096; ii += 1)
    //    {
    //        for(int jj = 0; jj < 4096; jj += 1)
    //        {
    //            glm::vec3 check = body->GetVertexAt(ii, jj);
    //            std::cout << "Terrain local position x: " << check.x << " y: " << check.y << " z: " << check.z << std::endl;
    //        }
    //    }
}

void PrototypeScene::handleWindowEvent() {
    View::OpenGL::ResizeWindow();
}

// SDLFIX
void PrototypeScene::handleInputData(Controller::Input::InputData inputData) {

    auto &engine      = BlueEngine::Engine::get();
    auto &guiManager  = engine.getGuiManager();
    auto handledMouse = false;

    switch (inputData.inputType) {
        case BLUE_InputType::KEY_PRESS: { //  Key Press events

            switch (inputData.inputAction) {
                case BLUE_InputAction::INPUT_MOVE_FORWARD: {
                    moveForward = true;
                } break;
                case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
                    moveBackward = true;
                } break;
                case BLUE_InputAction::INPUT_MOVE_LEFT: {
                    moveLeft = true;
                } break;
                case BLUE_InputAction::INPUT_MOVE_RIGHT: {
                    moveRight = true;
                } break;
                case BLUE_InputAction::INPUT_ESCAPE: {
                    guiManager.toggleWindow("menu");
                } break;

                default: break;
            }

        } break;
        case BLUE_InputType::KEY_RELEASE: { // Key Release events
            switch (inputData.inputAction) {
                case BLUE_InputAction::INPUT_MOVE_FORWARD: {
                    moveForward = false;
                } break;
                case BLUE_InputAction::INPUT_MOVE_BACKWARD: {
                    moveBackward = false;
                } break;
                case BLUE_InputAction::INPUT_MOVE_LEFT: {
                    moveLeft = false;
                } break;
                case BLUE_InputAction::INPUT_MOVE_RIGHT: {
                    moveRight = false;
                } break;
                case BLUE_InputAction::INPUT_ACTION_2: {
                    auto &renderer = BlueEngine::Engine::get().renderer;
                    renderer.ToggleWireFrame();
                } break;
                case BLUE_InputAction::INPUT_ACTION_3: {
                    guiManager.toggleWindow("instructions");
                } break;
                case BLUE_InputAction::INPUT_ACTION_4: {
                    guiManager.toggleWindow("exit");
                } break;
                default: break;
            }
        } break;
        case BLUE_InputType::MOUSE_MOTION: { // Mouse motion event
            if (!engine.getMouseMode()) {
                auto x = static_cast<double>(inputData.mouseMotionRelative.x);
                auto y = static_cast<double>(inputData.mouseMotionRelative.y);
                y      = y * -1.0;
                camera.ProcessMouseMovement(x, y);
                handledMouse = true;
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

auto PrototypeScene::display() -> void {
    auto &renderer = BlueEngine::Engine::get().renderer;
    renderer.SetCameraOnRender(camera);
    // glm::mat4 model = glm::mat4(5.0f);
    // renderer.AddToQue(models.at(0));
    terrain.AddToDraw();
    // terrain.Draw(projection, view, camera.Position);
    // renderer.draw(view, projection);
}

void PrototypeScene::unInit() {}
