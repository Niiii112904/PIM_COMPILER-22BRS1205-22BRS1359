// target/PIM/PIMAsmPrinter.cpp
#include "PIMAsmPrinter.h"
#include "PIMMCInstLower.h"

using namespace llvm;

bool PIMAsmPrinter::runOnMachineFunction(MachineFunction &MF) {
  PIMMCInstLower MCInstLowering(MF.getContext(), *this);
  return AsmPrinter::runOnMachineFunction(MF);
}

void PIMAsmPrinter::emitInstruction(const MachineInstr *MI) {
  // Convert to MCInst and emit
  PIMMCInstLower Lower(MF->getContext(), *this);
  MCInst TmpInst;
  Lower.lower(MI, TmpInst);
  EmitToStreamer(*OutStreamer, TmpInst);
}