#pragma once
#include <raylib.h>
#include <unordered_map>
#include <string>
#include <memory>

class AssetManager
{
public:
	static std::shared_ptr<Texture2D> LoadSprite(const std::string& resource);
	static std::shared_ptr<Sound> LoadSound(const std::string& resource);
	static std::shared_ptr<Music> LoadMusic(const std::string& resource);
	static void CleanUp();
	static void MurderOrphans();

private:
	static std::unordered_map<std::string, std::shared_ptr<Texture2D>> texturePtrs;
	static std::unordered_map<std::string, std::shared_ptr<Sound>> soundPtrs;
	static std::unordered_map<std::string, std::shared_ptr<Music>> musicPtrs;
};

//std::unordered_map<std::string, std::shared_ptr<Texture2D>> AssetManager::texturePtrs;