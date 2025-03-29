include "llvm/IR/Intrinsics.td"

let TargetPrefix = "pim" in {
  def int_pim_matmul : Intrinsic<[llvm_i32_ty], 
                               [llvm_ptr_ty, llvm_ptr_ty, llvm_i32_ty],
                               [IntrNoMem]>;
}