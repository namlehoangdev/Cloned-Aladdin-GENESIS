#include "dxinput.h"
#define BUTTON_DOWN(obj, button) (obj.rgbButtons[button] & 0x80)

LPDIRECTINPUT8 dinput;
LPDIRECTINPUTDEVICE8 dikeyboard;
DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];
//keyboard input
char keys[256];
int Init_DirectInput(HWND hwnd)
{
	//initialize DirectInput object
	HRESULT result = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&dinput,
		NULL
	);
	if (result != DI_OK)
		return 0;
	//initialize the keyboard
	result = dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
	if (result != DI_OK)
		return 0;
	//clean return
	return 1;
}
int Init_Keyboard(HWND hWnd)
{
	//set the data format for keyboard input
	HRESULT result = dikeyboard->SetDataFormat(&c_dfDIKeyboard); 
	if (result != DI_OK)
		return 0;
	//set the cooperative level
	result = dikeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
		return 0;

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size
	result = dikeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (result != DI_OK)
		return 0;
	//accquire the keyboard
	result = dikeyboard->Acquire();

	if (result != DI_OK)
		return 0;
	//give a go ahead
	return 1;
}

void Poll_Keyboard()
{
	if(dikeyboard!=nullptr)
		dikeyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
}
int Key_Hold(int key)
{
	return (keys[key] & 0x80);
}

void Key_Pressed(int)
{

}


void Kill_Keyboard()
{
	if (dikeyboard!=NULL)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL;
	}
}
