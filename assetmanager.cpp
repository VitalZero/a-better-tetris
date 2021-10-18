#include "assetmanager.h"

void AssetManager::CleanUp()
{
	for(auto& tex : texturePtrs)
	{
		UnloadTexture(tex.second);
	}

	for(auto& snd : soundPtrs)
	{
		UnloadSound(snd.second);
	}

	for(auto& msc : musicPtrs)
	{
		UnloadMusicStream(msc.second);
	}
}