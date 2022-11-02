#include "../headers/Parser.hpp"
#include "../headers/Instruction.hpp"

void parser::init_parser(){
    input_code_path = "";
    fetched_instructions_count = 0;
    seek_position = 0;
    instructions.clear();
    factory = InstructionFactory();
}

parser::parser() {
    init_parser();
}
std::vector<std::string> parser::split(std::string line){
    std::stringstream ss(line); 
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    return vstrings;
}

parser::parser(std::string _input_code_path) {
    init_parser();
    input_code_path = _input_code_path;
}

int parser::parse() {
    // returns the number of instructions fetched and places them in the instructions vector
    instructions.clear();
    std::ifstream input_file(input_code_path, std::ios::in);
    if(!input_file.is_open()) {
        std::cerr << "Error opening file: " << input_code_path << " - " << strerror(errno) << std::endl;
        return -1;
    }
    if (!input_file.seekg(seek_position, std::ios::beg)) {
        std::cerr << "Error seeking file" << strerror(errno) << std::endl;
        return 0;
    }
    if (input_file.eof()) {
        std::cerr << "EOF" << std::endl;
        return 0;
    }
    int counter = 0;
    while (counter < INSTRUCTION_MEMORY_SIZE) {
        std::string line;
        if(!std::getline(input_file, line) || line.empty()){
           break;
        }
        seek_position = input_file.tellg();
        
        std::vector<std::string> split_instructions = split(line);
        opcode_t opcode = get_opcode(split_instructions);
        Instruction* instruction = factory.create_instruction(opcode, split_instructions);
        instruction->log();
        instructions.push_back(instruction);
        counter++;
    }
    return counter;
}
const std::unordered_map<std::string, opcode_t>& parser::Opcodes() { 
    static const auto* opcodes = new std::unordered_map<std::string, opcode_t>
    { 
        {"ADD", ADD_OPCODE},
        {"NEG", NEG_OPCODE},
        {"MUL", MUL_OPCODE},
        {"JPA", JPA_OPCODE},
        {"JPO", JPO_OPCODE},
        {"ASI", ASI_OPCODE},
        {"LOE", LOE_OPCODE},
        {"HLT", HLT_OPCODE},
    }; 
    return *opcodes; 
}
bool match(std::string& str1, std::string str2) {
    return str1.compare(str2) == 0;
}

opcode_t parser::get_opcode(std::vector<std::string>& p_instruction){
    std::string& operation = p_instruction[0];
    size_t arguments_count = p_instruction.size();

    if(match(operation, "ADD")){
        return Opcodes().at("ADD");
    }
    else if(match(operation, "NEG")){
        return Opcodes().at("NEG");
    }
    else if(match(operation, "MUL")){
        return Opcodes().at("MUL");
    }
    else if(match(operation, "JPA")){
        return Opcodes().at("JPA");
    }
    else if (match(operation, "JPo")){
        return Opcodes().at("JPo");
    }
    else if (match(operation, "ASI")){
        return Opcodes().at("ASI");
    }
    else if(match(operation, "LOE")){
        return Opcodes().at("LOE");
    }
    else if (match(operation, "HLT")){
        return Opcodes().at("HLT");
    }
    else {
        return 0;
    }
}

std::vector<Instruction*>& parser::get_instructions(){
    return instructions;
}

parser::~parser() {
    input_code_path = "";
    fetched_instructions_count = 0;
    seek_position = 0;
    instructions.clear();
}
