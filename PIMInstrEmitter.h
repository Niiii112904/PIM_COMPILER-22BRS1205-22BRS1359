#ifndef PIM_INSTR_EMITTER_H
#define PIM_INSTR_EMITTER_H

#include <vector>
#include <cstdint>

class PIMInstrEmitter {
    std::vector<uint32_t> instructions;
    
    enum OpType { PROG = 0, EXE = 1, END = 2 };
    
    uint32_t packInstruction(uint8_t opType, uint8_t pointer, 
                           uint16_t memAddr, bool read, bool write);
    
public:
    void emitPROG(unsigned corePtr, unsigned funcWordAddr);
    void emitEXE(unsigned opPtr, unsigned memAddr, bool read, bool write);
    void emitEND();
    
    const std::vector<uint32_t>& getInstructions() const { return instructions; }
    void clear() { instructions.clear(); }
};

#endif