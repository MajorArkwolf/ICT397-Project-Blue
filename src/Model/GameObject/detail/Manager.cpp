	/// Declaration Include
#include "../Manager.hpp"

	/// Internal Dependencies
#include "Controller/Engine/LuaManager.hpp"
#include "Controller/PhysicsManager.hpp"
#include "../Types.hpp"
#include "../Base.hpp"
#include "../Static.hpp"
#include "../Item.hpp"
#include "../Character.hpp"
#include "../Player.hpp"
#include "../NPC.hpp"

void GameObj_Manager::init() {
	// Prevent registering multiple times
	static bool is_registered = false;
	if (is_registered)
		return;

	// Register the Base GameObject class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("GameObject")
			.beginClass<GameObj_Base>("GO_Base")
				.addFunction("id", &GameObj_Base::id)
				.addFunction("type", &GameObj_Base::type)
				.addProperty("physBody", &GameObj_Base::physBody)
				.addProperty("model", &GameObj_Base::model)
			.endClass()
		.endNamespace();

	// Register the Static GameObject class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("GameObject")
			.deriveClass<GameObj_Static, GameObj_Base>("GO_Static")
				.addFunction("type", &GameObj_Static::type)
			.endClass()
		.endNamespace();

	// Register the Item GameObject class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("GameObject")
			.deriveClass<GameObj_Item, GameObj_Base>("GO_Item")
				.addFunction("type", &GameObj_Item::type)
			.endClass()
		.endNamespace();

	// Register the Character GameObject class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("GameObject")
			.deriveClass<GameObj_Character, GameObj_Base>("GO_Character")
				.addFunction("type", &GameObj_Character::type)
				.addFunction("status_assign", &GameObj_Character::status_assign)
				.addFunction("status_has", &GameObj_Character::status_has)
				.addFunction("status_get", &GameObj_Character::status_get)
				.addFunction("status_delete", &GameObj_Character::status_delete)
				.addFunction("status_clear", &GameObj_Character::status_clear)
			.endClass()
		.endNamespace();

	// Register the Player GameObject class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("GameObject")
			.deriveClass<GameObj_Player, GameObj_Character>("GO_Player")
				.addFunction("type", &GameObj_Player::type)
			.endClass()
		.endNamespace();

	// Register the NPC GameObject class
	luabridge::getGlobalNamespace(LuaManager::getInstance().getLuaState())
		.beginNamespace("GameObject")
			.deriveClass<GameObj_NPC, GameObj_Character>("GO_Player")
				.addFunction("type", &GameObj_NPC::type)
				.addFunction("context", &GameObj_NPC::context)
			.endClass()
		.endNamespace();
}

void GameObj_Manager::insert(std::shared_ptr<GameObj_Base> object) {
	// Catch and stop processing nullptr
	if (!object)
		return;

	// Optimizatin storage split
	switch (object->type())
	{
	case (BlueEngine::ID(GameObj_Type::Invalid)):
		// Do nothing, this is an invalid GameObject
		break;

	case (BlueEngine::ID(GameObj_Type::Static)):
	case (BlueEngine::ID(GameObj_Type::Item)):
		// Store into the generic GameObject map
		generic_objs[object.get()->id()] = object;
		break;

	case (BlueEngine::ID(GameObj_Type::Player)):
	case (BlueEngine::ID(GameObj_Type::NPC)):
		// Store into the character GameObject map
		character_objs[object.get()->id()] = object;
		break;
	}
}

std::shared_ptr<GameObj_Base> GameObj_Manager::get(BlueEngine::ID identifier)
{
	// Catch any errors thrown
	try {
		if (generic_objs.find(identifier) != generic_objs.end())
		{
			// Attempt to find and return a copy of the requested GameObject
			return generic_objs.at(identifier);
		}

		// Attempt to find and return a copy of the requested GameObject
		return character_objs.at(identifier);
	}
	catch (...) {
		// Indicate no element with specified found
		return nullptr;
	}
}

void GameObj_Manager::remove(BlueEngine::ID identifier) {
	// Check if the target GameObject is generic
	if (generic_objs.find(identifier) != generic_objs.end())
	{
		// Just remove the specified GameObject from the manager, don't directly call for it to be removed from memory
		generic_objs.erase(identifier);
	}
	else
	{
		// Just remove the specified GameObject from the manager, don't directly call for it to be removed from memory
		character_objs.erase(identifier);
	}
}

void GameObj_Manager::clear() {
	// Just remove the GameObjects from the manager, don't directly call for it to be removed from memory
	generic_objs.clear();
	character_objs.clear();
}

void GameObj_Manager::process_all(std::function<void(std::shared_ptr<GameObj_Base> GameObj_In)> function) {
	// Catch invalid function pointer
	if (function == nullptr)
		return;

	// Loop through all of the generic GameObjects
	for (auto i = generic_objs.begin(); i != generic_objs.end(); ++i)
	{
		// Pass the currently processed GameObject to the provided function
		function(i->second);
	}

	// Loop through all of the character GameObjects
	for (auto i = character_objs.begin(); i != character_objs.end(); ++i)
	{
		// Pass the currently processed GameObject to the provided function
		function(i->second);
	}
}

void GameObj_Manager::addAllToDraw() {
	// Process all of the generic GameObjects
	for (auto i = generic_objs.begin(); i != generic_objs.end(); ++i)
	{
		// Call the currently accessed GameObject's addToDraw function
		i->second.get()->addToDraw();
	}

	// Process all of the character GameObjects
	for (auto i = character_objs.begin(); i != character_objs.end(); ++i)
	{
		// Call the currently accessed GameObject's addToDraw function
		i->second.get()->addToDraw();
	}
}

void GameObj_Manager::updatePhys() {
	// Keep track of the collision and dynamics physics worlds
	auto world_collision = Physics::PhysicsManager::GetInstance().GetCollisionWorld();
	auto world_dynamics = Physics::PhysicsManager::GetInstance().GetDynamicsWorld();

	// Loop through all of the generic GameObjects
	for (auto i = generic_objs.begin(); i != generic_objs.end(); ++i)
	{
		// Only process the generic GameObjects with a rigid body
		if (i->second->type() == BlueEngine::ID(GameObj_Type::Static))
		{
			// Track the engine physics bodies for the current GameObject
			auto body_collision = world_collision->GetCollisionBody(i->second->physBody);
			auto body_rigid = world_dynamics->GetRigidBody(i->second->physBody);

			// Update the collision body to match the rigid body
			body_collision->SetPositionAndOrientation(body_rigid->GetPosition(), body_rigid->GetOrientation());
		}
	}

	// Loop through all of the character GameObjects
	for (auto i = character_objs.begin(); i != character_objs.end(); ++i)
	{
		// Track the engine physics bodies for the current GameObject
		auto body_collision = world_collision->GetCollisionBody(i->second->physBody);
		auto body_rigid = world_dynamics->GetRigidBody(i->second->physBody);

		// Update the collision body to match the rigid body
		body_collision->SetPositionAndOrientation(body_rigid->GetPosition(), body_rigid->GetOrientation());
	}
}

	/// Static Initialisation
std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>> GameObj_Manager::generic_objs = std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>>();
std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>> GameObj_Manager::character_objs = std::map<BlueEngine::ID, std::shared_ptr<GameObj_Base>>();
