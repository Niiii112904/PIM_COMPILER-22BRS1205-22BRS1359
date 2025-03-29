#ifndef LLVM_PIM_SUBTARGET_H
#define LLVM_PIM_SUBTARGET_H

#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "PIMFrameLowering.h"
#include "PIMISelLowering.h"
#include "PIMInstrInfo.h"
#include "PIMSelectionDAGInfo.h"

namespace llvm {

class PIMSubtarget : public TargetSubtargetInfo {
  PIMFrameLowering FrameLowering;
  PIMInstrInfo InstrInfo;
  PIMTargetLowering TLInfo;
  PIMSelectionDAGInfo TSInfo;

public:
  PIMSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
               const PIMTargetMachine &TM);
  
  const PIMInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const PIMFrameLowering *getFrameLowering() const override { return &FrameLowering; }
  const PIMTargetLowering *getTargetLowering() const override { return &TLInfo; }
  const PIMSelectionDAGInfo *getSelectionDAGInfo() const override { return &TSInfo; }
  
  //