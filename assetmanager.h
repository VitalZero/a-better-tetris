#pragma once
#include <raylib.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <typeinfo>

class AssetManager
{
public:
	template<typename T>
	T* LoadAsset(const std::string& resource)
	{
		static_assert("this class type is not implemented");
		return nullptr;
	}
	void CleanUp();

private:
	std::unordered_map<std::string, Texture2D> texturePtrs;
	std::unordered_map<std::string, Sound> soundPtrs;
	std::unordered_map<std::string, Music> musicPtrs;
};

template<>
inline Texture2D* AssetManager::LoadAsset<Texture2D>(const std::string& resource)
{
	const auto i = texturePtrs.find(resource);

	if( i != texturePtrs.end())
	{
		return &i->second;
	}
	else
	{
		texturePtrs.insert({ resource, ::LoadTexture(resource.c_str()) });

		return &texturePtrs.find(resource)->second;
	}
}

template<>
inline Sound* AssetManager::LoadAsset<Sound>(const std::string& resource)
{
	const auto i = soundPtrs.find(resource);

	if( i != soundPtrs.end())
	{
		return &i->second;
	}
	else
	{
		soundPtrs.insert({ resource, ::LoadSound(resource.c_str()) });

		return &soundPtrs.find(resource)->second;
	}
}

template<>
inline Music* AssetManager::LoadAsset<Music>(const std::string& resource)
{
	const auto i = musicPtrs.find(resource);

	if( i != musicPtrs.end())
	{
		return &i->second;
	}
	else
	{
		musicPtrs.insert({ resource, ::LoadMusicStream(resource.c_str()) });

		return &musicPtrs.find(resource)->second;
	}
}