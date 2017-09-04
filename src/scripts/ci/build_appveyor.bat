
python configure.py --cc=msvc --cpu=%PLATFORM% %CONFIG%

jom -j2

botan-test

nmake install
