#include "Frame.h"

Frame::Frame()
{
	_frameInterval = 0.2f;
}

Frame::~Frame()
{
}

void Frame::Init(ID3DXSprite* spriteDX, IDirect3DTexture9* textureDX,
	int left, int top, int width, int height,
	float frameInterval)
{
	_spriteDX = spriteDX;
	_textureDX = textureDX;
	_frameInterval = frameInterval;

	// ����� ���� ����
	_textureRect.left = left;
	_textureRect.right = _textureRect.left + width;
	_textureRect.top = top;
	_textureRect.bottom = _textureRect.top + height;

	_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void Frame::Render()
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

void Frame::Reset()
{
}
