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
	float frameInterval, D3DCOLOR textureColor)
{
	_spriteDX = spriteDX;
	_textureDX = textureDX;
	_frameInterval = frameInterval;

	// ����� ���� ����
	_textureRect.left = left;
	_textureRect.right = _textureRect.left + width;
	_textureRect.top = top;
	_textureRect.bottom = _textureRect.top + height;

	_textureColor = textureColor;

	_width = width;
	_height = height;
}

void Frame::Render()
{
	// Ȯ�� ���
	D3DXVECTOR2 scale = D3DXVECTOR2(1.0f, 1.0f);

	// ȸ�� �߽�
	D3DXVECTOR2 rotCenter = D3DXVECTOR2(_width*0.5f, _height*0.5f);

	// ȸ�� ����
	float rot = 0.0f;

	// �̵�
	D3DXVECTOR2 translate = D3DXVECTOR2(0.0f, 0.0f);

	D3DXMATRIX matrix;	// ũ��, ȸ��, ȸ�� �߽�, ȸ�� ����, �̵�
	D3DXMatrixTransformation2D(
		&matrix,		// ���� ���
		NULL,		// �������� �߽���
		0.0f,		// Ȯ�� ȸ�� ��ų ��, x,y�� ������ �ٸ� ��� ���� ��
		&scale,		// Ȯ��/���
		&rotCenter,	// ȸ�� �߽���
		rot,	// ȸ�� ����
		&translate);

	_spriteDX->SetTransform(&matrix);
	_spriteDX->Draw(_textureDX, &_textureRect, NULL, NULL,_textureColor);	// 2D �̹��� ��� ����. Texture(�ؽ���)
}

void Frame::Reset()
{
}
