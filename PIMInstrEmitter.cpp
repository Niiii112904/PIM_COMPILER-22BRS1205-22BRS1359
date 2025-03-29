#include "PIMInstrEmitter.h"

uint32_t PIMInstrEmitter::packInstruction(uint8_t opType, uint8_t pointer, 
                                        uint16_t memAddr, bool read, bool write) {
    uint32_t instr = 0;
    instr |= (opType & 0x3) << 22;
    instr |= (pointer & 0x3F) << 16;
    instr |= (read ? 1 : 0) << 9;
    instr |= (write ? 1 : 0) << 8;
    instr |= (memAddr & 0x1FF);
    return instr;
}

void PIMInstrEmitter::emitPROG(unsigned corePtr, unsigned funcWordAddr) {
    instructions.push_back(packInstruction(PROG, corePtr, funcWordAddr, false, false));
}

void PIMInstrEmitter::emitEXE(unsigned opPtr, unsigned memAddr, bool read, bool write) {
    instructions.push_back(packInstruction(EXE, opPtr, memAddr, read, write));
}

void PIMInstrEmitter::emitEND() {
    instructions.push_back(packInstruction(END, 0, 0, false, false));
}