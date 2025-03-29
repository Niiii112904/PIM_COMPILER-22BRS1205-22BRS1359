# win_clang.cmake
set(CMAKE_C_COMPILER "clang-cl.exe")
set(CMAKE_CXX_COMPILER "clang-cl.exe")
set(CMAKE_LINKER "lld-link.exe")

# Use MSVC runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

# Windows SDK paths (update these if needed)
set(WINDOWS_SDK_DIR "C:/Program Files (x86)/Windows Kits/10")
set(WINDOWS_SDK_VERSION "10.0.22621.0")
set(MSVC_TOOLS_DIR "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.39.33519")

# Include directories
include_directories(
  "\/include"
  "\/Include/\/ucrt"
  "\/Include/\/shared"
)

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS 
    "/libpath:\/lib/x64 
     /libpath:\/Lib/\/ucrt/x64 
     /libpath:\/Lib/\/um/x64"
)
