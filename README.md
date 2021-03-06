<p align="center">
<img src="https://github.com/LunaRyuko/LunarViewer/blob/main/docs/lv_logo_256.png">

<h1 align="center">LunarViewer</h1>

<p align="center">
<a href="https://github.com/LunaRyuko/LunarViewer/actions/workflows/windows.yml"><img src="https://github.com/LunaRyuko/LunarViewer/actions/workflows/windows.yml/badge.svg?branch=main" alt="Windows (x64)"></a>
<a href="https://github.com/LunaRyuko/LunarViewer/actions/workflows/linux.yml"><img src="https://github.com/LunaRyuko/LunarViewer/actions/workflows/linux.yml/badge.svg?branch=main" alt="Linux (x64)"></a><br>
A model viewer for Quake 1 and Hexen 2 with a focus on accurate representation.<br><br>
<img align="center" src="https://github.com/LunaRyuko/LunarViewer/blob/main/docs/viewer_pic.png"><br><br>
Powered by raylib and dear imgui!
</p>

## Features

 - Support for Quake 1 (IDPO) and Hexen 2 (RAPO) model formats
 - Hardware-accelerated with OpenGL, while still maintaining the software renderer look
 - Vertices are transformed and animated all on the GPU via a vertex shader
 - Supports previewing animations with interpolation

## Known issues

 - Linux doesn't have a File Select Dialog yet. The model needs to be loaded via a launch argument (like `LunarViewer ~/id1/progs/shambler.mdl`). I'm planning on implementing one using ImGui that wouldn't require platform specific implementations and it would allow me to add model previews within that.
 - Sometimes when switching the render mode, the model's texture will get unloaded. Switching the render mode again a few times will fix it.
 - Models with animated textures (groupskins) are not supported yet
 - You can't change the skin that's being previewed
 - No config of any kind is saved (apart from imgui)
 - There's a slight offset on the UVs that I need to look into
 - The code is an absolute mess that needs to be cleaned up

## Building
### On Windows
Run `premake-2019.bat` to create a Visual Studio 2019 solution!
### On Linux/Mac
Run `premake-linux.sh` to create the Makefiles and then run `make` to build! (You can do `make config=release_x64` to make a release build)

## Helpful resources used in the making of this project

Loading Quake 1 MDL files - http://tfc.duke.free.fr/coding/mdl-specs-en.html

## Credits

 - Quake Mapping Discord (specifically Spoike and [Paril](https://www.planetminecraft.com/member/paril)) - help with the RAPO model format and flags
 - [MissLav](https://www.artstation.com/misslavender) - testing on Linux with Wine
 - [Joshua Barrett](https://github.com/jjbarr) - help with getting the application working on Linux
 - [Melanie Kat](https://melaniekat.com/) - the very cool icon

## Used open source projects and libraries

### raylib

https://github.com/raysan5/raylib/

Used as the rendering backend. The app also uses normal OpenGL code to do stuff that raylib itself doesn't expose.

The code was modified to ~~fix the normal matrix (it was in view space and not world space)~~ ([It's fixed!](https://github.com/raysan5/raylib/commit/c4804c4c0cc3f20545fd2280a3501a463c8f92e7)) and to allow for the use of the stencil buffer.

### ImGui

https://github.com/ocornut/imgui

Used for the main UI

### raylib backend for ImGui

https://github.com/oskaritimperi/imgui-impl-raylib

### PhysicsFS

https://github.com/icculus/physfs

Not used for anything yet, but the goal is to use it to read files from PAKs and other archive formats it supports

### glslang

https://github.com/KhronosGroup/glslang

Used for preprocessing the shader files

### Premake

https://premake.github.io/

'nuff said
