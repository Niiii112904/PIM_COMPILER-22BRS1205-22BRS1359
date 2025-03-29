// target/PIM/PIMInstrInfo.cpp
#include "PIMInstrInfo.h"
#include "PIMSubtarget.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"

using namespace llvm;

PIMInstrInfo::PIMInstrInfo(const PIMSubtarget &ST)
    : PIMGenInstrInfo(PIM::ADJCALLSTACKDOWN, PIM::ADJCALLSTACKUP),
      RI() {}

void PIMInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                              MachineBasicBlock::iterator MBBI,
                              const DebugLoc &DL,
                              MCRegister DestReg, MCRegister SrcReg,
                              bool KillSrc) const {
  // Implement register copying
  if (PIM::GPRRegClass.contains(DestReg, SrcReg)) {
    BuildMI(MBB, MBBI, DL, get(PIM::MOVrr), DestReg)
        .addReg(SrcReg, getKillRegState(KillSrc));
  } else {
    llvm_unreachable("Unsupported register copy");
  }
}