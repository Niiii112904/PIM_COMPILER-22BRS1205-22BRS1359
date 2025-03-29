// target/PIM/PIMSubtarget.cpp
#include "PIMSubtarget.h"
#include "PIM.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "pim-subtarget"

PIMSubtarget::PIMSubtarget(const Triple &TT, StringRef CPU, 
                          StringRef FS, const PIMTargetMachine &TM)
    : PIMGenSubtargetInfo(TT, CPU, /*TuneCPU*/ CPU, FS),
      FrameLowering(*this),
      InstrInfo(*this),
      TLInfo(TM, *this),
      TSInfo() {}

bool PIMSubtarget::enableMachineScheduler() const {
  return true; // Enable MI scheduling
}