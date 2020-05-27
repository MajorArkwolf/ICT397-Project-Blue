	/// Declaration Include
#include "../Manager.hpp"

	/// Internal Dependencies
#include "Controller/PhysicsManager.hpp"
#include "../Types.hpp"

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
