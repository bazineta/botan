
echo Current build setup MSVS="%MSVS%" PLATFORM="%PLATFORM%" CONFIG="%CONFIG%"

if %MSVS% == 2013 call "%ProgramFiles(x86)%\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" %PLATFORM%
if %MSVS% == 2015 call "%ProgramFiles(x86)%\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" %PLATFORM%
if %MSVS% == 2017 call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" %PLATFORM%

cl # check compiler version

appveyor DownloadFile http://download.qt.io/official_releases/jom/jom.zip -FileName jom.zip
7z e jom.zip
