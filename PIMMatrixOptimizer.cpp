#include "PIMMatrixOptimizer.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

PreservedAnalyses PIMMatrixOptimizerPass::run(Function &F, 
                                           FunctionAnalysisManager &AM) {
    bool Changed = false;
    
    for (auto &BB : F) {
        for (auto &I : BB) {
            if (auto *Call = dyn_cast<CallInst>(&I)) {
                if (Call->getCalledFunction()->getName().contains("matmul")) {
                    IRBuilder<> Builder(&I);
                    auto *MatMul = Builder.CreateIntrinsic(
                        Intrinsic::pim_matmul,
                        {I.getType()},
                        {Call->getArgOperand(0), Call->getArgOperand(1)}
                    );
                    I.replaceAllUsesWith(MatMul);
                    I.eraseFromParent();
                    Changed = true;
                }
            }
        }
    }
    
    return Changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
}