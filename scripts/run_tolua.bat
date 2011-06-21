rem Script for running tolua++, generating the C++ interface for LUA
rem Requires tolua++5.1 on your system. You also need to add it to your
rem Windows PATH or change this script to include the absolute path.
rem
rem Arguments:
rem --with-testsuite      including the testsuite interface
rem
@echo off
setlocal ENABLEDELAYEDEXPANSION

cd ..\src\

rem Check if we should include the testsuite in our LUA package file.
IF ""%1""==""--with-testsuite"" (
    rem Check if the CLuaTestInterface.pkg is already included in our CLuaInterface.pkg.
    rem If it's not, then we add it once. Otherwise we skip this part.
    FOR /F "tokens=3" %%A IN ('find /C "CLuaTestInterface.pkg" "CLuaInterface.pkg"') DO ( SET foundstr=%%A )
    IF "!foundstr!"=="0 " (
        echo $pfile "CLuaTestInterface.pkg" >> CLuaInterface.pkg ) )


rem Generate the C++ LUA interface
tolua++5.1.exe -o CLuaInterfaceGenerated.cpp -H CLuaInterfaceGenerated.H CLuaInterface.pkg
cd ..\scripts