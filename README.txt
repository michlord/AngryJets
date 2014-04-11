To compile this project you need a C++11 compliant compiler and Code::Blocks IDE (unless you modify the project to use other build system).
MinGW 4.8.1 should do fine. Code::Blocks 12.11 was used since it has improved C++11 support.
If you are going to use included libraries (in the lib.7z archive) then make sure your compiler is MinGW sjlj or it won't work.

The following dlls are needed to run executable:
jsoncpp.dll
libgcc_s_sjlj-1.dll
libsndfile-1.dll
libstdc++-6.dll
openal32.dll
sfml-audio-2.dll
sfml-graphics-2.dll
sfml-system-2.dll
sfml-window-2.dll

Sigslot library needs WIN32 define which you could set in Code::Blocks > Settings > Compiler > #defines.
If you choose not to use Code::Blocks then you supply g++ with -DWIN32 parameter.