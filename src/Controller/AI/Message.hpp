#pragma once

	/// System Dependencies
#include <set>
#include <vector>

	/// Internal Dependencies
#include "Controller/Engine/IDTracker.hpp"
#include "Controller/Engine/LuaManager.hpp"

	//! Defines the types of inter-FSM messages that can be sent.
enum class Message_Type {
	Invalid,
	PositionX,
	PositionY,
	PositionZ,
	TargetFound,
	IAmHurt,
	IAmHelping
};

// Registratiion of Enum Message_Type
namespace luabridge {
	template <>
	struct luabridge::Stack <Message_Type> : EnumWrapper <Message_Type> {};
}

	/*!
	 * @brief The data structure used for inter-FSM communication.
	 * @note Wraps only a single setter and getter interface for its internal recipient set for scripting.
	 */
class Message {
public:
		/*!
		 * @brief The default constructor, calls for the internal set's constructor.
		 * @note This is only declared for compatibility of creation within the scripting system scope.
		 */
	Message();

		/*!
		 * @brief Stores the identifier of the FSM that generated this message.
		 * @warning The identifier is not guaranteed to match any existing FSM!
		 */
	BlueEngine::ID sender;

		/*!
		 * @brief Stores the type identifier for this message.
		 * @note This value is used for applying context to the message's contents.
		 */
	Message_Type type;

		/*!
		 * @brief Secondary message data, used to suppliment the stored type.
		 * @note Use of this data should match the context implied by the message's stored type.
		 */
	float attachment;

		/*!
		 * @brief The amount of FSM Manager updates that should occur before this message is delivered.
		 * @note Applicable to avoiding an infinite loop of inter-FSM messaging, 0 will deliver immediately.
		 * @warning This is not delta-time sensitive, only FSM Manager updating sensitive!
		 */
	unsigned int delay;

		/*!
		 * @brief Stores a set of intended recipient FSMs, referenced via their identifier.
		 * @warning Only the interfaces to add and list the contents is exposed to the scripting system!
		 */
	std::set<BlueEngine::ID> recipients;

		/*!
		 * @brief Scripting interface to add a target recipient for this message.
		 * @param [in] identifier The identifier of the FSM to send this message to.
		 */
	void recipient_add(BlueEngine::ID identifier);

		/*!
		 * @brief Scripting interface to list the target recipients for this message.
		 * @return A vector of FSM identifiers stored in the message's recipient set.
		 */
	std::vector<BlueEngine::ID> recipient_list();
};
