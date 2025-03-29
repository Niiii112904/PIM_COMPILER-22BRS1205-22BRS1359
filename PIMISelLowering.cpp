// src/PIMISelLowering.cpp
#include "llvm/CodeGen/TargetLowering.h"

using namespace llvm;

namespace {
class PIMTargetLowering : public TargetLowering {
public:
    PIMTargetLowering(const TargetMachine &TM) : TargetLowering(TM) {}
};
}
