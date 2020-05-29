	/// Declaration Include
#include "../Manager.hpp"

	/// Internal Dependencies
#include "Controller/PhysicsManager.hpp"
#include "Controller/Factory/GameAssetFactory.hpp"
#include "LuaAssist.hpp"

void GameObj_Manager::init() {
	// Prevent registering multiple times
	static bool is_registered = false;
	if (is_registered)
		return;

	// Register the Base GameObject class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginClass<GameObj_Base>("GameObj_Base")
			.addFunction("id", &GameObj_Base::id)
			.addFunction("type", &GameObj_Base::type)
			.addProperty("physBody", &GameObj_Base::physBody)
			.addProperty("model", &GameObj_Base::model)
		.endClass();

	// Register this GameObject Manager class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("GameObject")
			.addFunction("create", &GameObj_Manager::lua_create)
			.addFunction("get", &GameObj_Manager::lua_get)
			.addFunction("remove", &GameObj_Manager::remove)
			.addFunction("clear", &GameObj_Manager::clear)
			.addFunction("syncPhys", &GameObj_Manager::syncPhys)
			.addFunction("charData", &GameObj_Manager::lua_charData)
		.endNamespace();

	// Register the GameObj_Type enum spawning functions
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("GameObject")
			.beginNamespace("Types")
				.addFunction("Invalid", &GameObj_LuaHelper::Invalid)
				.addFunction("Static", &GameObj_LuaHelper::Static)
				.addFunction("Item", &GameObj_LuaHelper::Item)
				.addFunction("Player", &GameObj_LuaHelper::Player)
				.addFunction("NPC", &GameObj_LuaHelper::NPC)
			.endNamespace()
		.endNamespace();

	// Register the LuaHelper class for the Character GameObjects
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginClass<GameObj_LuaHelper::CharacterWrapper>("GameObject_CharacterData")
			.addFunction("type", &GameObj_LuaHelper::CharacterWrapper::type)
			.addFunction("status_assign", &GameObj_LuaHelper::CharacterWrapper::status_assign)
			.addFunction("status_count", &GameObj_LuaHelper::CharacterWrapper::status_count)
			.addFunction("status_has", &GameObj_LuaHelper::CharacterWrapper::status_has)
			.addFunction("status_list", &GameObj_LuaHelper::CharacterWrapper::status_list)
			.addFunction("status_get", &GameObj_LuaHelper::CharacterWrapper::status_get)
			.addFunction("status_delete", &GameObj_LuaHelper::CharacterWrapper::status_delete)
			.addFunction("status_clear", &GameObj_LuaHelper::CharacterWrapper::status_clear)
			.addFunction("npc_context", &GameObj_LuaHelper::CharacterWrapper::npc_context)
			.addFunction("is_valid", &GameObj_LuaHelper::CharacterWrapper::is_valid)
		.endClass();
}

void GameObj_Manager::insert(std::shared_ptr<GameObj_Base> object) {
	// Catch and stop processing nullptr
	if (!object)
		return;

	// Optimizatin storage split
	switch (object->type()) {
	case (GameObj_Type::Invalid):
		// Do nothing, this is an invalid GameObject
		break;

	case (GameObj_Type::Static):
	case (GameObj_Type::Item):
	case (GameObj_Type::Player):
	case (GameObj_Type::NPC):
		// Store into the character GameObject map
		managed_objs[object.get()->id()] = object;
		break;
	}
}

std::shared_ptr<GameObj_Base> GameObj_Manager::get(BlueEngine::ID identifier) {
	// Catch any errors thrown
	try {
		// Attempt to find and return a copy of the requested GameObject
		return managed_objs.at(identifier);
	}
	catch (...) {
		// Indicate no element with specified found
		return nullptr;
	}
}

void GameObj_Manager::remove(BlueEngine::ID identifier) {
	// Just remove the specified GameObject from the manager's map
	managed_objs.erase(identifier);
}

void GameObj_Manager::clear() {
	// Just remove the GameObjects from the manager's map
	managed_objs.clear();
}

void GameObj_Manager::process_all(std::function<void(std::shared_ptr<GameObj_Base> GameObj_In)> function) {
	// Catch invalid function pointer
	if (function == nullptr)
		return;

	// Loop through all of the GameObjects
	for (auto i = managed_objs.begin(); i != managed_objs.end(); ++i) {
		// Pass the currently processed GameObject to the provided function
		function(i->second);
	}
}

void GameObj_Manager::addAllToDraw() {
	// Process all of the GameObjects
	for (auto i = managed_objs.begin(); i != managed_objs.end(); ++i) {
		// Call the currently accessed GameObject's addToDraw function
		i->second.get()->addToDraw();
	}
}

void GameObj_Manager::syncPhys() {
	// Keep track of the collision and dynamics physics worlds
	auto world_collision = Physics::PhysicsManager::GetInstance().GetCollisionWorld();
	auto world_dynamics = Physics::PhysicsManager::GetInstance().GetDynamicsWorld();

	// Loop through all of the GameObjects
	for (auto i = managed_objs.begin(); i != managed_objs.end(); ++i) {
		// Only process the GameObjects with a rigid body
		if ((i->second->type() != GameObj_Type::Invalid) && (i->second->type() != GameObj_Type::Item)) {
			// Track the engine physics bodies for the current GameObject
			auto body_collision = world_collision->GetCollisionBody(i->second->physBody);
			auto body_rigid = world_dynamics->GetRigidBody(i->second->physBody);

			// Update the collision body to match the rigid body
			body_collision->SetPositionAndOrientation(body_rigid->GetPosition(), body_rigid->GetOrientation());
		}
	}
}

BlueEngine::ID GameObj_Manager::lua_create(GameObj_Type type) {
	// Attempt to generate the GameObject from the Factory, and hold onto its output
	auto temp = Controller::Factory::get().GameObject(type);

	// Catch if the Factory output is valid
	if (temp == nullptr) {
		// Return 0u in cases where the GameObject would not be valid
		return BlueEngine::ID(0u);
	}

	// Store the GameObject into the Manager
	GameObj_Manager::insert(temp);

	// Return the GameObject's identifier
	return temp->id();
}

GameObj_Base* GameObj_Manager::lua_get(BlueEngine::ID identifier) {
	// Just return the same outcome, but without the smart pointer wrapper
	return GameObj_Manager::get(identifier).get();
}

GameObj_LuaHelper::CharacterWrapper GameObj_Manager::lua_charData(BlueEngine::ID identifier) {
	// Attempt to gather the requested GameObject
	std::shared_ptr<GameObj_Base> temp_reference;
	try {
		// Attempt to gather the GameObject
		temp_reference = managed_objs.at(identifier);

		// Check the type
		if ((temp_reference->type() != GameObj_Type::Player) && (temp_reference->type() != GameObj_Type::NPC))
		{
			// Catch the invalid type, just pass nullptr out
			temp_reference = nullptr;
		}
	}
	catch (...) {
		// Just pass nullptr out
		temp_reference = nullptr;
	}

	// Encapculate the GameObject and return it
	std::shared_ptr<GameObj_Character> temp_out(dynamic_cast<GameObj_Character*>(temp_reference.get()));
	return GameObj_LuaHelper::CharacterWrapper(temp_out);
}

	/// Static Initialisation
std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>> GameObj_Manager::managed_objs = std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>>();
