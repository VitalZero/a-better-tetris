#include "wrappers.h"

// Texture2D Wrappers
CTexture2D::CTexture2D(const char* fileName)
	:
	texture(::LoadTexture(fileName))
{
}

CTexture2D::~CTexture2D()
{
	::UnloadTexture(texture);
}

Texture2D& CTexture2D::GetTexture()
{
	return texture;
}

// Sound Wrappers	
CSound::CSound(const char* fileName)
	:
	sound(::LoadSound(fileName))
{
}

CSound::~CSound()
{
	::UnloadSound(sound);
}

Sound& CSound::GetSound()
{
	return sound;
}
