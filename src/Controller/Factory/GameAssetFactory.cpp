#include "GameAssetFactory.hpp"

	/// Internal Dependencies
#include "Controller/AI/Manager.hpp"
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
            dynamic_cast<Physics::ReactRigidBody *>(
                Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(phys_id))
                ->SetBodyType(Physics::ReactRigidBody::RigidBodyType::STATIC);

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
			// Only configure the player setup once
			static std::shared_ptr<GameObj_Base> staticPlayer;
			static bool isGenerated = false;
			if (!isGenerated) {
				// Create a new physics body for the GameObject, assigining default properties
				auto phys_id = id_assigner.getID();
				Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->CreateRigidBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);
				Physics::PhysicsManager::GetInstance().GetCollisionWorld()->CreateCollisionBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);
				dynamic_cast<Physics::ReactRigidBody*>(
					Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(phys_id))
					->SetBodyType(Physics::ReactRigidBody::RigidBodyType::DYNAMIC);

				// Configure the static Player GameObject
				staticPlayer = std::make_shared<GameObj_Player>(0u, phys_id);

				// Prevent the re-configuration of the GameObject in the factory
				isGenerated = true;
			}

			// Return a reference to the static Player GameObject
			object = staticPlayer;
		}
		break;

	case (GameObj_Type::NPC):
		{
			// Create a new physics body for the GameObject, assigining default properties
			auto phys_id = id_assigner.getID();
			Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->CreateRigidBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);
			Physics::PhysicsManager::GetInstance().GetCollisionWorld()->CreateCollisionBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);

		            dynamic_cast<Physics::ReactRigidBody *>(
                Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(phys_id))
                ->SetBodyType(Physics::ReactRigidBody::RigidBodyType::DYNAMIC);

			// Create a configured the GameObject
			auto npc_temp = std::make_shared<GameObj_NPC>(0u, phys_id, 0u);
			object = npc_temp;

			// Create a new FSM for the NPC
			npc_temp->contextID = FSM_Manager::create(object);
		}
		break;
    default:
        break;
	}
	return object;
}
