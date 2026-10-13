msbuild .\msvc\nocrash_qmm.vcxproj /p:Configuration=Release /p:Platform=x86
if errorlevel 1 exit /b errorlevel
msbuild .\msvc\nocrash_qmm.vcxproj /p:Configuration=Release /p:Platform=x64
if errorlevel 1 exit /b errorlevel
