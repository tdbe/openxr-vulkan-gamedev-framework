(for convenience I also included an executable windows x64 build in the `/out/` folder)

## To set up and build this project:

For XR/gaming use Windows (x64) (and CMake/Clang or MSVC). To keep it cross-platform and simple we have CMakeLists, not `sln`'s.

### To use Visual Studio

- Install Visual Studio Community, with `Desktop development with C++` (including MSVC and/or CMake or Clang, Windows 11 SDK etc.).
- Download Vulkan SDK: https://vulkan.lunarg.com/sdk/home#windows

If you want to stick with Visual Studio, that's it. You're done. Just open the folder in VS and you can click the green play button 🙂 It will recognize the CMakeLists, no need for a `.sln`.

(You can also use whatever compiler and platform/OS you want, with CMake)

### To use VSCode

- Download Vulkan SDK: https://vulkan.lunarg.com/sdk/home#windows

For the most gamedev-friendly, least worries, "it just works", method of compiling & building C++, just set VSCode to find and use an existing compiler - and the one you probably already have is the MSVC compiler / cl.exe from your Visual Studio (Community):

- Install VSCode and extensions: C/C++ and C/C++ Extension Pack (which includes CMake Tools)
- Then in vscode File->Open Workspace: `./vscode.code-workspace`.
- If Intellisense in VSCode says it can't find the Vulkan SDK: read Note[1].
- Now, when you build, vscode probably won't find cl.exe / MS-cl / Clang-cl. There's 2 things we need to do as described in this answer (paths pointing to MSVC specifically): https://stackoverflow.com/questions/78961556/how-to-permanently-configure-vscode-to-use-cl-exe-without-launching-it-from-the:
1. Set `C:\Program Files\Microsoft Visual Studio\[year]\Community\VC\Tools\MSVC\[version]\bin\Hostx64\x64\cl.exe` to your system Path
2. And set the other env vars. For me the Envvars.bat looks like this: Note[2].
- Restart the PC for the env vars to take effect.
- When you build in VSCode, it'll ask in the top bar which compiler to use, choose the windows compiler cl/msvc. (if you accidentally loose that prompt, find the "wrench and screwdriver" icon on the VSCode bottom bar "click to change the active kit", or Ctrl+Shift+P and type "Cmake: Select (a kit)"). 
- NOTE: if you have long paths to your compiler, or use MSVC or any compiler from the Visual Studio path, you will get a misleading AF compilation error. To fix it I set custom compiler output paths: (I changed the .vscode/settings.json for this project to use c make presets: "Cmake: Use C Make Presets" `always`.) So go to Ctrl + Shift + P and type "Cmake: Select Configure Preset" (also found in the CMake extension tab (button on the left side VSCode column) Project Status > Folder > Configure) and you should find my `MSVC x64 (Debug/Release)` preset, the one defined in the root of the project in `CMakePresets.json` (if you loose that file (easily gets overwritten), there's a backup in the `/.vscode/cmake-presets.json`). After this, VSCode should automatically also set the Project Status > Folder > Build targets to `msvc-x64-Debug` or `msvc-x64-Release`.

Now you can build & run from VSCode, and all you have to worry about any more is update your cmake files to manually add any new cpp/h/hpp files you create etc.

(These processes should be less clownshoes opaque, self-errorponed, and laborious, after like 50 years, don't you agree my fellow hoo-man who wants to just also have time for a semblance of a life? Eh..)

------------------

Note: If you're using MSVC, make sure you avoid the Microsoft subset of C++; only use actual Standard C++ (e.g. the `__event` keyword is specific to "Microsoft C++", is not part of Standard C++).

<Note[1]>: To find vulkan sdk, add these two lines in your c_cpp_properties settings (I already added this as an actual external json file, which vscode will read from the included .vscode folder, so it should just work.)
```
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${default}",
                "${workspaceFolder}/**",   <======
                "${VULKAN_SDK}/Include/**" <======
            ],
```
</Note[1]>

<Note[2]>
```
setx INCLUDE "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\include;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\ATLMFC\include;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\VS\include;C:\Program Files (x86)\Windows Kits\10\include\10.0.22621.0\ucrt;C:\Program Files (x86)\Windows Kits\10\\include\10.0.22621.0\\um;C:\Program Files (x86)\Windows Kits\10\\include\10.0.22621.0\\shared;C:\Program Files (x86)\Windows Kits\10\\include\10.0.22621.0\\winrt;C:\Program Files (x86)\Windows Kits\10\\include\10.0.22621.0\\cppwinrt" /M
setx LIB "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\ATLMFC\lib\x64;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\lib\x64;C:\Program Files (x86)\Windows Kits\10\lib\10.0.22621.0\ucrt\x64;C:\Program Files (x86)\Windows Kits\10\\lib\10.0.22621.0\\um\x64" /M
setx LIBPATH "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\ATLMFC\lib\x64;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\lib\x64;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\lib\x86\store\references;C:\Program Files (x86)\Windows Kits\10\UnionMetadata\10.0.22621.0;C:\Program Files (x86)\Windows Kits\10\References\10.0.22621.0;C:\Windows\Microsoft.NET\Framework64\v4.0.30319" /M
```
</Note[2]>
