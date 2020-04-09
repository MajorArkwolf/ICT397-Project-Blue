#include "GameObject.hpp"

GameObject::GameObject() {
	// Set the default values of the GameObject's 3D position attributes
	position = {0.0f, 0.0f, 0.0f};
	look_at  = {0.0f, 0.0f, 1.0f};
	look_up  = {0.0f, 1.0f, 0.0f};
}
