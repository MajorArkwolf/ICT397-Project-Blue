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
			// Create a new physics body for the GameObject, assigining default properties
			auto phys_id = id_assigner.getID();
			Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->CreateRigidBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);
			Physics::PhysicsManager::GetInstance().GetCollisionWorld()->CreateCollisionBody(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), phys_id);

            dynamic_cast<Physics::ReactRigidBody *>(
                Physics::PhysicsManager::GetInstance().GetDynamicsWorld()->GetRigidBody(phys_id))
                ->SetBodyType(Physics::ReactRigidBody::RigidBodyType::DYNAMIC);


			// Create a atatic configured the GameObject, onlmy return this one
			auto static staticPlayer = std::make_shared<GameObj_Player>(0u, phys_id);
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

			//TODO: Finish AI system and generate a FSM for the GameObject

			// Create a configured the GameObject
			object = std::make_shared<GameObj_NPC>(0u, phys_id, 0u);

		}
		break;
    default:
        break;
	}
	return object;
}
