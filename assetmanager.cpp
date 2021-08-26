#include "assetmanager.h"

std::shared_ptr<Texture2D> AssetManager::LoadSprite(const std::string& resource)
{
	const auto i = texturePtrs.find(resource);

	if( i != texturePtrs.end())
	{
		return i->second;
	}
	else
	{
		Texture2D tex = LoadTexture(resource.c_str());
		auto pTex = std::make_shared<Texture2D>(tex);

		texturePtrs.insert({ resource, pTex });

		return pTex;
	}
}

void AssetManager::CleanUp()
{
	for(auto& tex : texturePtrs)
	{
		UnloadTexture(*tex.second);
	}
}

void AssetManager::MurderOrphans()
{
	for(auto i = texturePtrs.begin(); i != texturePtrs.end(); )
	{
		if(i->second.unique())
		{
			i = texturePtrs.erase(i);
		}
		else
		{
			i++;
		}
	}
}

std::unordered_map<std::string, std::shared_ptr<Texture2D>> AssetManager::texturePtrs;