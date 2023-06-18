// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
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


// defintions
void RenderText(HDC hdc);
void detourSurfaceFunctions(LPDIRECTDRAWSURFACE7 FAR* unnamedParams2);


//  DirectDrawCreateEx type
typedef HRESULT(WINAPI* LPDIRECTDRAWCREATEEX)(GUID FAR* lpGuid, LPVOID* lplpDD, REFIID  iid, IUnknown FAR* pUnkOuter);

// IDirectDraw7 TYPES
typedef HRESULT(WINAPI* IDirectDrawSurface7_QueryInterface)(IDirectDraw7* unnamed, REFIID riid, LPVOID FAR* ppvObj);
IDirectDrawSurface7_QueryInterface real_queryInterface = NULL;

typedef HRESULT(WINAPI* IDirectDrawSurface7_Flipp)(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, DWORD unnamedParam2);
IDirectDrawSurface7_Flipp real_flip = NULL;

typedef HRESULT(WINAPI* IDirectDrawSurface7_AddRef)(IDirectDraw7* unnamed);
IDirectDrawSurface7_AddRef real_addref = NULL;

typedef HRESULT(WINAPI* IDirectDrawSurface7_Compact)(void);
IDirectDrawSurface7_Compact real_compact = NULL;

typedef HRESULT(WINAPI* IDirectDrawSurface7_CreateClipper)(IDirectDraw7* unnamed, DWORD unknownParam1, LPDIRECTDRAWCLIPPER FAR* unknownParam2, IUnknown FAR*
    unknownParam3);
IDirectDrawSurface7_CreateClipper real_clipper = NULL;

typedef HRESULT(WINAPI* IDirectDrawSurface7_CreatePalette)(IDirectDraw7* unnamed, DWORD unnamedParam1, LPPALETTEENTRY unnamedParam2, LPDIRECTDRAWPALETTE FAR*
    unnamedParam3, IUnknown FAR* unnamedParam4);
IDirectDrawSurface7_CreatePalette real_palette = NULL;

typedef HRESULT(WINAPI* IDirectDrawSurface7_CreateSurface)(IDirectDraw7* unnamed, LPDDSURFACEDESC2 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR*
    unnamedParam2, IUnknown FAR* unnamedParam3);
IDirectDrawSurface7_CreateSurface real_surface = NULL;

typedef HRESULT(WINAPI* IDirectDrawSurface7_DuplicateSurface)(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR* unnamedParam2);
IDirectDrawSurface7_DuplicateSurface real_duplicatesurface = NULL;

typedef HRESULT(WINAPI* IDirectDrawSurface7_GetSurfaceFromDC)(IDirectDraw7* unnamed, HDC unnamedParam1, LPDIRECTDRAWSURFACE7* unnamedParam2);
IDirectDrawSurface7_GetSurfaceFromDC real_getsurfaceFromDC = NULL;

typedef HRESULT(WINAPI* IDirectDrawSurface7_GetGDIService)(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 FAR* unnamedParam1);
IDirectDrawSurface7_GetGDIService real_getGDIService = NULL;

// IDirectDraw7 Hooked Functions

HRESULT WINAPI HookedQueryInterface(IDirectDraw7* unnamed, REFIID riid, LPVOID FAR* ppvObj)
{
    std::cout << "HOOKED QUERYINTERFACE" << std::endl;
    return real_queryInterface(unnamed, riid, ppvObj);
}

HRESULT WINAPI HookedFlipToGDI(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, DWORD unnamedParam2)
{
    std::cout << "HOOKED FLIPTOGDIDEVICE" << std::endl;
    return real_flip(unnamed, unnamedParam1, unnamedParam2);
}

HRESULT WINAPI HookedAddRef(IDirectDraw7* unnamed)
{
    std::cout << "HOOKED ADDREF" << std::endl;
    return real_addref(unnamed);
}

HRESULT WINAPI HookedCompact(void)
{
    std::cout << "HOOKED COMPACT" << std::endl;
    return real_compact();
}

HRESULT WINAPI HookedCreateClipper(IDirectDraw7* unnamed, DWORD unnamedParam1, LPDIRECTDRAWCLIPPER FAR* unnamedParam2, IUnknown FAR*
    unnamedParam3)
{
    std::cout << "HOOKED CREATE CLIPPER" << std::endl;
    return real_clipper(unnamed, unnamedParam1, unnamedParam2, unnamedParam3);
}

