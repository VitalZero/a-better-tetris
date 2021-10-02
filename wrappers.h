#pragma once
#include "raylib.h"

// Texture2D wrapper
class CTexture2D
{
public:
	CTexture2D() = default;
	CTexture2D(const char* fileName);
	CTexture2D(const CTexture2D&) = delete;
	CTexture2D operator = (const CTexture2D&) = delete;
	~CTexture2D();
	Texture2D& GetTexture();
private:
	Texture2D texture;
};

// Sound Wrapper
class CSound
{
public:
	CSound() = default;
	CSound(const char* fileName);
	CSound(const CSound&) = delete;
	CSound operator = (const CSound&) = delete;
	~CSound();
	Sound& GetSound();
private:
	Sound sound;
};