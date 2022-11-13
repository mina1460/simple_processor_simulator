
#include "../headers/Instruction.hpp"


InstructionFactory::InstructionFactory(){}
// using the factory pattern to create the instruction objects
Instruction* InstructionFactory::create_instruction(opcode_t opcode, std::vector<std::string> operands){
    // create the instruction object based on the opcode
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
        case JP0_OPCODE:
            return new JP0_instruction(operands);
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
            // throw an exception if the opcode is not valid
            throw(std::invalid_argument("Invalid opcode"));
    }
}

void Instruction::log(){
    // log the instruction 
    std::cout << log_msg.str();
}
void Instruction::set_data_memory(std::array<std::atomic<int32_t>, DATA_MEMORY_SIZE>* p_data_memory){
    // set the data memory pointer inside the instruction object to know how to operate on the data memory
    data_memory = p_data_memory;
}
void Instruction::set_instruction_counter(int* p_instruction_counter){
    // set the instruction counter pointer inside the instruction object 
    instruction_counter = p_instruction_counter;
}
void Instruction::set_fetched_instructions_count(int* p_fetched_instructions_count){
    fetched_instructions_count = p_fetched_instructions_count;
}
void Instruction::set_log_msg(std::stringstream& p_log_msg){

    log_msg.str(p_log_msg.str());
    // log_msg << p_log_msg.rdbuf();
}

opcode_t Instruction::get_opcode(){
    return opcode;
}

void Instruction::set_core_id(int _core_id){
    this->core_id = _core_id;
}

InstructionFactory::~InstructionFactory(){}
Instruction::Instruction(){}
Instruction::~Instruction(){}

ADD_instruction::ADD_instruction(std::vector<std::string>& p_instruction){
    // define the opcode and validates the number of operands
    opcode = ADD_OPCODE;
    if(p_instruction.size() != 4){
        throw(std::invalid_argument("Invalid number of operands for ADD instruction"));
    }
    // get the operands
    operand1 = std::stoi(p_instruction[1]);
    operand2 = std::stoi(p_instruction[2]);
    // compute the result
    result = std::stoi(p_instruction[3]);
}
void ADD_instruction::execute(){
    // execute the add instruction and update the data memory
    int32_t num1 = (*data_memory)[operand1];
    int32_t num2 = (*data_memory)[operand2];
    
    (*data_memory)[result] = num1 + num2;

    // report the instruction execution log
    std::stringstream log_msg;
    log_msg << "[Thread "<<core_id <<"][" << (*instruction_counter) << "] The SIM just added memory location " << operand1 << " with value " << num1 
            << " and memory location " << operand2 << " with value " << num2 
            << " and stored it in memory location " << result << " now with value " << (*data_memory)[result] 
            << std::endl;
    set_log_msg(log_msg);
    log();
    // std::cout << log_msg.str();
}

NEG_instruction::NEG_instruction(std::vector<std::string>& p_instruction){
    // define the opcode and validates the number of operands
    opcode = NEG_OPCODE;
    // validate the number of operands
    if(p_instruction.size() != 3){
        throw(std::invalid_argument("Invalid number of operands for NEG instruction"));
    }
    // get the operands 
    operand1 = std::stoi(p_instruction[1]);
    result = std::stoi(p_instruction[2]);
}
void NEG_instruction::execute(){

    // execute the neg instruction and update the data memory

    int32_t num1 = (*data_memory)[operand1];
    (*data_memory)[result] = -num1;

    // report the instruction execution log
    std::stringstream log_msg;
    log_msg << "[Thread "<<core_id <<"][" <<  (*instruction_counter) << "] The SIM just negated memory location " << operand1 << " with value " << num1 
            << " and stored it in memory location " << result << " now with value " << (*data_memory)[result] 
            << std::endl;
    set_log_msg(log_msg);
    log();
    // std::cout << log_msg.str();
}

MUL_instruction::MUL_instruction(std::vector<std::string>& p_instruction){
    // define the opcode and validates the number of operands
    opcode = MUL_OPCODE;
    if(p_instruction.size() != 4){
        throw(std::invalid_argument("Invalid number of operands for MUL instruction"));
    }
    operand1 = std::stoi(p_instruction[1]);
    operand2 = std::stoi(p_instruction[2]);
    result = std::stoi(p_instruction[3]);
}
void MUL_instruction::execute(){
    // execute the mul instruction and update the data memory
    int32_t num1 = (*data_memory)[operand1];
    int32_t num2 = (*data_memory)[operand2];
    int32_t op_result = num1 * num2;
    (*data_memory)[result] = op_result;

    // report the instruction execution log
    std::stringstream log_msg;
    log_msg << "[Thread "<<core_id <<"][" <<  (*instruction_counter) << "] The SIM just multiplied memory location " << operand1 << " with value " << num1 
            << " and memory location " << operand2 << " with value " << num2 
            << " and stored it in memory location " << result << " now with value " << (*data_memory)[result] 
            << std::endl;
    set_log_msg(log_msg);
    log();
    // std::cout << log_msg.str();
}


