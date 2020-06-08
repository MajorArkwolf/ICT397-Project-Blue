	/// Definition Include
#include "../Base.hpp"

	/// System Dependencies
#include <functional>

	/// Internal Dependencies
#include "Controller/Engine/Engine.hpp"
#include "Controller/PhysicsManager.hpp"
#include "View/Renderer/Renderer.hpp"
#include "Model/GameObject/Types.hpp"
#include "LuaAssist.hpp"

GameObj_Base::GameObj_Base(BlueEngine::ID model_in, BlueEngine::ID physBody_in) {	
	// Store the external asset identifiers
	model = model_in;
	physBody = physBody_in;
	program = std::make_shared<Shader>(Shader("res/shader/vertshader.vs", "res/shader/fragshader.fs"));

	// Generate the GameObject's unique identifier.
	uniqueID = BlueEngine::IDTracker::getInstance().getID();

    //Peters addition
    auto *modelObj = ResourceManager::getModel(static_cast<unsigned>(model));
    if (modelObj->isAnimated) {
        animator = std::make_unique<Controller::Animator>();
        animator->LinkToModel(model);
        // All animation loading must be uppercase
        animator->LoadAnimation("WALK");
    }
}

BlueEngine::ID GameObj_Base::id()
{
	// Return a copy of the GameObject's unique identifier.
	return uniqueID;
}

GameObj_Type GameObj_Base::type() const {
	// The Base GameObject will always return an indicator that its type is not valid.
	return GameObj_Type::Invalid;
}

void GameObj_Base::lua_init_register() {
	// Register the Base GameObject class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginClass<GameObj_Base>("GameObj_Base")
			.addProperty("id", &GameObj_Base::uniqueID, false)
			.addProperty("type", &GameObj_Base::type)
			.addProperty("physBody", &GameObj_Base::physBody)
			.addProperty("model", &GameObj_Base::model)
		.endClass();
}
void GameObj_Base::update(double t, double dt) {
    if (animator != nullptr) {
        animator->BoneTransform(dt);
    }
}
