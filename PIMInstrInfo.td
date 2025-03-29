include "PIMRegisterInfo.td"

class InstPIM<dag outs, dag ins, string asmstr, list<dag> pattern>
  : Instruction {
  let Namespace = "PIM";
  let OutOperandList = outs;
  let InOperandList = ins;
  let AsmString = asmstr;
  let Pattern = pattern;
}

def MOVrr : InstPIM<(outs GPR:$dst), (ins GPR:$src), "mov $dst, $src", []>;
// Add more instructions...