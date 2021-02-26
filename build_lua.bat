@echo OFF

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Preview\VC\Auxiliary\Build\vcvars64.bat"

cd %~dp0\Extern\LuaJIT\src

:: get the dll AND libs
call msvcbuild.bat
call msvcbuild.bat "static"

set "destdir=%~dp0\libs"

if not exist %destdir% mkdir %destdir%

copy lua51.lib %destdir%
copy luajit.lib %destdir%

Exit