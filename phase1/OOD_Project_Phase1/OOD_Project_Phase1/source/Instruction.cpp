
#include "../headers/Instruction.hpp"


InstructionFactory::InstructionFactory(){}

Instruction* InstructionFactory::create_instruction(opcode_t opcode, std::vector<std::string> operands){
    switch (opcode)
    {
        case ADD_OPCODE:
            return new ADD_instruction(operands);
            break;
        case NEG_OPCODE:
            return new NEG_instruction(operands);
            break;
        case MUL_OPCODE:
            return new  MUL_instruction(operands);
            break;
        case JPA_OPCODE:
            return new JPA_instruction(operands);
            break;
        case JPO_OPCODE:
            return new JPo_instruction(operands);
            break;
        case ASI_OPCODE:
            return new ASI_instruction(operands);
            break;
        case LOE_OPCODE:
            return new LOE_instruction(operands);
            break;
        case HLT_OPCODE:
            return new HLT_instruction(operands);
            break;
        default:
            throw(std::invalid_argument("Invalid opcode"));
    }
}

void Instruction::log(){
    std::cout << "Instruction: " << opcode << " ";
    std::cout << std::endl;
}

InstructionFactory::~InstructionFactory(){}
Instruction::Instruction(){}
Instruction::~Instruction(){}

ADD_instruction::ADD_instruction(std::vector<std::string>& p_instruction){
    opcode = ADD_OPCODE;
    if(p_instruction.size() != 4){
        throw(std::invalid_argument("Invalid number of operands"));
    }
    operand1 = std::stoi(p_instruction[1]);
    operand2 = std::stoi(p_instruction[2]);
    result = std::stoi(p_instruction[3]);
}

