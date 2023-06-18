#pragma once

#include "detours.h"
#include <ddraw.h>
#include <windows.h>
#include <iostream>
#include <d3d.h>
#pragma comment( lib, "ddraw.lib" )
#pragma  comment( lib, "dxguid.lib" )
#pragma comment(lib, "detours.lib")
#include <winuser.h>
#include <vector>


// typedefs
typedef HRESULT(WINAPI* LPDIRECTDRAWCREATEEX)(GUID FAR* lpGuid, LPVOID* lplpDD, REFIID  iid, IUnknown FAR* pUnkOuter);

typedef HRESULT(WINAPI* IDirectDrawSurface7_QueryInterface)(IDirectDraw7* unnamed, REFIID riid, LPVOID FAR* ppvObj);


typedef HRESULT(WINAPI* IDirectDrawSurface7_Flipp)(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, DWORD unnamedParam2);

typedef HRESULT(WINAPI* IDirectDrawSurface7_AddRef)(IDirectDraw7* unnamed);

typedef HRESULT(WINAPI* IDirectDrawSurface7_Compact)(void);

typedef HRESULT(WINAPI* IDirectDrawSurface7_CreateClipper)(IDirectDraw7* unnamed, DWORD unknownParam1, LPDIRECTDRAWCLIPPER FAR* unknownParam2, IUnknown FAR*
	unknownParam3);

typedef HRESULT(WINAPI* IDirectDrawSurface7_CreatePalette)(IDirectDraw7* unnamed, DWORD unnamedParam1, LPPALETTEENTRY unnamedParam2, LPDIRECTDRAWPALETTE FAR*
	unnamedParam3, IUnknown FAR* unnamedParam4);

typedef HRESULT(WINAPI* IDirectDrawSurface7_CreateSurface)(IDirectDraw7* unnamed, LPDDSURFACEDESC2 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR*
	unnamedParam2, IUnknown FAR* unnamedParam3);

typedef HRESULT(WINAPI* IDirectDrawSurface7_DuplicateSurface)(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR* unnamedParam2);



class DirectHook
{
public:
	void hookFunctions();
	IDirectDrawSurface7_QueryInterface real_queryInterface = NULL;
	IDirectDrawSurface7_Flipp real_flip = NULL;
	IDirectDrawSurface7_AddRef real_addref = NULL;
	IDirectDrawSurface7_Compact real_compact = NULL;
	IDirectDrawSurface7_CreateClipper real_clipper = NULL;
	IDirectDrawSurface7_CreatePalette real_palette = NULL;
	IDirectDrawSurface7_CreateSurface static real_surface;
	IDirectDrawSurface7_DuplicateSurface real_duplicatesurface = NULL;

private:
	// hooks

	void detourFunctions(void** table);
	HRESULT WINAPI HookedQueryInterface(IDirectDraw7* unnamed, REFIID riid, LPVOID FAR* ppvObj);
	HRESULT WINAPI HookedFlipToGDI(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, DWORD unnamedParam2);
	HRESULT WINAPI HookedAddRef(IDirectDraw7* unnamed);
	HRESULT WINAPI HookedCompact(void);
	HRESULT WINAPI HookedCreateClipper(IDirectDraw7* unnamed, DWORD unnamedParam1, LPDIRECTDRAWCLIPPER FAR* unnamedParam2, IUnknown FAR*
		unnamedParam3);
	HRESULT WINAPI HookedCreatePalette(IDirectDraw7* unnamed, DWORD unnamedParam1, LPPALETTEENTRY unnamedParam2, LPDIRECTDRAWPALETTE FAR*
		unnamedParam3, IUnknown FAR* unnamedParam4);
	static HRESULT WINAPI HookedCreateSurface(IDirectDraw7* unnamed, LPDDSURFACEDESC2 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR*
		unnamedParam2, IUnknown FAR* unnamedParam3)
	{
		std::cout << "HOOKED CREATE SURFACE" << std::endl;
		return real_surface(unnamed, unnamedParam1, unnamedParam2, unnamedParam3);
	}
	HRESULT WINAPI HookedCreateDuplicateSurface(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR* unnamedParam2);
};

