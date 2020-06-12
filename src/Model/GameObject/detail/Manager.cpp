/// Declaration Include
#include "../Manager.hpp"

/// Internal Dependencies
#include "Controller/Factory/GameAssetFactory.hpp"
#include "Controller/PhysicsManager.hpp"
#include "LuaAssist.hpp"

void GameObj_Manager::init() {
	// Prevent registering multiple times
	static bool is_registered = false;
	if (is_registered)
		return;

	// Register the raw GameObject classes
	GameObj_Base::lua_init_register();
	GameObj_Character::lua_init_register();
	GameObj_NPC::lua_init_register();

	// Register this GameObject Manager class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("GameObject")
			.addFunction("create", GameObj_Manager::lua_create)
			.addFunction("get", GameObj_Manager::lua_get)
			.addFunction("getPlayer", GameObj_Manager::lua_getPlayer)
			.addFunction("listNPCs", GameObj_Manager::lua_listNPCs)
			.addFunction("remove", GameObj_Manager::remove)
			.addFunction("clear", GameObj_Manager::clear)
			.addFunction("syncPhys", GameObj_Manager::syncPhys)
			.addFunction("to_character", GameObj_Manager::lua_to_character)
			.addFunction("to_npc", GameObj_Manager::lua_to_npc)
		.endNamespace();

	// Register the GameObj_Type enum spawning functions
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("GameObject")
			.beginNamespace("Types")
				.addFunction("Invalid", GameObj_LuaHelper::Invalid)
				.addFunction("Static", GameObj_LuaHelper::Static)
				.addFunction("Item", GameObj_LuaHelper::Item)
				.addFunction("Player", GameObj_LuaHelper::Player)
				.addFunction("NPC", GameObj_LuaHelper::NPC)
			.endNamespace()
		.endNamespace();

	// Prevent re-registration
	is_registered = true;
}

void GameObj_Manager::insert(const std::shared_ptr<GameObj_Base> &object) {
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
			managed_objs[object->id()] = object;
			break;
	}
}

std::shared_ptr<GameObj_Base> GameObj_Manager::get(BlueEngine::ID identifier) {
	// Catch any errors thrown
	try {
		// Attempt to find and return a copy of the requested GameObject
		return managed_objs.at(identifier);
	} catch (...) {
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

void GameObj_Manager::process_all(const std::function<void(std::shared_ptr<GameObj_Base> GameObj_In)>
	&function) {
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
	for (auto &i : managed_objs) {
		// Call the currently accessed GameObject's addToDraw function
		i.second->addToDraw();
	}
}

void GameObj_Manager::syncPhys() {
	// Keep track of the collision and dynamics physics worlds
	auto *world_collision = Physics::PhysicsManager::GetInstance().GetCollisionWorld();
	auto *world_dynamics  = Physics::PhysicsManager::GetInstance().GetDynamicsWorld();

	// Loop through all of the GameObjects
	for (auto &i : managed_objs) {
		// Only process the GameObjects with a rigid body
		if ((i.second->type() != GameObj_Type::Invalid) && (i.second->type() != GameObj_Type::Item)) {
			// Track the engine physics bodies for the current GameObject
			auto *body_collision = world_collision->GetCollisionBody(i.second->physBody);
			auto *body_rigid     = world_dynamics->GetRigidBody(i.second->physBody);

			// Update the collision body to match the rigid body
			body_collision->SetPositionAndOrientation(body_rigid->GetPosition(),
													  body_rigid->GetOrientation());
		}
	}
}

BlueEngine::ID GameObj_Manager::lua_create(GameObj_Type type) {
	// Attempt to generate the GameObject from the Factory, and hold onto its output
	auto temp = Controller::Factory::get().GameObject(type);

	// Catch if the Factory output is valid
	if (temp == nullptr) {
		// Return 0u in cases where the GameObject would not be valid
        assert(0);
		return BlueEngine::ID(0u);
	}

	// Store the GameObject into the Manager
	GameObj_Manager::insert(temp);

	// Return the GameObject's identifier
	return temp->id();
}

GameObj_Base *GameObj_Manager::lua_get(BlueEngine::ID identifier) {
	// Just return the same outcome, but without the smart pointer wrapper
	return GameObj_Manager::get(identifier).get();
}

GameObj_Base *GameObj_Manager::lua_getPlayer() {
	// Gather and return the GameObject Player
	return dynamic_cast<GameObj_Character *>(
		Controller::Factory::get().GameObject(GameObj_Type::Player).get());
}

std::vector<BlueEngine::ID> GameObj_Manager::lua_listNPCs() {
	// Keep track of the identifiers
	std::vector<BlueEngine::ID> identifierList;

	// Process all of the GameObjects
	for (auto & managed_obj : managed_objs) {
		// Catch if the GameObject is an NPC
		if (managed_obj.second->type() == GameObj_Type::NPC)
			identifierList.push_back(managed_obj.second->id());
	}

	// Return the generated list
	return identifierList;
}

GameObj_Character *GameObj_Manager::lua_to_character(GameObj_Base *raw_in) {
	// Perform the case, it'll return nullptr if an invalid cast
	return dynamic_cast<GameObj_Character *>(raw_in);
}

GameObj_NPC *GameObj_Manager::lua_to_npc(GameObj_Character *raw_in) {
	// Perform the case, it'll return nullptr if an invalid cast
	return dynamic_cast<GameObj_NPC *>(raw_in);
}

void GameObj_Manager::animation_update(double t, double dt) {
	// Process all of the GameObjects
	//for (auto i = managed_objs.begin(); i != managed_objs.end(); ++i) {
	for (auto &i :managed_objs) {
		// Update the GameObject's animation, relative to the delta time
		i.second->animator_update(t, dt);
	}
}

	/// Static Initialisation
std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>> GameObj_Manager::managed_objs = std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>>();
