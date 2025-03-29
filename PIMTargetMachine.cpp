#include "PIMTargetMachine.h"
#include "PIMSubtarget.h"
#include "TargetInfo/PIMTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializePIMTarget() {
  RegisterTargetMachine<PIMTargetMachine> X(getThePIMTarget());
}

PIMTargetMachine::PIMTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   Optional<Reloc::Model> RM,
                                   Optional<CodeModel::Model> CM,
                                   CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T, "e-m:e-p:32:32-i64:64-n32-S128", TT, CPU, FS, Options,
                        RM ? *RM : Reloc::Static,
                        CM ? *CM : CodeModel::Small, OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

namespace {
class PIMPassConfig : public TargetPassConfig {
public:
  PIMPassConfig(PIMTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}
      
  PIMTargetMachine &getPIMTargetMachine() const {
    return getTM<PIMTargetMachine>();
  }
  
  bool addInstSelector() override;
  void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *PIMTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new PIMPassConfig(*this, PM);
}