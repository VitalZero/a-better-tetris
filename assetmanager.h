#pragma once
#include <raylib.h>
#include <unordered_map>
#include <string>
#include <memory>

class AssetManager
{
public:
	static std::shared_ptr<Texture2D> LoadSprite(const std::string& resource);

private:
	static std::unordered_map<std::string, std::shared_ptr<Texture2D>> texturePtrs;
};

//std::unordered_map<std::string, std::shared_ptr<Texture2D>> AssetManager::texturePtrs;