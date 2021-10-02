#pragma once
#include <raylib.h>
#include <unordered_map>
#include <string>
#include <memory>
#include "wrappers.h"

class AssetManager
{
public:
	static std::shared_ptr<Texture2D> LoadSprite(const std::string& resource);
	static std::shared_ptr<Sound> LoadSound(const std::string& resource);
	static std::shared_ptr<Music> LoadMusic(const std::string& resource);
	template<class TAsset>
	static std::shared_ptr<TAsset> LoadAsset(const std::string& resource)
	{
		const auto i = assetPtrs.find(resource);

		if( i != assetPtrs.end())
		{
			return i->second;
		}
		else
		{
			TAsset tmpAsset(resource.c_str());
			std::shared_ptr<TAsset> pAsset = std::make_shared<TAsset>(std::move(tmpAsset));

			assetPtrs<TAsset>.insert({ resource, pAsset });

			return pAsset;
		}
	}
	static void CleanUp();
	static void MurderOrphans();

private:
	static std::unordered_map<std::string, std::shared_ptr<Texture2D>> texturePtrs;
	static std::unordered_map<std::string, std::shared_ptr<Sound>> soundPtrs;
	static std::unordered_map<std::string, std::shared_ptr<Music>> musicPtrs;
	template<class TAsset>
	static std::unordered_map<std::string, std::shared_ptr<TAsset>> assetPtrs;
};

//std::unordered_map<std::string, std::shared_ptr<Texture2D>> AssetManager::texturePtrs;