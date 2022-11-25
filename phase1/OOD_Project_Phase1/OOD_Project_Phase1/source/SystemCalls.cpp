
#include "../headers/SystemCalls.hpp"

std::mutex SystemCalls::mtx;

int SystemCalls::read_data_memory(int32_t address){
    return SIM::data_memory[address];
}

int SystemCalls::write_data_memory(int32_t address, int32_t value){
    SIM::data_memory[address] = value;
    return value;
}

int SystemCalls::syscall(int32_t syscall_id, std::vector<int32_t> & args){
    mtx.lock();
    int return_value = 0;
    switch (syscall_id)
    {
    case ADD_OPCODE:
        assert(args.size() == 3);
        args[0] = read_data_memory(args[0]);
        args[1] = read_data_memory(args[1]);
        args[2] = write_data_memory(args[2], args[0] + args[1]);
        return_value = args[2];
        break;
    case NEG_OPCODE:
        assert(args.size() == 2);
        args[0] = read_data_memory(args[0]);
        args[1] = write_data_memory(args[1], -args[0]);
        return_value = args[1];
        break;
    case MUL_OPCODE:
        assert(args.size() == 3);
        args[0] = read_data_memory(args[0]);
        args[1] = read_data_memory(args[1]);
        args[2] = write_data_memory(args[2], args[0] * args[1]);
        return_value = args[2];
        break;
    case JP0_OPCODE:
        assert(args.size() == 1);
        args[0] = read_data_memory(args[0]);
        return_value = args[0];
        break;
    case ASI_OPCODE:
        assert(args.size() == 2);
        args[1] = write_data_memory(args[1], args[0]);
        return_value = args[1];
        break;
    case LOE_OPCODE:
        assert(args.size() == 3);
        args[0] = read_data_memory(args[0]);
        args[1] = read_data_memory(args[1]);
        args[2] = write_data_memory(args[2], args[0] <= args[1]);
        return_value = args[2];
        break;    
    default:
        return_value = -1;
        break;
    }
    mtx.unlock();
    return return_value;
}

void SystemCalls::print_data_memory(int start, int end){
    std::cout << "======================================" << std::endl;
    std::cout << "Printing data memory from " << start << " to " << end << std::endl;
    for (int i = start; i < end; i++){
        std::cout << "\tdata_memory[" << i << "] = " << SIM::data_memory[i] << std::endl;
    }
    std::cout << "======================================" << std::endl;
}

void SystemCalls::print_data_memory(int end){
    print_data_memory(0, end);
}