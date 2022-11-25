
#ifndef SYSTEM_CALL_HPP
#define SYSTEM_CALL_HPP

#include "SIM.hpp"

class SystemCalls {
    private:
        static std::mutex mtx;
        static int read_data_memory(int32_t address);
        static int write_data_memory(int32_t address, int32_t value);
    public:
        static int32_t syscall(int32_t syscall_id, std::vector<int32_t>& args);
        static void print_data_memory(int start, int end);
        static void print_data_memory(int end = DATA_MEMORY_SIZE);

};

#endif