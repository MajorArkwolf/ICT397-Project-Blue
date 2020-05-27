#include "GameAssetFactory.hpp"

	/// Internal Dependencies
#include "Controller/PhysicsManager.hpp"
#include "Model/GameObject/Types.hpp"
#include "Model/GameObject/Static.hpp"
#include "Model/GameObject/Item.hpp"
#include "Model/GameObject/Player.hpp"
#include "Model/GameObject/NPC.hpp"

Controller::Factory::Factory() {
    terrain.Init();
    //terrain.LoadLua();
}

auto Controller::Factory::get() -> Factory & {
    static auto instance = Factory{};
    return instance;
}

std::shared_ptr<GameObj_Base> Controller::Factory::GameObject(GameObj_Type type) {
	// Keep track of the engine id generator
	auto id_assigner = BlueEngine::IDTracker::getInstance();

	// Process the provided type key
	std::shared_ptr<GameObj_Base> object = nullptr;
	switch (type)
	{
	case (GameObj_Type::Static):
		{
			// Create a new physics body for the GameObject, assigining default properties
			auto phys_id = id_assigner.getID();
			Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->CreateRigidBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);
			Physics::PhysicsManager::GetInstance().GetCollisionWorld()->CreateCollisionBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);

			// Make the rigid physics body not move on its own accord
			Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(phys_id)->SetSleeping(true);

			// Create a configured the GameObject
			object = std::make_shared<GameObj_Static>(0u, phys_id);
		}
		break;

	case (GameObj_Type::Item):
		{
			// Create a new physics body for the GameObject, assigining default properties
			auto phys_id = id_assigner.getID();
			Physics::PhysicsManager::GetInstance().GetCollisionWorld()->CreateCollisionBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);

			// Create a configured the GameObject
			object = std::make_shared<GameObj_Item>(0u, phys_id);
		}
		break;

	case (GameObj_Type::Player):
		{
			// Create a new physics body for the GameObject, assigining default properties
			auto phys_id = id_assigner.getID();
			Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->CreateRigidBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);
			Physics::PhysicsManager::GetInstance().GetCollisionWorld()->CreateCollisionBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);

			// Create a configured the GameObject
			object = std::make_shared<GameObj_Player>(0u, phys_id);
		}
		break;

	case (GameObj_Type::NPC):
		{
			// Create a new physics body for the GameObject, assigining default properties
			auto phys_id = id_assigner.getID();
			Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->CreateRigidBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);
			Physics::PhysicsManager::GetInstance().GetCollisionWorld()->CreateCollisionBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);

			//TODO: Finish AI system and generate a FSM for the GameObject

			// Create a configured the GameObject
			object = std::make_shared<GameObj_NPC>(0u, phys_id, 0u);
		}
		break;

	//default:
		// No need to do anything else, without additional configuration this will always return nullptr.
	}
	return object;
}
