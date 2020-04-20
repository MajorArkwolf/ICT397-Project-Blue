	/// Definition Include
#include "../NPC.hpp"

	/// External Dependencies
#include <glm/gtc/matrix_transform.hpp>

	/// Internal Dependencies
#include "View/Renderer/Renderer.hpp"
#include "../GameObject.hpp"

#include "Controller/Engine/Engine.hpp"

	/// Debugging Dependencies
#include <assert.h>

GameObj_NPC::GameObj_NPC()
	: GameObj_Base() {
	// Configure the Shader
	gameObj_shader = std::make_shared<Shader>(Shader("res/shader/vertshader.vs", "res/shader/fragshader.fs"));
}

GameObj_NPC::GameObj_NPC(std::string path, unsigned long int physBody, glm::vec3 position, float rotateHori, float rotateVert, float rotateTilt)
	: GameObj_Base(path, physBody, position, rotateHori, rotateVert, rotateTilt) {
	// Configure the Shader
	gameObj_shader = std::make_shared<Shader>(Shader("res/shader/vertshader.vs", "res/shader/fragshader.fs"));
}

GameObj_NPC::~GameObj_NPC() {
	// GameObj_NPC has no unique destruction procedure yet.
}

GameObjType GameObj_NPC::gameObj_getTypeID() const {
	// Return a copy of the class's unique type identifier
	return _gameObj_getTypeID();
}

GameObjType GameObj_NPC::_gameObj_getTypeID() {
	// Always return error indicator GAMEOBJ_NPC, never return anything else.
	return GAMEOBJ_NPC;
}

void GameObj_NPC::gameObj_addToDraw() {
    auto &renderer = BlueEngine::Engine::get().renderer;
    //We create a function pointer of our model and pass it in.
    std::function e = [&](const glm::mat4 &projection, const glm::mat4 &view, const glm::dvec3 &cameraPos) {
        this->Draw(projection, view, cameraPos);
    };
    View::Data::DrawItem di;
    di.drawPointer = e;
    di.pos = gameObj_pos;
    renderer.AddToQue(di);
}

void GameObj_NPC::Draw(const glm::mat4& projection, const glm::mat4& view, const glm::dvec3& cameraPos) {
    if (gameObj_shader != nullptr) {
        //Please modify your code to take a reference instead throughout your code.
        auto& res_manager = ResourceManager::getInstance();
        //Please add model and scale to your game objects so these can be changed accordingly.
        glm::mat4 model = glm::mat4(1.0f);
        auto scale =  glm::vec3(1.0f);
        model = glm::translate(model, gameObj_pos);
        model = glm::scale(model, scale);
        // Then we enabled the shader and set the model up. Always enable before setting.
        gameObj_shader->use();
        gameObj_shader->setMat4("projection", projection);
        gameObj_shader->setMat4("view", view);
        gameObj_shader->setMat4("model", model);
        res_manager.drawModel(gameObj_modelId, gameObj_shader.get());
    }
}