JPA_instruction::JPA_instruction(std::vector<std::string>& p_instruction){
    // define the opcode and validates the number of operands
    opcode = JPA_OPCODE;
    if(p_instruction.size() != 2){
        throw(std::invalid_argument("Invalid number of operands for JPA instruction"));
    }
    operand1 = std::stoi(p_instruction[1]);
}
void JPA_instruction::execute(){
    // execute the jpa instruction and update the instruction counter
    std::stringstream log_msg;
    log_msg << "[Thread "<<core_id <<"][" <<  (*instruction_counter) << "] ";
    
    // make sure the jump is to a valid instruction
    if (operand1 >= 0 && operand1 < *fetched_instructions_count){
        *instruction_counter = operand1-1;
    } else {
        throw(std::invalid_argument("Instruction address out of range for JPA instruction"));
    }
    
    // report the instruction execution log
    log_msg << "The SIM just jumped to instruction address " << (*instruction_counter+1)
            << std::endl;
    set_log_msg(log_msg);
    log();
    // std::cout << log_msg.str();
}

JP0_instruction::JP0_instruction(std::vector<std::string>& p_instruction){
    // define the opcode and validates the number of operands
    opcode = JP0_OPCODE;
    if(p_instruction.size() != 3){
        throw(std::invalid_argument("Invalid number of operands for JP0 instruction"));
    }
    operand1 = std::stoi(p_instruction[1]);
    operand2 = std::stoi(p_instruction[2]);
}
void JP0_instruction::execute(){
    // execute the jp0 instruction and update the instruction counter
    std::stringstream log_msg;
    log_msg << "[Thread "<<core_id <<"][" <<  (*instruction_counter) << "] ";
    
    int32_t num = data_memory->at(operand1);
    if (operand2 >= 0 && operand2 < *fetched_instructions_count){
        if ( num == 0){
            *instruction_counter = operand2-1;
        }
    } else {
        throw(std::invalid_argument("Instruction address out of range for JP0 instruction"));
    }

    // report the instruction execution log
    log_msg << "The SIM just checked memory location " << operand1 << " with value " << num 
            << ((num == 0) ? (" and it was 0, so it jumped to instruction address ") :
            (" and it was not 0, so it did not jump to memory address ")) << (*instruction_counter+1)
            << std::endl;
    set_log_msg(log_msg);
    log();
    // std::cout << log_msg.str();
}

ASI_instruction::ASI_instruction(std::vector<std::string>& p_instruction){
    opcode = ASI_OPCODE;
    if(p_instruction.size() != 3){
        throw(std::invalid_argument("Invalid number of operands for ASI instruction"));
    }
    operand1 = std::stoi(p_instruction[1]);
    operand2 = std::stoi(p_instruction[2]);
}
void ASI_instruction::execute(){
    // std::cout << "Executing ASI instruction" << std::endl;
    (*data_memory)[operand2] = operand1;

    // report the instruction execution log
    std::stringstream log_msg;
    log_msg << "[Thread "<<core_id <<"][" << (*instruction_counter) << "] The SIM just stored the value " << operand1 << " in memory location " << operand2 << " now with value " << (*data_memory)[operand2] << std::endl;
    set_log_msg(log_msg);
    log();
    // std::cout << log_msg.str();
}

LOE_instruction::LOE_instruction(std::vector<std::string>& p_instruction){
    opcode = LOE_OPCODE;
    if(p_instruction.size() != 4){
        throw(std::invalid_argument("Invalid number of operands for LOE instruction"));
    }
    operand1 = std::stoi(p_instruction[1]);
    operand2 = std::stoi(p_instruction[2]);
    result = std::stoi(p_instruction[3]);
}
void LOE_instruction::execute(){
    int32_t num1 = (*data_memory)[operand1];
    int32_t num2 = (*data_memory)[operand2];
    int32_t op_result = num1 <= num2;
    (*data_memory)[result] = op_result;

    // report the instruction execution log
    std::stringstream log_msg;
    log_msg << "[Thread "<<core_id <<"][" << (*instruction_counter) << "] The SIM just compared memory location " << operand1 << " with value " << num1 
            << " and memory location " << operand2 << " with value " << num2 
            << " and stored it in memory location " << result << " now with value " << (*data_memory)[result] 
            << std::endl;
    set_log_msg(log_msg);
    log();
    // std::cout << log_msg.str();
}

HLT_instruction::HLT_instruction(std::vector<std::string>& p_instruction){
    opcode = HLT_OPCODE;
    if(p_instruction.size() != 1){
        throw(std::invalid_argument("Invalid number of operands for HLT instruction"));
    }
}
void HLT_instruction::execute(){

    // report the instruction execution log
    std::stringstream log_msg;
    log_msg << "[Thread "<<core_id <<"][" << (*instruction_counter) << "] The SIM just halted" << std::endl;
    set_log_msg(log_msg);
    log();
    // std::cout << log_msg.str();
}