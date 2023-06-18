#pragma once
#include "pch.h"
#include "dllmain.cpp"

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
