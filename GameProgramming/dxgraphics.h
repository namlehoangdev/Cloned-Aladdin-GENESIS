#ifndef _DXGRAPHICS_H
#define _DXGRAPHICS_H

#define FPS 35
#define SCALE_RATE 2.1
#include <d3d9.h>
#include <d3dx9.h>
//function prototypes
int Init_Direct3D(HWND, int, int, int);
LPDIRECT3DSURFACE9 LoadSurface(char *, D3DCOLOR);
LPDIRECT3DTEXTURE9 LoadTexture(char *, D3DCOLOR, D3DXIMAGE_INFO*);
void CreateHWND(HINSTANCE Hinstance, DWORD style);
//variable declarations
extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;
extern LPD3DXSPRITE sprite_handler;
extern D3DXMATRIX old_matrix;
extern HWND hwnd;
#endif
