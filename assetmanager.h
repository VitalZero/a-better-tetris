#pragma once
#include <raylib.h>
#include <unordered_map>
#include <string>
#include <memory>
#include "wrappers.h"
#include <typeinfo>

class AssetManager
{
public:
	//std::shared_ptr<Texture2D> LoadSprite(const std::string& resource);
	//std::shared_ptr<Sound> LoadSound(const std::string& resource);
	//std::shared_ptr<Music> LoadMusic(const std::string& resource);
	template<typename T>
	std::shared_ptr<T> LoadAsset(const std::string& resource)
	{
		static_assert("this class type is not implemented");
		return nullptr;
	}
	void CleanUp();
	void MurderOrphans();

private:
	std::unordered_map<std::string, std::shared_ptr<Texture2D>> texturePtrs;
	std::unordered_map<std::string, std::shared_ptr<Sound>> soundPtrs;
	std::unordered_map<std::string, std::shared_ptr<Music>> musicPtrs;
};

template<>
inline std::shared_ptr<Texture2D> AssetManager::LoadAsset<Texture2D>(const std::string& resource)
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

template<>
inline std::shared_ptr<Sound> AssetManager::LoadAsset<Sound>(const std::string& resource)
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

template<>
inline std::shared_ptr<Music> AssetManager::LoadAsset<Music>(const std::string& resource)
{
	const auto i = musicPtrs.find(resource);

	if( i != musicPtrs.end())
	{
		return i->second;
	}
	else
	{
		Music msc = ::LoadMusicStream(resource.c_str());
		auto pMsc = std::make_shared<Music>(msc);

		musicPtrs.insert({ resource, pMsc });

		return pMsc;
	}
}