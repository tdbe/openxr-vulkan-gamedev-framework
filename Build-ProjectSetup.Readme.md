(for convenience I also included an executable windows x64 build in the `/out/` folder)

## To set up and build this project:

For XR/gaming  I use Windows (x64) (and CMake):

- Install VS Community, with `Desktop development with C++` (including MSVC, CMake, Windows 11 SDK etc.).
- Download Vulkan SDK: https://vulkan.lunarg.com/sdk/home#windows

If you want to stick with Visual Studio, that's it. You're done. Just open the folder in VS and you can click the green play button 🙂 It will recognize the CMakeLists, no need for a `.sln`.

(You can also use whatever compiler and platform/OS you want, with CMake)

### To use VSCode

For the most "it just works" method of compiling & building C++, just set VSCode to find and use the MSVC compiler / cl.exe from your Visual Studio Community (above):

- Install VSCode and extensions: C/C++ and C/C++ Extension Pack (which includes CMake Tools)
- Then in vscode File->Open Workspace: `./vscode.code-workspace`.
- If Intellisense in VSCode says it can't find the Vulkan SDK: read Note[1].
- Now, when you build, vscode probably won't find cl.exe (the one from Visual Studio). There's 2 things we need to do as described in this answer: https://stackoverflow.com/questions/78961556/how-to-permanently-configure-vscode-to-use-cl-exe-without-launching-it-from-the:
1. Set `C:\Program Files\Microsoft Visual Studio\[year]\Community\VC\Tools\MSVC\[version]\bin\Hostx64\x64\cl.exe` to your system Path
2. And set the other env vars. For me the Envvars.bat looks like this: Note[2].
- Restart the PC for the env vars to take effect.
- When you build in VSCode, it'll ask in the top bar which compiler to use, choose the windows compiler cl/msvc.

Now you can build & run from VSCode and all you have to worry about is update your cmake files when you create a new file etc. 


------------------

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
