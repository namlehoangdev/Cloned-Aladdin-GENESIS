#include "Scene1BackGround.h"
#include "GameManager.h"
#include <xmmintrin.h>


void Scene1BackGround::LoadRectByXML()
{
	xml_document fileXml;
	xml_parse_result result = fileXml.load_file("Res/BackgroundScene1XML.xml");
	xml_node root = fileXml.child("Animations");


	vector <RECT> srcRect;
	vector <D3DXVECTOR3> srcPos;
	int posY = 0;

	for (xml_node nodeAnimation = root.first_child(); nodeAnimation; nodeAnimation = nodeAnimation.next_sibling())
	{

		string name = nodeAnimation.attribute("name").value();

		for (xml_node nodeRec = nodeAnimation.first_child(); nodeRec; nodeRec = nodeRec.next_sibling())
		{
			RECT rect;
			rect.top = atoi(nodeRec.attribute("y").value()) ;
			rect.left = atoi(nodeRec.attribute("x").value());
			rect.bottom = atoi(nodeRec.attribute("h").value()) + rect.top;
			rect.right = atoi(nodeRec.attribute("w").value()) + rect.left;
			srcRect.push_back(rect);

			D3DXVECTOR3 pos = D3DXVECTOR3(0, posY,0);
			posY += atoi(nodeRec.attribute("h").value());
			srcPos.push_back(pos);

		}

	
	}
	for (int i = 0; i < 5; i++)
	{
		_rect[i] = srcRect.at(i);
		_position[i] = srcPos.at(i);
	}

	
}

void Scene1BackGround::Render()

{
	Update();
	sprite_handler->SetTransform(&backgroundMatrix);

	for(int i = 0 ; i < 4;i++)
	{
		sprite_handler->Draw(
			_sprite->image(),
			&_rect[i],
			NULL,
			new D3DXVECTOR3(_position[i].x - _index[i]*_speed[i],_position[i].y,0),
			D3DCOLOR_XRGB(255, 255, 255)
		);
		sprite_handler->Draw(
			_sprite->image(),
			&_rect[i],
			NULL,
			new D3DXVECTOR3(_position[i].x - _index[i]*_speed[i] + _rect[i].right, _position[i].y, 0),
			D3DCOLOR_XRGB(255, 255, 255)
		);
	}

	sprite_handler->Draw(
		_sprite->image(),
		&_rect[4],
		NULL,
		&_position[4],
		D3DCOLOR_XRGB(255, 255, 255)
	);




	sprite_handler->SetTransform(&old_matrix);

}

void Scene1BackGround::Update()
{
	for (int i = 0; i < 4; i++)
	{
		_index[i] = (_index[i] + 1) % _maxindex[i];
	}
}

Scene1BackGround::Scene1BackGround()
{
	for (int i = 0; i < 4; i++)
	{
		_index[i]= 0;
		_maxindex[i] = 640 / _speed[i];
	}
	_sprite = new Sprite("Res/EnhancedScene1Background.png", 640, 480);
	LoadRectByXML();
	D3DXMATRIX rota, trans, scale;
	D3DXMatrixScaling(&scale, 1,1, 1);
	D3DXMatrixTranslation(&trans, 0, 0, 0);
	D3DXMatrixRotationX(&rota, 0);

	backgroundMatrix = rota*scale*trans;

}


Scene1BackGround::~Scene1BackGround()
{
}
