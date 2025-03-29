#ifndef LLVM_PIM_INSTRINFO_H
#define LLVM_PIM_INSTRINFO_H

#include "llvm/CodeGen/TargetInstrInfo.h"

namespace llvm {

class PIMSubtarget;

class PIMInstrInfo : public TargetInstrInfo {
public:
  explicit PIMInstrInfo(const PIMSubtarget &ST);
  
  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
                   const DebugLoc &DL, MCRegister DestReg, MCRegister SrcReg,
                   bool KillSrc) const override;
                   
  void storeRegToStackSlot(MachineBasicBlock &MBB,
                          MachineBasicBlock::iterator MI,
                          Register SrcReg, bool isKill, int FrameIndex,
                          const TargetRegisterClass *RC,
                          const TargetRegisterInfo *TRI) const override;
                          
  void loadRegFromStackSlot(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MI,
                           Register DestReg, int FrameIndex,
                           const TargetRegisterClass *RC,
                           const TargetRegisterInfo *TRI) const override;
};

} // namespace llvm

#endif