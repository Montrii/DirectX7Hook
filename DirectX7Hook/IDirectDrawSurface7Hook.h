#include "pch.h"
#include "IDirectDraw7Hook.h"


typedef HRESULT(WINAPI* Surface7_Blt)(IDirectDrawSurface7* unnamed, LPRECT unnamedParam1, LPDIRECTDRAWSURFACE7 unnamedParam2, LPRECT
    unnamedParam3, DWORD unnamedParam4, LPDDBLTFX unnamedParam5);
Surface7_Blt real_surface_blip = NULL;


HRESULT WINAPI HookedSurfaceBlt(IDirectDrawSurface7* unnamed, LPRECT unnamedParam1, LPDIRECTDRAWSURFACE7 unnamedParam2, LPRECT
    unnamedParam3, DWORD unnamedParam4, LPDDBLTFX unnamedParam5)
{
    // render first
    HRESULT result = real_surface_blip(unnamed, unnamedParam1, unnamedParam2, unnamedParam3, unnamedParam4, unnamedParam5);
    std::cout << "HOOKED SURFACE BLT" << std::endl;
    return result;
}

typedef HRESULT(WINAPI* Surface7_Flip)(IDirectDrawSurface7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, DWORD unnamedParam2);
Surface7_Flip real_surface_flip = NULL;

HRESULT WINAPI HookedSurfaceFlip(IDirectDrawSurface7* unnamed, LPDIRECTDRAWSURFACE7 unnamedParam1, DWORD unnamedParam2)
{
    // render first
    HRESULT result = real_surface_flip(unnamed, unnamedParam1, unnamedParam2);
    std::cout << "HOOKED SURFACE FLIP" << std::endl;

    return result;
}