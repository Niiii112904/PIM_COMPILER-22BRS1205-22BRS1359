include "llvm/Target/TargetCallingConv.td"

def CC_PIM : CallingConv<[
  CCIfType<[i32], CCAssignToReg<[R0, R1, R2, R3]>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;