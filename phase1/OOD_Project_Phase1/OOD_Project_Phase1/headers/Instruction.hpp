#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "includes.hpp"

class instruction;

class instruction_factory{
    public:
        instruction_factory();
        instruction* create_instruction(opcode_t opcode, std::vector<std::string> operands);
        ~instruction_factory();        
};

class instruction {
    public:
        instruction();
        instruction(std::string line);
        int get_opcode(std::vector<std::string>& p_instruction);
        virtual void execute() = 0;
        virtual void log();
        ~instruction();
    private:
        const std::unordered_map<std::string, opcode_t>& Opcodes();
    protected:
        opcode_t opcode;
};


class ADD_instruction : public instruction {
    public:
        ADD_instruction(std::vector<std::string>& p_instruction);
        void execute(){
            std::cout << "Executing ADD instruction" << std::endl;
            result = operand1 + operand2;
            std::cout << "Adding " << operand1 << " and " << operand2 << std::endl;
            std::cout << "Result is " << result << std::endl;
        }
        ~ADD_instruction(){}
    private:
        int32_t operand1;
        int32_t operand2;
        int32_t result;
};

class NEG_instruction : public instruction {
    public:
        NEG_instruction(std::vector<std::string>& p_instruction){
            opcode = NEG_OPCODE;
        };
        void execute(){
            std::cout << "Executing NEG instruction" << std::endl;
        }
        ~NEG_instruction(){}
    private:
        int32_t operand1;
        int32_t result;
};

class MUL_instruction : public instruction {
    public:
        MUL_instruction(std::vector<std::string>& p_instruction){}
        void execute(){
            std::cout << "Executing MUL instruction" << std::endl;
        }
        ~MUL_instruction(){}
    private:
        int32_t operand1;
        int32_t operand2;
        int32_t result;
};

class JPA_instruction : public instruction {
    public:
        JPA_instruction(std::vector<std::string>& p_instruction){}
        void execute(){
            std::cout << "Executing JPA instruction" << std::endl;
        }
        ~JPA_instruction(){}
    private:
        int32_t operand1;
};

class JPo_instruction : public instruction {
    public:
        JPo_instruction(std::vector<std::string>& p_instruction){}
        void execute(){
            std::cout << "Executing JPO instruction" << std::endl;
        }
        ~JPo_instruction(){}
    private:
        int32_t operand1;
};

class ASI_instruction : public instruction {
    public:
        ASI_instruction(std::vector<std::string>& p_instruction){}
        void execute(){
            std::cout << "Executing ASI instruction" << std::endl;
        }
        ~ASI_instruction(){}
    private:
        int32_t operand1;
        int32_t operand2;
};

class LOE_instruction : public instruction {
    public:
        LOE_instruction(std::vector<std::string>& p_instruction){}
        void execute(){
            std::cout << "Executing LOE instruction" << std::endl;
        }
        ~LOE_instruction(){}
    private:
        int32_t operand1;
        int32_t operand2;
        int32_t result;
};

class HLT_instruction : public instruction {
    public:
        HLT_instruction(std::vector<std::string>& p_instruction){}
        void execute(){
            std::cout << "Executing HLT instruction" << std::endl;
        }
        ~HLT_instruction(){}
    private:
};


#endif /* INSTRUCTION_HPP */
