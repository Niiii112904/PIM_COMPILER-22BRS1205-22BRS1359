// target/PIM/PIMRegisterInfo.cpp
#include "PIMRegisterInfo.h"
#include "PIMSubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"

using namespace llvm;

PIMRegisterInfo::PIMRegisterInfo() : PIMGenRegisterInfo(PIM::LR) {}

const MCPhysReg*
PIMRegisterInfo::getCalleeSavedRegs(const MachineFunction *) const {
  static const MCPhysReg CalleeSavedRegs[] = { PIM::R4, PIM::R5, 0 };
  return CalleeSavedRegs;
}

BitVector PIMRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  Reserved.set(PIM::SP); // Stack pointer
  Reserved.set(PIM::LR); // Link register
  return Reserved;
}