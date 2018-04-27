#include "sprite.h"
#include "game.h"

int Sprite::NUMBER_SPRITE_CREATED = 0;
int Sprite::NUMBER_SPRITE_DELETED = 0;
int Sprite::COUNT = 0;

Sprite::Sprite(LPCSTR FilePath, int Width, int Height,D3DCOLOR color)
{
	_id = COUNT++;
	//OutputDebugString("Tao ra sprite");
	//OutputDebugString(std::to_string(_id).c_str());
	//OutputDebugString("\n");
	NUMBER_SPRITE_CREATED++;
	D3DXIMAGE_INFO info;
	HRESULT result;
	_image = NULL;
	_width = Width;
	_height = Height;
	try
	{
		result = D3DXGetImageInfoFromFile(FilePath, &info);
		if (result != D3D_OK)
		{
			return;
		}
		result = D3DXCreateTextureFromFileEx(
			d3ddev,
			FilePath,
			info.Width,
			info.Height,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			color,
			&info,
			NULL,
			&_image
		);
		if (result != D3D_OK)
		{
			return;
		}
	}
	catch(int e)
	{
		return;
	}
	
}

Sprite::Sprite()
{
	_id = COUNT++;
	//OutputDebugString("Tao ra sprite");
	//OutputDebugString(std::to_string(_id).c_str());
	//OutputDebugString("\n");
	//if(_id == 4 || _id == 7 || _id == 10 || _id == 15 || _id == 18 || _id == 27 || _id == 32 || _id == 36 || (_id >=40 && _id <=45))
	//{
	//	OutputDebugString("Hello");
	//	int a = 5;
	//}
	NUMBER_SPRITE_CREATED++;
}


Sprite::~Sprite()
{
	//OutputDebugString("Huy bo sprite");
	//OutputDebugString(std::to_string(_id).c_str());
	//OutputDebugString("\n");
	NUMBER_SPRITE_DELETED++;
	if(_image)
		_image->Release();
}
