#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "includes.hpp"

class Instruction;

/*
    The InstructionFactory class is a factory class that creates instance of 
    Instruction objects in a polymorphic way.
*/
class InstructionFactory{
    public:
        InstructionFactory();
        Instruction* create_instruction(opcode_t opcode, std::vector<std::string> operands);
        ~InstructionFactory();        
};

/*
    The Instruction class is an abstract class that defines the interface for 
    all the instruction classes.
*/
class Instruction {
    public:
        Instruction();
        Instruction(std::string line);
        opcode_t get_opcode();
        int get_opcode(std::vector<std::string>& p_instruction);
        void set_core_id(int core_id);
        void set_data_memory(std::array<int32_t, DATA_MEMORY_SIZE>* p_data_memory);
        void set_instruction_counter(int* p_instruction_counter);
        void set_fetched_instructions_count(int* p_fetched_instructions_count);
        virtual void execute() = 0;
        virtual void log();
        ~Instruction();
    private:
        const std::unordered_map<std::string, opcode_t>& Opcodes();
    protected:
        opcode_t opcode;
        int core_id;
        std::array<int32_t, DATA_MEMORY_SIZE>* data_memory;
        int* instruction_counter;
        int* fetched_instructions_count;
};

/*
    The following classes inherit from Instruction. They define and implement their
    own data members and methods depending on the instruction type.
*/
class ADD_instruction : public Instruction {
    public:
        ADD_instruction(std::vector<std::string>& p_instruction);
        void execute();
        ~ADD_instruction(){}
    private:
        int32_t operand1;
        int32_t operand2;
        int32_t result;
};

class NEG_instruction : public Instruction {
    public:
        NEG_instruction(std::vector<std::string>& p_instruction);
        void execute();
        ~NEG_instruction(){}
    private:
        int32_t operand1;
        int32_t result;
};

class MUL_instruction : public Instruction {
    public:
        MUL_instruction(std::vector<std::string>& p_instruction);
        void execute();
        ~MUL_instruction(){}
    private:
        int32_t operand1;
        int32_t operand2;
        int32_t result;
};

class JPA_instruction : public Instruction {
    public:
        JPA_instruction(std::vector<std::string>& p_instruction);
        void execute();
        ~JPA_instruction(){}
    private:
        int32_t operand1;
};

class JP0_instruction : public Instruction {
    public:
        JP0_instruction(std::vector<std::string>& p_instruction);
        void execute();
        ~JP0_instruction(){}
    private:
        int32_t operand1;
        int32_t operand2;
};

class ASI_instruction : public Instruction {
    public:
        ASI_instruction(std::vector<std::string>& p_instruction);
        void execute();
        ~ASI_instruction(){}
    private:
        int32_t operand1;
        int32_t operand2;
};

class LOE_instruction : public Instruction {
    public:
        LOE_instruction(std::vector<std::string>& p_instruction);
        void execute();
        ~LOE_instruction(){}
    private:
        int32_t operand1;
        int32_t operand2;
        int32_t result;
};

class HLT_instruction : public Instruction {
    public:
        HLT_instruction(std::vector<std::string>& p_instruction);
        void execute();
        ~HLT_instruction(){}
    private:
};


#endif /* INSTRUCTION_HPP */