HRESULT WINAPI HookedCreatePalette(IDirectDraw7* unnamed, DWORD unnamedParam1, LPPALETTEENTRY unnamedParam2, LPDIRECTDRAWPALETTE FAR*
    unnamedParam3, IUnknown FAR* unnamedParam4)
{
    std::cout << "HOOKED CREATE PALETTE" << std::endl;
    return real_palette(unnamed, unnamedParam1, unnamedParam2, unnamedParam3, unnamedParam4);
}

HRESULT WINAPI HookedCreateDuplicateSurface(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR* unnamedParam2)
{
    std::cout << "HOOKED DUPLICATE SURFACE" << std::endl;
    return real_duplicatesurface(unnamed, unnamedParam1, unnamedParam2);
}

HRESULT WINAPI HookedGetSurfaceFromDC(IDirectDraw7* unnamed, HDC unnamedParam1, LPDIRECTDRAWSURFACE7* unnamedParam2)
{
    std::cout << "HOOKED GET SURFACE FROM DC" << std::endl;
    return real_getsurfaceFromDC(unnamed, unnamedParam1, unnamedParam2);
}

HRESULT WINAPI HookedGetGDIService(IDirectDraw7* unnamed, LPDIRECTDRAWSURFACE7 FAR* unnamedParam1)
{
    std::cout << "HOOKED GET SURFACE FROM DC" << std::endl;
    return real_getGDIService(unnamed, unnamedParam1);
}

bool detoured = false;
HRESULT WINAPI HookedCreateSurface(IDirectDraw7* unnamed, LPDDSURFACEDESC2 unnamedParam1, LPDIRECTDRAWSURFACE7 FAR*
    unnamedParam2, IUnknown FAR* unnamedParam3)
{
    std::cout << "HOOKED CREATE SURFACE" << std::endl;

    HRESULT result = real_surface(unnamed, unnamedParam1, unnamedParam2, unnamedParam3);

    if (SUCCEEDED(result))
    {
        if (detoured == false)
        {
            detourSurfaceFunctions(unnamedParam2);
        }
    }
    return result;
}


// IDirectDrawSurface7 Types

typedef HRESULT(WINAPI* Surface7_Blt)(IDirectDrawSurface7* unnamed, LPRECT unnamedParam1, LPDIRECTDRAWSURFACE7 unnamedParam2, LPRECT
    unnamedParam3, DWORD unnamedParam4, LPDDBLTFX unnamedParam5);
Surface7_Blt real_surface_blip = NULL;

typedef HRESULT(WINAPI* Surface7_Flip)(IDirectDrawSurface7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, DWORD unnamedParam2);
Surface7_Flip real_surface_flip = NULL;

typedef HRESULT(WINAPI* Surface7_Lock)(IDirectDrawSurface7* unnamed, LPRECT unnamedParam1, LPDDSURFACEDESC2 unnamedParam2, DWORD
    unnamedParam3, HANDLE unnamedParam4);
Surface7_Lock real_surface_lock = NULL;

typedef HRESULT(WINAPI* Surface7_IsLock)(IDirectDrawSurface7* unnamed);
Surface7_IsLock real_surface_islock = NULL;

// IDirectDrawSurface7 Hooked Functions

HRESULT WINAPI HookedSurfaceBlt(IDirectDrawSurface7* unnamed, LPRECT unnamedParam1, LPDIRECTDRAWSURFACE7 unnamedParam2, LPRECT
    unnamedParam3, DWORD unnamedParam4, LPDDBLTFX unnamedParam5)
{
    HRESULT result = real_surface_blip(unnamed, unnamedParam1, unnamedParam2, unnamedParam3, unnamedParam4, unnamedParam5);
    std::cout << "HOOKED SURFACE BLT" << std::endl;
    return result;
}

HRESULT WINAPI HookedSurfaceFlip(IDirectDrawSurface7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, DWORD unnamedParam2)
{
    HRESULT result = real_surface_flip(unnamed, unnamedParam1, unnamedParam2);
    std::cout << "HOOKED SURFACE FLIP" << std::endl;
    return result;
}

HRESULT WINAPI HookedSurfaceLock(IDirectDrawSurface7* unnamed, LPRECT unnamedParam1, LPDDSURFACEDESC2 unnamedParam2, DWORD
    unnamedParam3, HANDLE unnamedParam4)
{
    HRESULT result = real_surface_lock(unnamed, unnamedParam1, unnamedParam2, unnamedParam3, unnamedParam4);
    std::cout << "HOOKED SURFACE LOCK" << std::endl;
    return result;
}

HRESULT WINAPI HookedSurfaceIsLock(IDirectDrawSurface7* unnamed)
{
    HRESULT result = real_surface_islock(unnamed);
    std::cout << "HOOKED ISLOCK SURFACE" << std::endl;
    return result;
}




// Detour Functions

