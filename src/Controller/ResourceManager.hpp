#pragma once
#include <string>

#include "Controller/Engine/LuaManager.hpp"
#include "Controller/TextureManager.hpp"
#include "Model/Models/ModelManager.hpp"
#include "Model/TextManager.hpp"

/*
 * @class ResourceManager
 * @brief Used as the overall handler for all resources
 * Is a singleton class
 */
class ResourceManager {
  public:
    /**
     * @brief Sets up and runs the lua script to load in resources
     */
    auto loadResources() -> void;
    /**
     * @brief Inserts a string in to the text manager with a given key
     * @param key The identifier to give the key
     * @param value the string value to insert into the text manager
     */
    auto insertString(std::string key, std::string value) -> void;
    /**
     * @brief Gets a string from the text manager
     * @param key The key value for the string to return
     * @return A string at the given key location
     */
    auto getString(std::string key) -> std::string;
    /**
     * @brief Gets the id of the model with the given filename / key
     * @param filename The key / filename of the model to return the id of
     * @return The ID of the model with the given key /filename
     */
    auto getModelID(std::string filename) -> size_t;
    /**
     * @brief Draws a model with the given id using the given shader
     * @param id The id of the model to draw
     *  @param ourshader A pointer to the shader to use
     */
    auto drawModel(size_t id, Shader *ourshader) -> void;

    /**
     * @brief Returns a static instance of the singleton Resource Manager
     * @return A static instance of the resource manager
     */
    static auto getInstance() -> ResourceManager &;

    /**
     * @brief Returns the text manager
     * @return The text manager
     */
    TextManager &GetTextManager();
    /**
     * @brief Returns the model manager
     * @return The model manager
     */
    ModelManager &GetModelManager();
    /**
     * @brief Returns the texture manager
     * @return The texture manager
     */
    TextureManager &GetTextureManager();

  private:
    /// A manager for all text elements in the program
    TextManager textManager;
    /// A manager for all models within the program
    ModelManager modelManager;
    /// A manager for all textures within the program
    TextureManager textureManager;

    /// Private default constructor
    ResourceManager();

    /**
     * @brief Used to provide lua with a means to load a model
     * @param filePath The filepath of the model to load
     */
    static auto loadModel(const std::string &filePath) -> void;
    /**
     * @brief Used to provide lua with a means to load a string
     * @param key The key to look for in the lua file
     */
    static auto loadString(const std::string key) -> void;
    /**
     * @brief used to provide lua with  a means to load a texture
     * @param filepath The filepath of the image to load  as texture
     * @param textureName The key to use to store the texture
     */
    static auto loadTexture(const std::string filePath, const std::string textureName) -> void;
};
