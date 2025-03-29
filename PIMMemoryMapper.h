#ifndef PIM_MEMORY_MAPPER_H
#define PIM_MEMORY_MAPPER_H

#include "llvm/IR/Value.h"
#include <map>

class PIMMemoryMapper {
    std::map<const llvm::Value*, unsigned> memMap;
    unsigned nextAddr;
    
public:
    PIMMemoryMapper() : nextAddr(0) {}
    
    unsigned allocate(const llvm::Value* val, unsigned size);
    unsigned getAddress(const llvm::Value* val) const;
    void optimizeMatrixPlacement(llvm::Function &F);
};

#endif