void detourSurfaceFunctions(LPDIRECTDRAWSURFACE7 FAR* unnamedParam2)
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

    real_surface_lock = (Surface7_Lock)surfaceTable[25];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_surface_lock, HookedSurfaceLock);
    std::cout << "DETOUR ATTACHED (SURFACE7 Lock)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING SURFACE7 Lock HOOK!" << std::endl;
    }
    else
    {
        detoured = true;
    }

    real_surface_islock = (Surface7_IsLock)surfaceTable[24];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_surface_islock, HookedSurfaceIsLock);
    std::cout << "DETOUR ATTACHED (SURFACE7 ISLOCK)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING SURFACE7 ISLOCK HOOK!" << std::endl;
    }
    else
    {
        detoured = true;
    }
}

void detouringDirectDrawFunctions(void** table)
{
    real_flip = (IDirectDrawSurface7_Flipp)table[11];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_flip, HookedFlipToGDI);
    std::cout << "DETOUR ATTACHED (FLIPTOGDISERVICE)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING FLIP HOOK!" << std::endl;
    }

    real_queryInterface = (IDirectDrawSurface7_QueryInterface)table[0];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_queryInterface, HookedQueryInterface);
    std::cout << "DETOUR ATTACHED (QUERYINTERFACE)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING QUERYINTERFACE HOOK!" << std::endl;
    }

    real_addref = (IDirectDrawSurface7_AddRef)table[1];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_addref, HookedAddRef);
    std::cout << "DETOUR ATTACHED (ADDREF)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING ADDREF HOOK!" << std::endl;
    }

    real_compact = (IDirectDrawSurface7_Compact)table[3];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_compact, HookedCompact);
    std::cout << "DETOUR ATTACHED (COMPACT)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING COMPACT HOOK!" << std::endl;
    }


    real_clipper = (IDirectDrawSurface7_CreateClipper)table[4];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_clipper, HookedCreateClipper);
    std::cout << "DETOUR ATTACHED (CREATECLIPPER)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING CREATECLIPPER HOOK!" << std::endl;
    }


    real_palette = (IDirectDrawSurface7_CreatePalette)table[5];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_palette, HookedCreatePalette);
    std::cout << "DETOUR ATTACHED (CREATEPALETTE)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING CREATEPALETTE HOOK!" << std::endl;
    }

    real_surface = (IDirectDrawSurface7_CreateSurface)table[6];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_surface, HookedCreateSurface);
    std::cout << "DETOUR ATTACHED (CREATESURFACE)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING CREATESURFACE HOOK!" << std::endl;
    }

    real_duplicatesurface = (IDirectDrawSurface7_DuplicateSurface)table[7];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_duplicatesurface, HookedCreateDuplicateSurface);
    std::cout << "DETOUR ATTACHED (DUPLICATESURFACE)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING DUPLICATESURFACE HOOK!" << std::endl;
    }


    real_getsurfaceFromDC = (IDirectDrawSurface7_GetSurfaceFromDC)table[24];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_getsurfaceFromDC, HookedGetSurfaceFromDC);
    std::cout << "DETOUR ATTACHED (GETSURFACEFROMDC)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING GETSURFACEFROMDC HOOK!" << std::endl;
    }


    real_getGDIService = (IDirectDrawSurface7_GetGDIService)table[15];

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_getGDIService, HookedGetGDIService);
    std::cout << "DETOUR ATTACHED (GETGDISERVICE)" << std::endl;
    if (DetourTransactionCommit() != ERROR_SUCCESS)
    {
        std::cout << "ERROR WHILE CREATING GETGDISERVICE HOOK!" << std::endl;
    }
}





// MAIN THREAD AND DLL ENTRY

void mainThread()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    HMODULE ddraw = GetModuleHandleA("ddraw.dll");
    void* ddrawTable[49];
    if (ddraw)
    {
        LPDIRECTDRAW7 pDDraw = nullptr;
        auto pDDCreate = reinterpret_cast<LPDIRECTDRAWCREATEEX>(GetProcAddress(ddraw, "DirectDrawCreateEx"));
        if (pDDCreate)
        {
            HRESULT hr = pDDCreate(NULL, reinterpret_cast<LPVOID*>(&pDDraw), IID_IDirectDraw7, NULL);
            if (SUCCEEDED(hr))
            {
                memcpy(ddrawTable, *reinterpret_cast<void***>(pDDraw), sizeof(ddrawTable));
                pDDraw->Release();
                detouringDirectDrawFunctions((void**)ddrawTable);
            }
            else
            {
                std::cout << "didnt work!!" << std::endl;
            }
        }
    }
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mainThread, NULL, NULL, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

