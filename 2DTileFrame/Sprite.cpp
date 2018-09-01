#include <d3dx9.h>
#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

void Sprite::Init(std::wstring fileName,
	LPDIRECT3DDEVICE9 dxDevice,
	ID3DXSprite * spriteDX)
{
	_dxDevice = dxDevice;
	_spriteDX = spriteDX;

	HRESULT hr;

	D3DXIMAGE_INFO texInfo;
	{
		// ���Ϸ� ���� �̹����� �ʺ�� ���̸� ��´�
		hr = D3DXGetImageInfoFromFile(fileName.c_str(), &texInfo);
		if (FAILED(hr))
		{
			return;
		}

		// �̹�������Ÿ �ε�
		hr = D3DXCreateTextureFromFileEx(dxDevice,
			fileName.c_str(),
			texInfo.Width, texInfo.Height,
			1,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_ARGB(255, 255, 255, 255),
			&texInfo,
			NULL,
			&_textureDX);
		if (FAILED(hr))
		{
			return;
		}

		// ����� ���� ����
		_textureRect.left = 0;
		_textureRect.right = _textureRect.left + texInfo.Width;
		_textureRect.top = 0;
		_textureRect.bottom = _textureRect.top + texInfo.Height;

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
}
