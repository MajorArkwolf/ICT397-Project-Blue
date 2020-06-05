	/// Declaration Include
#include "Controller/AI/Message.hpp"

Message::Message() {
	// Nothing needed here, all set assignment is automatically called.
}

void Message::recipient_add(BlueEngine::ID identifier) {
	// Call the set's operation
	recipients.insert(identifier);
}

std::vector<BlueEngine::ID> Message::recipient_list() {
	// Copy and return the entire range of set elements into a new vector
	return std::vector<BlueEngine::ID>(recipients.begin(), recipients.end());
}
