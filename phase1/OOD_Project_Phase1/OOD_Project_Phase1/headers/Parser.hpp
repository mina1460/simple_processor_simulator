#ifndef PARSER_HPP
#define PARSER_HPP

#include "includes.hpp"
#include "Instruction.hpp"

class parser {
    public:
        parser();
        parser(std::string input_code_path);
        void init_parser();
        void log(Instruction& p_instruction);
        int parse();
        const std::unordered_map<std::string, opcode_t>& Opcodes(); 
        opcode_t get_opcode(std::vector<std::string>& p_instruction);
        std::vector<Instruction*>& get_instructions();
        std::vector<std::string> split(std::string line); 
        ~parser();
    private:
        std::string input_code_path;
        std::vector<Instruction*> instructions;
        int fetched_instructions_count;
        int64_t seek_position;
        InstructionFactory factory;
};
#endif /* PARSER_HPP */
