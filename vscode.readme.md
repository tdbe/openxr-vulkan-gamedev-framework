For everyone's sanity and ease of reproduceability (and using Windows + VSCode), I chose the most "click to install and it just works" method of compiling & building C++: 

- We just use the MSVC compiler / cl.exe from your Visual Studio Community, by setting VSCode to use it. So install VS Community, with C++ tools / sdk etc if you didn't already.
- Then install VSCode and extensions: C/C++ and C/C++ Extension Pack (which includes CMake Tools)
- Then in vscode File->Open Workspace: ./vscode.code-workspace.
- If Intellisense in VSCode says it can't find the Vulkan SDK: read Note[1].
- Now, when you build, vscode probably won't find cl.exe (the one from Visual Studio). There's 2 things we need to do as described in this answer: https://stackoverflow.com/questions/78961556/how-to-permanently-configure-vscode-to-use-cl-exe-without-launching-it-from-the
- Set C:\Program Files\Microsoft Visual Studio\[year]\Community\VC\Tools\MSVC\[version]\bin\Hostx64\x64\cl.exe to your system Path
- And set the other env vars. For me the Envvars.bat looks like this: Note[2].
- Restart for the env vars to take effect.

Now you can build & run from VSCode and all you have to worry about is cmake files. 


------------------

<Note[1]>: To find vulkan sdk, add these two lines in your c_cpp_properties settings (I already added this as an actual external json file, which vscode will read from the included .vscode folder, so it should just work.)

{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${default}",
                "${workspaceFolder}/**",   <======
                "${VULKAN_SDK}/Include/**" <======
            ],
</Note[1]>

<Note[2]>

setx INCLUDE "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\include;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\ATLMFC\include;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\VS\include;C:\Program Files (x86)\Windows Kits\10\include\10.0.22621.0\ucrt;C:\Program Files (x86)\Windows Kits\10\\include\10.0.22621.0\\um;C:\Program Files (x86)\Windows Kits\10\\include\10.0.22621.0\\shared;C:\Program Files (x86)\Windows Kits\10\\include\10.0.22621.0\\winrt;C:\Program Files (x86)\Windows Kits\10\\include\10.0.22621.0\\cppwinrt" /M
setx LIB "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\ATLMFC\lib\x64;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\lib\x64;C:\Program Files (x86)\Windows Kits\10\lib\10.0.22621.0\ucrt\x64;C:\Program Files (x86)\Windows Kits\10\\lib\10.0.22621.0\\um\x64" /M
setx LIBPATH "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\ATLMFC\lib\x64;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\lib\x64;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\lib\x86\store\references;C:\Program Files (x86)\Windows Kits\10\UnionMetadata\10.0.22621.0;C:\Program Files (x86)\Windows Kits\10\References\10.0.22621.0;C:\Windows\Microsoft.NET\Framework64\v4.0.30319" /M

</Note[2]>
