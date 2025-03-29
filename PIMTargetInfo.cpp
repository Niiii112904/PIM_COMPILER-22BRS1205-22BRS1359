// target/PIM/PIMTargetInfo.cpp
#include "PIM.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

Target &getThePIMTarget() {
  static Target ThePIMTarget;
  return ThePIMTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializePIMTargetInfo() {
  RegisterTarget<Triple::pim> X(getThePIMTarget(), "pim", "PIM Processor", "PIM");
}