#ifndef LLVM_PIM_TARGETTRANSFORMINFO_H
#define LLVM_PIM_TARGETTRANSFORMINFO_H

#include "llvm/CodeGen/BasicTTIImpl.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class PIMSubtarget;
class PIMTargetLowering;

class PIMTTIImpl : public BasicTTIImplBase<PIMTTIImpl> {
private:
  const PIMSubtarget *ST;
  const PIMTargetLowering *TLI;
  
public:
  explicit PIMTTIImpl(const PIMTargetMachine *TM, const Function &F)
      : BasicTTIImplBase<PIMTTIImpl>(TM, F.getParent()->getDataLayout()),
        ST(TM->getSubtargetImpl(F)),
        TLI(ST->getTargetLowering()) {}

  // Add target-specific TTI implementations here
  unsigned getRegisterBitWidth(bool Vector) const {
    return Vector ? 128 : 32; // Example for 32-bit registers
  }
};

} // namespace llvm

#endif