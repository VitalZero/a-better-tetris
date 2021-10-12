#include "assetmanager.h"

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

	for(auto& msc : musicPtrs)
	{
		UnloadMusicStream(*msc.second);
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

	for(auto i = musicPtrs.begin(); i != musicPtrs.end(); )
	{
		if(i->second.unique())
		{
			i = musicPtrs.erase(i);
		}
		else
		{
			i++;
		}
	}

}