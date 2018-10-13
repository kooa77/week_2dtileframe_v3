#include <fstream>
#include <string>

#include <d3dx9.h>
#include <reader.h>

#include "Frame.h"
#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	for (int i = 0; i < _frameList.size(); i++)
	{
		delete _frameList[i];
	}
	_frameList.clear();

	if (_textureDX)
	{
		_textureDX->Release();
		_textureDX = NULL;
	}
}

void Sprite::Init(std::wstring fileName,
	std::wstring scriptName,
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

		//std::string fileName = "Test.json";
		std::ifstream infile(scriptName);
		if (infile.is_open())
		{
			char recordString[1000];
			while (false == infile.eof())
			{
				infile.getline(recordString, 1000);

				// Parsing
				Json::Value root;
				Json::Reader reader;
				bool isSuccess = reader.parse(recordString, root);
				if (true == isSuccess)
				{
					// 파싱된 값을 적용
					int x = root["x"].asInt();
					int y = root["y"].asInt();
					int width = root["width"].asInt();
					int height = root["height"].asInt();
					float frameInterval = root["frameInterval"].asDouble();

					Frame* frame = new Frame();
					frame->Init(_spriteDX, _textureDX,
						x, y, width, height, frameInterval,
						D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f);
					_frameList.push_back(frame);
				}
			}
		}

		/*
		{	// frame 1
			Frame* frame = new Frame();
			frame->Init(_spriteDX, _textureDX, 0, 0, 32, 32, 0.5f, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f);
			_frameList.push_back(frame);
		}
		{	// frame 2
			Frame* frame = new Frame();
			frame->Init(_spriteDX, _textureDX, 64, 0, 32, 32, 0.5f, D3DCOLOR_ARGB(255, 255, 0, 0), 1.5f);
			_frameList.push_back(frame);
		}
		*/
		/*
		{
			Frame* frame = new Frame();
			frame->Init(_spriteDX, _textureDX, 0, 0, 32, 32, 0.4f);
			_frameList.push_back(frame);
		}
		{
			Frame* frame = new Frame();
			frame->Init(_spriteDX, _textureDX, 64, 0, 32, 32, 0.4f);
			_frameList.push_back(frame);
		}
		{
			Frame* frame = new Frame();
			frame->Init(_spriteDX, _textureDX, 0, 0, 32, 32, 0.2f);
			_frameList.push_back(frame);
		}
		{
			Frame* frame = new Frame();
			frame->Init(_spriteDX, _textureDX, 64, 0, 32, 32, 0.2f);
			_frameList.push_back(frame);
		}
		*/
		_frameIdx = 0;
		_frameDuration = 0.0f;
	}
}

void Sprite::Update(float deltaTime)
{
	// 현재 프레임이 출력된 후 흐른 시간
	_frameDuration += deltaTime;
	if (_frameList[_frameIdx]->GetFrameInterval() <= _frameDuration)
	{
		_frameDuration = 0.0f;
		_frameIdx++;
		if (_frameList.size() <= _frameIdx)
		{
			_frameIdx = 0;
		}
	}
}

void Sprite::Render()
{
	if (_frameIdx < _frameList.size())
	{
		_frameList[_frameIdx]->SetPosition(_x, _y);
		_frameList[_frameIdx]->Render();
	}
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

	for (int i = 0; i < _frameList.size(); i++)
	{
		_frameList[i]->Reset();
	}
}

void Sprite::SetPosition(float x, float y)
{
	_x = x;
	_y = y;
}
