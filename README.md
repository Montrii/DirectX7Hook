
# DirectX 7 Hook

This repository showcases to you how to successfully hook DirectX 7 (ddraw.dll), in order to draw your own application. 

It only fulfills documentary and educational purposes.

The two interfaces responsible for rendering and drawing your stuff onto your game are [IDirectDraw7](https://learn.microsoft.com/en-us/windows/win32/api/ddraw/nn-ddraw-idirectdraw7) and [IDirectDrawSurface7](https://learn.microsoft.com/en-us/windows/win32/api/ddraw/nn-ddraw-idirectdrawsurface7).











## Approachment

As of creating this respository, i did not really have alot of understanding of how hooking functions, especially drawing functions, worked. 

However due to the broad amount of information (Linked down below), i was able to figure out alot of it.

After digging through the internet, i have come to the conclusion that the [IDirectDrawSurface7::Blt](https://learn.microsoft.com/en-us/windows/win32/api/ddraw/nf-ddraw-idirectdrawsurface7-blt) and [IDirectDrawSurface7::Flip](https://learn.microsoft.com/en-us/windows/win32/api/ddraw/nf-ddraw-idirectdrawsurface7-flip) were indeed responsible for drawing information, which was all the information i needed in order to actually start coding.

In order to hopefully make this respository global for every DirectX 7 Game, it was decided upon not use any function pointers or pointers in general of any game, so that the project itself would stay loyal to its purpose.

How did i hook the functions?

By getting its function pointer through the virtual Table of DirectX 7 (same as many DirectX 9 Hookers work).
Lookup [ddraw.h](https://github.com/apitrace/dxsdk/blob/master/Include/ddraw.h) to understand where the function pointers are located in the structure.

Only thing worth noting is in order to get a [IDirectDrawSurface7](https://learn.microsoft.com/en-us/windows/win32/api/ddraw/nn-ddraw-idirectdrawsurface7) pointer, we hook the [IDirectDraw7::CreateSurface](https://learn.microsoft.com/en-us/windows/win32/api/ddraw/nf-ddraw-idirectdraw7-createsurface) function and then we can detour its functions aswell.

The code might be sloppy, i am open for improvements, however it does work.


## Compiling

In order to compile this project, use C++14, with the x86 option turned on.  
It does **not** work with 64 Bit.

This project compiles to a **.dll**, that you can then inject into your game with any available DLL-Injector.



## Contributing

Contributions are always welcome!

Worth noting:

- [unknowncheats](https://www.unknowncheats.me/forum/direct3d/67535-directdraw-hook-hooks-directx-7-a.html) - (giving a broad idea on how it works).
- [Detours](https://github.com/microsoft/Detours)


## Authors

- [@Montri](https://www.github.com/Montrii)





## License

[MIT](https://choosealicense.com/licenses/mit/)

