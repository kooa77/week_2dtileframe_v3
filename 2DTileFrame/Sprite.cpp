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
		// ���Ϸ� ���� �̹����� �ʺ�� ���̸� ��´�
		hr = D3DXGetImageInfoFromFile(fileName.c_str(), &_texInfo);
		if (FAILED(hr))
		{
			return;
		}

		// �̹�������Ÿ �ε�
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

		// ����� ���� ����
		_textureRect.left = 64;
		_textureRect.right = _textureRect.left + 32;
		_textureRect.top = 96;
		_textureRect.bottom = _textureRect.top + 32;

		_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
}

void Sprite::Render()
{
	// 2D �̹��� ��� ����. Texture(�ؽ���)
	_spriteDX->Draw(
		_textureDX,		// �׸� �ؽ��� ������ ����ִ� �������̽�
		&_textureRect,	// ���� �̹������� �׸� �κ�
		NULL,
		NULL,
		_textureColor	// ��������Ʈ�� ����� ����ä��
	);
}

void Sprite::Release()
{
}

void Sprite::Reset()
{
	// �ؽ��� ����
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
