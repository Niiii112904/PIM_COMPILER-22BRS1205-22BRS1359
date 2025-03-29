#ifndef PIM_MATRIX_OPTIMIZER_H
#define PIM_MATRIX_OPTIMIZER_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class PIMMatrixOptimizerPass : public PassInfoMixin<PIMMatrixOptimizerPass> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif