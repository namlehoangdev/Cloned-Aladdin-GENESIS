#include "SceneHome.h"
#include "dxinput.h"
#include "GameTime.h"
#include "GameManager.h"
#include "Scene1.h"
#include "Scene2.h"

//timing variable
//initializes the game
//debugging purpose
int SceneChanged;
#define KNIFE_X 65
#define KNIFE_UPPERY 130
#define KNIFE_LOWERY 150


SceneHome::SceneHome()
{
	start = GetTickCount();
}
int SceneHome::Game_Init(HWND hwnd)
{
	//init sound files

	mapinfo = new D3DXIMAGE_INFO();
	background = LoadSurface("Res/SceneHomeBackground.png", D3DCOLOR_XRGB(63, 72, 204));
	knifePointer->setSprite(new Sprite("Res\\knifePointer.png", 20, 20));
	knifePointer->set_state_manager(new StateManager("Res\\knifePointerXML.xml"));
	knifePointer->state_manager()->AddToDictState("0", "Idle");
	knifePointer->state_manager()->setState("0");
	knifePointer->setPosition(KNIFE_X, KNIFE_UPPERY);

	//initialize keyboard 
	if (!Init_Keyboard(hwnd))
	{
		MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}
	SceneChanged = false;
	//return oka
	return 1;
}

void SceneHome::Key_Pressed(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_Z:case DIK_RETURN:
		if (knifePointer->Position().y == KNIFE_UPPERY)
			SceneChanged = 1;
		else 
			SceneChanged = 2;

		break;
	case DIK_UP:
	{
		knifePointer->setPosition(KNIFE_X, KNIFE_UPPERY);
		break;
	}
	case DIK_DOWN:
	{
		knifePointer->setPosition(KNIFE_X, KNIFE_LOWERY);
		break;
	}
	}

}

void SceneHome::InputUpdate()
{
	Poll_Keyboard();
	ProcessKeyboard();

	if (Key_Hold(DIK_Z))
	{
		return;
	}
	return;


}


void SceneHome::PhysicsUpdate(float t)
{

}


void SceneHome::GraphicUpdate(float t)
{
	knifePointer->GraphicUpdate(t);
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);
	d3ddev->BeginScene();
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
	knifePointer->setScale(D3DXVECTOR2(1, 1));
	knifePointer->Render(false, true, true);


	sprite_handler->End();
	//stop rendering 
	d3ddev->EndScene();


}


//the main game loop content
void SceneHome::Game_Run(HWND hwnd, int dt)
{

	GameTime::GetInstance()->StartCounter();
	InputUpdate();

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;
	DWORD now = GetTickCount();
	//this keeps the game running at a steady frame rate
	float t = now - start;
	if (t >= 1000 / FPS)
	{
		//reset timing
		start = now;
		Sleep(1000 / FPS);
		PhysicsUpdate(FIXED_TIME);
		GraphicUpdate(FIXED_TIME);
	}
	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);
	//check for escape key (to exit program)	
	if (SceneChanged == 1)
	{

		Scene1* scene1 = new Scene1();
		GameManager::GetInstance()->ReplaceScene(scene1);
	}
	if (SceneChanged==2)
	{

		Scene2* scene2 = new Scene2();
		GameManager::GetInstance()->ReplaceScene(scene2);
	}
	//PostMessage(hwnd, WM_DESTROY, 0, 0);

}

void SceneHome::Game_End(HWND hwnd)
{
	
	Game::Game_End(hwnd);
	delete knifePointer;

}


SceneHome::~SceneHome()
{
}
