#ifndef LLVM_PIM_BACKEND_H
#define LLVM_PIM_BACKEND_H

#include "llvm/CodeGen/SelectionDAGISel.h"
#include "PIMTargetMachine.h"

namespace llvm {

class PIMDAGToDAGISel : public SelectionDAGISel {
public:
    explicit PIMDAGToDAGISel(PIMTargetMachine &TM);

    StringRef getPassName() const override {
        return "PIM DAG->DAG Pattern Instruction Selection";
    }

    bool runOnMachineFunction(MachineFunction &MF) override;

    void Select(SDNode *N) override;
};

} // namespace llvm

#endif