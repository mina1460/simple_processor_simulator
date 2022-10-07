
#include "headers/Instruction.hpp"


instruction_factory::instruction_factory(){}

instruction instruction_factory::create_instruction(opcode_t opcode, std::vector<std::string> operands){
    switch (opcode)
    {
        case ADD_OPCODE:
            return ADD_instruction(operands);
            break;
        case NEG_OPCODE:
            return NEG_instruction(operands);
            break;
        case MUL_OPCODE:
            return MUL_instruction(operands);
            break;
        case JPA_OPCODE:
            return JPA_instruction(operands);
            break;
        case JPO_OPCODE:
            return JPo_instruction(operands);
            break;
        case ASI_OPCODE:
            return ASI_instruction(operands);
            break;
        case LOE_OPCODE:
            return LOE_instruction(operands);
            break;
        case HLT_OPCODE:
            return HLT_instruction(operands);
            break;
        default:
            throw(std::invalid_argument("Invalid opcode"));
    }
}

void instruction::log(){
    std::cout << "Instruction: " << opcode << " ";
    for (auto& operand : operands){
        std::cout << operand << " ";
    }
    std::cout << std::endl;
}

instruction_factory::~instruction_factory(){}



instruction::instruction(){
    
}



instruction::~instruction(){

}
