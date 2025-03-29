// target/PIM/PIMRegisterInfo.td

// Include base definitions
include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Register Definitions
//===----------------------------------------------------------------------===//

class PIMReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "PIM";
}

// General Purpose Registers
def R0  : PIMReg<0x00, "r0">;
def R1  : PIMReg<0x01, "r1">;
def R2  : PIMReg<0x02, "r2">;
def R3  : PIMReg<0x03, "r3">;
def R4  : PIMReg<0x04, "r4">;
def R5  : PIMReg<0x05, "r5">;
def R6  : PIMReg<0x06, "r6">;
def R7  : PIMReg<0x07, "r7">;

// Special Registers
def SP  : PIMReg<0x08, "sp">;  // Stack Pointer
def LR  : PIMReg<0x09, "lr">;  // Link Register
def PC  : PIMReg<0x0A, "pc">;  // Program Counter
def SR  : PIMReg<0x0B, "sr">;  // Status Register

// PIM-Specific Registers
def PIM_CR  : PIMReg<0x0C, "cr">;   // Control Register
def PIM_DR  : PIMReg<0x0D, "dr">;   // Data Register
def PIM_AR  : PIMReg<0x0E, "ar">;   // Address Register
def PIM_CTR : PIMReg<0x0F, "ctr">;  // Counter Register
def MOVrr : InstPIM<(outs GPR:$dst), (ins GPR:$src), "mov $dst, $src", []>;
//===----------------------------------------------------------------------===//
// Register Classes
//===----------------------------------------------------------------------===//

// General Purpose Register Class
def GPR : RegisterClass<"PIM", [i32], 32, 
                       (add R0, R1, R2, R3, R4, R5, R6, R7)>;

// General Purpose + Special Registers
def GPRwithSP : RegisterClass<"PIM", [i32], 32,
                            (add R0, R1, R2, R3, R4, R5, R6, R7, SP)>;

// Pointer Register Class (for addresses)
def PTR : RegisterClass<"PIM", [i32], 32,
                      (add R0, R1, R2, R3, SP)>;

// Status Register Class
def SRReg : RegisterClass<"PIM", [i32], 32, (add SR)>;

// PIM-Special Register Class
def PIM_CRegs : RegisterClass<"PIM", [i32], 32,
                            (add PIM_CR, PIM_DR, PIM_AR, PIM_CTR)>;

//===----------------------------------------------------------------------===//
// Register Aliases
//===----------------------------------------------------------------------===//

def FP : RegisterAlias<SP>;  // Frame Pointer alias to SP
def IP : RegisterAlias<R7>;  // Intra-procedure call scratch register

//===----------------------------------------------------------------------===//
// Register Subsets
//===----------------------------------------------------------------------===//

// Argument registers
def ArgGPRs : RegisterSubRegSet<[R0, R1, R2, R3]>;

// Callee-saved registers
def CalleeSavedGPRs : RegisterSubRegSet<[R4, R5, R6, R7]>;
def CC_PIM : CallingConv<[
  CCIfType<[i32], CCAssignToReg<[R0, R1, R2, R3]>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;
//===----------------------------------------------------------------------===//
// Dwarf Register Numbers
//===----------------------------------------------------------------------===//

let DwarfNumbers = [
  DWARFRegNum<0x00, R0>,
  DWARFRegNum<0x01, R1>,
  // ... all other registers ...
  DWARFRegNum<0x0F, PIM_CTR>
] in {
  def PIM_DwarfRegs : DwarfRegNum<[]>;
}
def HasPIMExt : SubtargetFeature<"pimext", "PIMExtEnabled", "true",
                                "Enable PIM-specific extensions">;
//===----------------------------------------------------------------------===//
// Register Properties
//===----------------------------------------------------------------------===//

def PIMRegs : Registers<
  (sequence "R%u", 0, 7),  // R0-R7
  SP, LR, PC, SR,          // Special registers
  PIM_CR, PIM_DR, PIM_AR, PIM_CTR  // PIM-specific
>;