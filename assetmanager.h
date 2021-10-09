#pragma once
#include <raylib.h>
#include <unordered_map>
#include <string>
#include <memory>
#include "wrappers.h"

class AssetManager
{
public:
	std::shared_ptr<Texture2D> LoadSprite(const std::string& resource);
	std::shared_ptr<Sound> LoadSound(const std::string& resource);
	std::shared_ptr<Music> LoadMusic(const std::string& resource);
	void CleanUp();
	void MurderOrphans();

private:
	std::unordered_map<std::string, std::shared_ptr<Texture2D>> texturePtrs;
	std::unordered_map<std::string, std::shared_ptr<Sound>> soundPtrs;
	std::unordered_map<std::string, std::shared_ptr<Music>> musicPtrs;
};