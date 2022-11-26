
#include "../headers/SystemCalls.hpp"

// static variables
std::mutex SystemCalls::mtx[DATA_MEMORY_SIZE];

// reads data memory at address
int SystemCalls::read_data_memory(int32_t address){
    return SIM::data_memory[address];
}

// writes a value to data memory at address
int SystemCalls::write_data_memory(int32_t address, int32_t value){
    SIM::data_memory[address] = value;
    return value;
}

// locks the mutex at addresses
void SystemCalls::lock(const std::vector<int32_t>& addresses){
    std::set <int32_t> locked;
    for (int i = 0; i < addresses.size(); i++){
        if (locked.find(addresses[i]) == locked.end()){
            mtx[addresses[i]].lock();
            locked.insert(addresses[i]);
        }
    }
}

// unlocks the mutex at addresses
void SystemCalls::unlock(const std::vector<int32_t>& addresses){
    std::set <int32_t> unlocked;
    for (int i = 0; i < addresses.size(); i++){
        if (unlocked.find(addresses[i]) == unlocked.end()){
            mtx[addresses[i]].unlock();
            unlocked.insert(addresses[i]);
        }
    }
}

/* handles the system calls and ensures thread safety by locking the mutex when
    reading from and writing to the data memory 
    syscall_id: the operation opcode to be performed
    args: the arguments to be passed to the operation (contains the addresses or values)
    return args: the value for each address in args
    return value: the result written to data memory
*/
int SystemCalls::syscall(int32_t syscall_id, std::vector<int32_t> & args){
    int return_value = 0;
    std::vector <int32_t> addresses;
    switch (syscall_id)
    {
    case ADD_OPCODE:
        assert(args.size() == 3);
        addresses = {args[0], args[1], args[2]};
        lock(addresses);
        args[0] = read_data_memory(args[0]);
        args[1] = read_data_memory(args[1]);
        args[2] = write_data_memory(args[2], args[0] + args[1]);
        unlock(addresses);
        return_value = args[2];
        break;
    case NEG_OPCODE:
        assert(args.size() == 2);
        addresses = {args[0], args[1]};
        lock(addresses);
        args[0] = read_data_memory(args[0]);
        args[1] = write_data_memory(args[1], -args[0]);
        unlock(addresses);
        return_value = args[1];
        break;
    case MUL_OPCODE:
        assert(args.size() == 3);
        addresses = {args[0], args[1], args[2]};
        lock(addresses);
        args[0] = read_data_memory(args[0]);
        args[1] = read_data_memory(args[1]);
        args[2] = write_data_memory(args[2], args[0] * args[1]);
        unlock(addresses);
        return_value = args[2];
        break;
    case JP0_OPCODE:
        assert(args.size() == 1);
        addresses = {args[0]};
        lock(addresses);
        args[0] = read_data_memory(args[0]);
        unlock(addresses);
        return_value = args[0];
        break;
    case ASI_OPCODE:
        assert(args.size() == 2);
        addresses = {args[1]};
        lock(addresses);
        args[1] = write_data_memory(args[1], args[0]);
        unlock(addresses);
        return_value = args[1];
        break;
    case LOE_OPCODE:
        assert(args.size() == 3);
        addresses = {args[0], args[1], args[2]};
        lock(addresses);
        args[0] = read_data_memory(args[0]);
        args[1] = read_data_memory(args[1]);
        args[2] = write_data_memory(args[2], args[0] <= args[1]);
        unlock(addresses);
        return_value = args[2];
        break;    
    default:
        return_value = -1;
        break;
    }
    return return_value;
}

// prints the data memory from start to end
void SystemCalls::print_data_memory(int start, int end){
    std::cout << "======================================" << std::endl;
    std::cout << "Printing data memory from " << start << " to " << end << std::endl;
    for (int i = start; i < end; i++){
        std::cout << "\tdata_memory[" << i << "] = " << SIM::data_memory[i] << std::endl;
    }
    std::cout << "======================================" << std::endl;
}

// prints the data memory from 0 to end
void SystemCalls::print_data_memory(int end){
    print_data_memory(0, end);
}