#include "PIMBackend.h"
#include "PIMInstrEmitter.h"
#include "PIMMemoryMapper.h"

using namespace llvm;

PIMTargetLowering::PIMTargetLowering(const TargetMachine &TM)
    : TargetLowering(TM) {
    // Set up lowering rules
}

PIMDAGToDAGISel::PIMDAGToDAGISel(PIMTargetMachine &TM, 
                                 CodeGenOpt::Level OptLevel)
    : SelectionDAGISel(TM, OptLevel), 
      Subtarget(TM.getSubtarget<PIMSubtarget>()) {}

void PIMDAGToDAGISel::Select(SDNode *N) {
    switch (N->getOpcode()) {
    case ISD::ADD:
        // Convert to PIM ADD
        break;
    case ISD::MUL:
        // Convert to PIM MAC
        break;
    case ISD::LOAD:
        // Generate memory read
        break;
    case ISD::STORE:
        // Generate memory write
        break;
    case ISD::INTRINSIC_W_CHAIN:
        if (auto *IntNode = dyn_cast<IntrinsicSDNode>(N)) {
            switch (IntNode->getIntrinsicID()) {
            case Intrinsic::pim_matmul:
                // Lower to MAC sequence
                break;
            }
        }
        break;
    default:
        SelectCode(N);
    }
}