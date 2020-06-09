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

GameObj_Base::GameObj_Base(size_t model_in, BlueEngine::ID physBody_in) {
	// Store the external asset identifiers
	model = model_in;
	physBody = physBody_in;
	program = std::make_shared<Shader>(Shader("res/shader/vertshader.vs", "res/shader/fragshader.fs"));

	// Generate the GameObject's unique identifier.
	uniqueID = BlueEngine::IDTracker::getInstance().getID();
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
			.addFunction("anim_init", &GameObj_Base::animator_add)
			.addFunction("anim_set", &GameObj_Base::animator_changeAnimation)
			.addFunction("anim_has", &GameObj_Base::animator_has)
		.endClass();
}

bool GameObj_Base::animator_add() {
	// Get the raw access to the GameObject's model
	auto* modelObj = ResourceManager::getModel(model);

	// Catch an invalid model
	if (modelObj == nullptr)
		return false;

	// Check if the model is animated
	if (modelObj->isAnimated) {
		// Store a new animator into the GameObject, and link it to the model
		animator = std::make_unique<Controller::Animator>();
		animator->LinkToModel(model);

		// Indicate success
		return true;
	}

	// Catch a non-animated model
	return false;
}

void GameObj_Base::animator_update(double t [[maybe_unused]], double dt) {
	// Catch an invalid animator
	if (animator) {
		// Update the model's animation through a delta bone transform
		animator->BoneTransform(dt);
	}
}

void GameObj_Base::animator_changeAnimation(std::string animToLoad, bool stopOnEnd) {
	// Catch an invalid animator
	if (animator) {
		// Load the animation
		animator->LoadAnimation(animToLoad, stopOnEnd);
	}
}

bool GameObj_Base::animator_has() {
	// Return if the GameObject's animator is not nullptr
	return (animator != nullptr);
}
