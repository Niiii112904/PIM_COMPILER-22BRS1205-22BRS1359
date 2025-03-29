#ifndef LLVM_PIM_TARGETMACHINE_H
#define LLVM_PIM_TARGETMACHINE_H

#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetTransformImpl.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/TargetParser/Triple.h"

namespace llvm {

class PIMTargetMachine : public TargetMachine {
public:
    PIMTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    std::optional<Reloc::Model> RM, 
                    std::optional<CodeModel::Model> CM,
                    CodeGenOptLevel OL, bool JIT);

    ~PIMTargetMachine() override;

    const TargetSubtargetInfo *getSubtargetImpl(const Function &) const override { 
        return nullptr; 
    }
    
    TargetLoweringObjectFile *getObjFileLowering() const override { 
        return nullptr; 
    }
};

} // namespace llvm

#endif