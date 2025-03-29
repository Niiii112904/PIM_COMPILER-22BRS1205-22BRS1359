#include "llvm/CodeGen/TargetLowering.h"

using namespace llvm;

class PIMTargetLowering : public TargetLowering {
public:
  PIMTargetLowering(const TargetMachine &TM) : TargetLowering(TM) {
    // Declare support for 4-bit LUT operations
    addRegisterClass(MVT::i4, &PIM::LUTRegClass);
    setOperationAction(ISD::MUL, MVT::i4, Custom);
  }

  SDValue LowerMUL(SDValue Op, SelectionDAG &DAG) const override {
    // Implement 4-bit LUT-based multiplication (Section IV-D of paper)
    SDLoc dl(Op);
    SDValue LHS = Op.getOperand(0);
    SDValue RHS = Op.getOperand(1);
    return DAG.getNode(PIMISD::LUT_MUL, dl, MVT::i8, LHS, RHS);
  }
};