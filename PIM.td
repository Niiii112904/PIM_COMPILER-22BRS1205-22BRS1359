// Include base definitions
include "llvm/Target/Target.td"
include "PIMRegisterInfo.td"
include "PIMInstrInfo.td"
include "PIMCallingConv.td"

// Define the target
def PIM : Target {
  let InstructionSet = PIMInstrInfo;
  let AssemblyParsers  = [];
  let AssemblyPrinters = [];
  let CallConv = [CC_PIM];
}