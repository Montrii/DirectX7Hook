#include "pch.h"
#include "framework.h"
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


typedef HRESULT(WINAPI* LPDIRECTDRAWCREATEEX)(GUID FAR* lpGuid, LPVOID* lplpDD, REFIID  iid, IUnknown FAR* pUnkOuter);


typedef HRESULT(WINAPI* IDirectDrawSurface7_DuplicateSurface)(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR* unnamedParam2);
IDirectDrawSurface7_DuplicateSurface real_duplicatesurface = NULL;

HRESULT WINAPI HookedCreateDuplicateSurface(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR* unnamedParam2)
{
    std::cout << "HOOKED DUPLICATE SURFACE" << std::endl;
    return real_duplicatesurface(unnamed, unnamedParam1, unnamedParam2);
}


typedef HRESULT(WINAPI* IDirectDrawSurface7_GetSurfaceFromDC)(IDirectDraw7* unnamed, HDC unnamedParam1, LPDIRECTDRAWSURFACE7* unnamedParam2);
IDirectDrawSurface7_GetSurfaceFromDC real_getsurfaceFromDC = NULL;

HRESULT WINAPI HookedGetSurfaceFromDC(IDirectDraw7* unnamed, HDC unnamedParam1, LPDIRECTDRAWSURFACE7* unnamedParam2)
{
    std::cout << "HOOKED GET SURFACE FROM DC" << std::endl;
    return real_getsurfaceFromDC(unnamed, unnamedParam1, unnamedParam2);
}

typedef HRESULT(WINAPI* IDirectDrawSurface7_GetGDIService)(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 FAR* unnamedParam1);
IDirectDrawSurface7_GetGDIService real_getGDIService = NULL;


HRESULT WINAPI HookedGetGDIService(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 FAR* unnamedParam1)
{
    std::cout << "HOOKED GET SURFACE FROM DC" << std::endl;
    return real_getGDIService(unnamed, unnamedParam1);
}

typedef HRESULT(WINAPI* IDirectDrawSurface7_QueryInterface)(IDirectDraw7* unnamed, REFIID riid, LPVOID FAR* ppvObj);
IDirectDrawSurface7_QueryInterface real_queryInterface = NULL;

HRESULT WINAPI HookedQueryInterface(IDirectDraw7* unnamed, REFIID riid, LPVOID FAR* ppvObj)
{
    std::cout << "HOOKED QUERYINTERFACE" << std::endl;
    return real_queryInterface(unnamed, riid, ppvObj);
}

typedef HRESULT(WINAPI* IDirectDrawSurface7_Flipp)(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, DWORD unnamedParam2);
IDirectDrawSurface7_Flipp real_flip = NULL;

HRESULT WINAPI HookedFlipToGDI(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, DWORD unnamedParam2)
{
    std::cout << "HOOKED FLIPTOGDIDEVICE" << std::endl;
    return real_flip(unnamed, unnamedParam1, unnamedParam2);
}

typedef HRESULT(WINAPI* IDirectDrawSurface7_AddRef)(IDirectDraw7* unnamed);
IDirectDrawSurface7_AddRef real_addref = NULL;

HRESULT WINAPI HookedAddRef(IDirectDraw7* unnamed)
{
    std::cout << "HOOKED ADDREF" << std::endl;
    return real_addref(unnamed);
}

typedef HRESULT(WINAPI* IDirectDrawSurface7_Compact)(void);
IDirectDrawSurface7_Compact real_compact = NULL;

HRESULT WINAPI HookedCompact(void)
{
    std::cout << "HOOKED COMPACT" << std::endl;
    return real_compact();
}

typedef HRESULT(WINAPI* IDirectDrawSurface7_CreateClipper)(IDirectDraw7* unnamed, DWORD unknownParam1, LPDIRECTDRAWCLIPPER FAR* unknownParam2, IUnknown FAR*
    unknownParam3);
IDirectDrawSurface7_CreateClipper real_clipper = NULL;

HRESULT WINAPI HookedCreateClipper(IDirectDraw7* unnamed, DWORD unnamedParam1, LPDIRECTDRAWCLIPPER FAR* unnamedParam2, IUnknown FAR*
    unnamedParam3)
{
    std::cout << "HOOKED CREATE CLIPPER" << std::endl;
    return real_clipper(unnamed, unnamedParam1, unnamedParam2, unnamedParam3);
}

typedef HRESULT(WINAPI* IDirectDrawSurface7_CreatePalette)(IDirectDraw7* unnamed, DWORD unnamedParam1, LPPALETTEENTRY unnamedParam2, LPDIRECTDRAWPALETTE FAR*
    unnamedParam3, IUnknown FAR* unnamedParam4);
IDirectDrawSurface7_CreatePalette real_palette = NULL;

HRESULT WINAPI HookedCreatePalette(IDirectDraw7* unnamed, DWORD unnamedParam1, LPPALETTEENTRY unnamedParam2, LPDIRECTDRAWPALETTE FAR*
    unnamedParam3, IUnknown FAR* unnamedParam4)
{
    std::cout << "HOOKED CREATE PALETTE" << std::endl;
    return real_palette(unnamed, unnamedParam1, unnamedParam2, unnamedParam3, unnamedParam4);
}

typedef HRESULT(WINAPI* IDirectDrawSurface7_CreateSurface)(IDirectDraw7* unnamed, LPDDSURFACEDESC2 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR*
    unnamedParam2, IUnknown FAR* unnamedParam3);
IDirectDrawSurface7_CreateSurface real_surface = NULL;



HRESULT WINAPI HookedCreateSurface(IDirectDraw7* unnamed, LPDDSURFACEDESC2 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR*
    unnamedParam2, IUnknown FAR* unnamedParam3)
{
    std::cout << "HOOKED CREATE SURFACE" << std::endl;

    HRESULT result = real_surface(unnamed, unnamedParam1, unnamedParam2, unnamedParam3);

    if (SUCCEEDED(result))
    {
        std::cout << "IDIRECTDRAWSURFACE7 CREATED" << std::endl;

        /*
        if (detoured == false)
        {
            void** surfaceTable[49];
            memcpy(surfaceTable, *reinterpret_cast<void***>((*unnamedParam2)), sizeof(surfaceTable));
            real_surface_flip = (Surface7_Flip)surfaceTable[11];


            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(&(PVOID&)real_surface_flip, HookedSurfaceFlip);
            std::cout << "DETOUR ATTACHED (SURFACE7 FLIP)" << std::endl;
            if (DetourTransactionCommit() != ERROR_SUCCESS)
            {
                std::cout << "ERROR WHILE CREATING SURFACE7 FLIP HOOK!" << std::endl;
            }
            else
            {
                detoured = true;
            }

            real_surface_blip = (Surface7_Blt)surfaceTable[5];

            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(&(PVOID&)real_surface_blip, HookedSurfaceBlt);
            std::cout << "DETOUR ATTACHED (SURFACE7 Blt)" << std::endl;
            if (DetourTransactionCommit() != ERROR_SUCCESS)
            {
                std::cout << "ERROR WHILE CREATING SURFACE7 Blt HOOK!" << std::endl;
            }
            else
            {
                detoured = true;
            }
        }

        */

    }
    return result;
}
