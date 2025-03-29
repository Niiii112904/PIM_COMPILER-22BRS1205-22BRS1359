# win_clang_optimized.cmake
set(CMAKE_C_COMPILER "clang-cl.exe")
set(CMAKE_CXX_COMPILER "clang-cl.exe")
set(CMAKE_LINKER "lld-link.exe")

# MSVC runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

# Library paths
set(CMAKE_EXE_LINKER_FLAGS 
    "/libpath:\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.39.33519/lib/x64\" 
     /libpath:\"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/ucrt/x64\" 
     /libpath:\"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64\""
)
