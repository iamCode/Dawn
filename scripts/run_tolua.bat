:: Script for running tolua++, generating the C++ interface for LUA
:: Requires tolua++5.1 on your system. You also need to add it to your
:: Windows %PATH% or change this script to include the absolute path.
::
:: Arguments:
:: --with-testsuite      including the testsuite interface
::
@echo off
setlocal ENABLEDELAYEDEXPANSION

cd ..\src\

:: Check if we should include the testsuite in our LUA package file.
IF ""%1""==""--with-testsuite"" (
    :: Check if the CLuaTestInterface.pkg is already included in our CLuaInterface.pkg.
    :: If it's not, then we add it once. Otherwise we skip this part.
    FOR /F "tokens=3" %%A IN ('find /C "CLuaTestInterface.pkg" "CLuaInterface.pkg"') DO ( SET foundstr=%%A )
    IF "!foundstr!"=="0 " (
        echo $pfile "CLuaTestInterface.pkg" >> CLuaInterface.pkg ) )


:: Generate the C++ LUA interface
tolua++5.1.exe -o CLuaInterfaceGenerated.cpp -H CLuaInterfaceGenerated.H CLuaInterface.pkg
cd ..\scripts