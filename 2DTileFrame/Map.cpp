#include "Sprite.h"
#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::Init(LPDIRECT3DDEVICE9 dxDevice, ID3DXSprite* spriteDX)
{
	// 맵용 스프라이트 리스트 작업.
	// 타일 갯수하고 개별 타일 크기 합의 완료 (32x32, 256)
	int srcX = 0;
	int srcY = 0;
	int tileSize = 32;
	LPCWSTR fileName = L"../Resources/Images/PathAndObjects.png";
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			Sprite* sprite = new Sprite();
			sprite->Init(fileName,
				srcX, srcY, tileSize, tileSize, 1.0f,
				dxDevice, spriteDX);
			_spriteList.push_back(sprite);

			srcX += tileSize;
		}

		srcX = 0;
		srcY += tileSize;
	}

	int tileMapIndex[16][16];
	int idx = 0;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			//tileMapIndex[y][x] = idx++;
			tileMapIndex[y][x] = 17;
		}
	}
	
	//0,1,2,1...
	//16,17,18,1...
	tileMapIndex[0][0] = 0;
	tileMapIndex[0][1] = 1;
	tileMapIndex[0][2] = 2;
	tileMapIndex[1][0] = 16;
	tileMapIndex[1][1] = 17;
	tileMapIndex[1][2] = 18;

	// 스프라이트를  생성
	//LPCWSTR fileName = L"../Resources/Images/PathAndObjects.png";
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			int spriteIndex = tileMapIndex[y][x];
			_tileSprite[y][x] = _spriteList[spriteIndex];
			/*
			_tileSprite[y][x] = new Sprite();
			LPCWSTR scriptName = L"Test.json";

			int index = tileMapIndex[y][x];
			switch (index)
			{
			case 0:
				scriptName = L"PlayerLeft.json";
				break;
			case 1:
				scriptName = L"PlayerRight.json";
				break;
			case 2:
				scriptName = L"PlayerUp.json";
				break;
			case 3:
				scriptName = L"PlayerDown.json";
				break;
			}

			_tileSprite[y][x]->Init(fileName, scriptName, dxDevice, spriteDX);
			*/
		}
	}
}

void Map::Update(float deltaTime)
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->Update(deltaTime);
		}
	}
}

void Map::Render()
{
	float startX = 0.0f;
	float startY = 0.0f;
	float posX = startX;
	float posY = startY;
	int tileSize = 32;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->SetPosition(posX + 30, posY + 30);
			_tileSprite[y][x]->Render();
			posX += (tileSize);
		}
		posX = startX;
		posY += (tileSize);
	}
}

void Map::Release()
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->Release();
		}
	}
}

void Map::Reset()
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->Reset();
		}
	}
}

void Map::Deinit()
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			if (NULL != _tileSprite[y][x])
			{
				delete _tileSprite[y][x];
			}
		}
	}
}
