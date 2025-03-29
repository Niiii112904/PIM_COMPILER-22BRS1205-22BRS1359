cmake_minimum_required(VERSION 3.15)
project(PIMCompiler)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# LLVM Configuration
set(LLVM_DIR "C:/LLVM/clang+llvm-20.1.1-x86_64-pc-windows-msvc/lib/cmake/llvm")
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

# Include TableGen modules
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(TableGen)
include(AddLLVM)

# Add tablegen commands
set(LLVM_TARGET_DEFINITIONS ${CMAKE_CURRENT_SOURCE_DIR}/target/PIM/PIM.td)

tablegen(LLVM ${LLVM_TARGET_DEFINITIONS} 
  -gen-register-info -o PIMGenRegisterInfo.inc)
tablegen(LLVM ${LLVM_TARGET_DEFINITIONS} 
  -gen-instr-info -o PIMGenInstrInfo.inc)
tablegen(LLVM ${LLVM_TARGET_DEFINITIONS} 
  -gen-subtarget -o PIMGenSubtargetInfo.inc)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}  # For generated .inc files
)

# Essential LLVM components
llvm_map_components_to_libnames(LLVM_LIBS
    Core
    Support
    Target
    CodeGen
    TableGen
    AsmPrinter
    MC
)

# Target sources
set(PIM_TARGET_SOURCES
  target/PIM/PIMTargetInfo.cpp
  target/PIM/PIMSubtarget.cpp
  target/PIM/PIMInstrInfo.cpp
  target/PIM/PIMRegisterInfo.cpp
  target/PIM/PIMFrameLowering.cpp
  target/PIM/PIMISelLowering.cpp
  target/PIM/PIMSelectionDAGInfo.cpp
  target/PIM/PIMAsmPrinter.cpp
)

# Main sources
set(PIM_SOURCES
    lib/PIMBackend.cpp
    lib/PIMTargetMachine.cpp
    lib/PIMInstrEmitter.cpp
    lib/PIMMatrixOptimizer.cpp
    lib/PIMMemoryMapper.cpp
    ${PIM_TARGET_SOURCES}
)

# Static library
add_library(PIMBackend STATIC ${PIM_SOURCES})
target_link_libraries(PIMBackend PRIVATE ${LLVM_LIBS})

# Executable
add_executable(pimcc tools/pimcc.cpp)
target_link_libraries(pimcc PRIVATE PIMBackend ${LLVM_LIBS})

# Windows/Clang settings
if(WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set_target_properties(pimcc PROPERTIES 
        INTERPROCEDURAL_OPTIMIZATION FALSE
    )
    target_compile_options(pimcc PRIVATE -g)
endif()