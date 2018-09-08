#include <d3dx9.h>
#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	if (_textureDX)
	{
		_textureDX->Release();
		_textureDX = NULL;
	}
}

void Sprite::Init(std::wstring fileName,
	LPDIRECT3DDEVICE9 dxDevice,
	ID3DXSprite * spriteDX)
{
	_fileName = fileName;
	_dxDevice = dxDevice;
	_spriteDX = spriteDX;

	HRESULT hr;
	{
		// 파일로 부터 이미지의 너비와 높이를 얻는다
		hr = D3DXGetImageInfoFromFile(fileName.c_str(), &_texInfo);
		if (FAILED(hr))
		{
			return;
		}

		// 이미지데이타 로드
		hr = D3DXCreateTextureFromFileEx(dxDevice,
			fileName.c_str(),
			_texInfo.Width, _texInfo.Height,
			1,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_ARGB(255, 255, 255, 255),
			&_texInfo,
			NULL,
			&_textureDX);
		if (FAILED(hr))
		{
			return;
		}

		// 출력할 영역 지정
		_textureRect.left = 64;
		_textureRect.right = _textureRect.left + 32;
		_textureRect.top = 96;
		_textureRect.bottom = _textureRect.top + 32;

		_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
}

void Sprite::Render()
{
	// 2D 이미지 출력 공간. Texture(텍스쳐)
	_spriteDX->Draw(
		_textureDX,		// 그릴 텍스쳐 정보가 들어있는 인터페이스
		&_textureRect,	// 원본 이미지에서 그릴 부분
		NULL,
		NULL,
		_textureColor	// 스프라이트의 색상과 알파채널
	);
}

void Sprite::Release()
{
}

void Sprite::Reset()
{
	// 텍스쳐 복구
	HRESULT hr = D3DXCreateTextureFromFileEx(_dxDevice,
		_fileName.c_str(),
		_texInfo.Width, _texInfo.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		&_texInfo,
		NULL,
		&_textureDX);
}
