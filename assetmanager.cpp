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
		Texture2D tex = ::LoadTexture(resource.c_str());
		auto pTex = std::make_shared<Texture2D>(tex);

		texturePtrs.insert({ resource, pTex });

		return pTex;
	}
}


std::shared_ptr<Sound> AssetManager::LoadSound(const std::string& resource)
{
	const auto i = soundPtrs.find(resource);

	if( i != soundPtrs.end())
	{
		return i->second;
	}
	else
	{
		Sound snd = ::LoadSound(resource.c_str());
		auto pSnd = std::make_shared<Sound>(snd);

		soundPtrs.insert({ resource, pSnd });

		return pSnd;
	}
}


void AssetManager::CleanUp()
{
	for(auto& tex : texturePtrs)
	{
		UnloadTexture(*tex.second);
	}

	for(auto& snd : soundPtrs)
	{
		UnloadSound(*snd.second);
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

	for(auto i = soundPtrs.begin(); i != soundPtrs.end(); )
	{
		if(i->second.unique())
		{
			i = soundPtrs.erase(i);
		}
		else
		{
			i++;
		}
	}
}

std::unordered_map<std::string, std::shared_ptr<Texture2D>> AssetManager::texturePtrs;
std::unordered_map<std::string, std::shared_ptr<Sound>> AssetManager::soundPtrs;