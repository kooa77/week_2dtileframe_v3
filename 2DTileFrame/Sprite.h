#pragma once

#include <string>

class Sprite
{
private:
	LPDIRECT3DDEVICE9 _dxDevice;
	ID3DXSprite * _spriteDX;

	IDirect3DTexture9* _textureDX;
	RECT _textureRect;
	D3DCOLOR _textureColor;

	std::wstring _fileName;
	D3DXIMAGE_INFO _texInfo;

public:
	Sprite();	// 생성자 (Constructor)
	~Sprite();	// 해제자 (파괴자)(Destructor)

	void Init(std::wstring fileName,
		LPDIRECT3DDEVICE9 dxDevice,
		ID3DXSprite * spriteDX);
	void Render();
	void Release();
	void Reset();
};
