/*
** EPITECH PROJECT, 2020
** CCP_zia_2019
** File description:
** SharedMemory
*/

// #include "PlazzaError.hpp"
#include "SharedMemory.hpp"

void SharedMemory::write_data(key_t key, size_t data_size, size_t process, std::string data)
{
    char *tmp = get_data(key, data_size, process);
    
    if (sprintf(tmp, "%s\n", data.c_str()) < 0)
        throw(("sprintf() failed."));
    detach_from(tmp);
}

char *SharedMemory::get_data(key_t key, size_t data_size, size_t process) const
{
    char *data = nullptr;

    data = get_data_by_id(shm_id_gen(key, data_size, process));
    return data;
}

char *SharedMemory::get_data_by_id(int shmId) const
{
    char *data = nullptr;

    if ((data = (char *)shmat(shmId, (void *)0, 0)) == (void *)-1)
        throw(("shmat() failed."));
    return data;
}

void SharedMemory::detach_from(const void *data)
{
    if (shmdt(data) == -1)
        throw(("shmdt() failed."));
}

void SharedMemory::destroy(int shmId, int process)
{
    if (shmctl(shmId, process, NULL) == -1)
        throw(("shmctl() failed."));
}

key_t SharedMemory::key_gen(std::string pathname, int proj_id)
{
    return ftok(pathname.c_str(), proj_id);
}

int SharedMemory::shm_id_gen(key_t key, size_t data_size, size_t process)
{
    int shmId = 0;

    if ((shmId = shmget(key, data_size, 0666 | process)) < 0)
        throw(("shmget() failed."));
    return shmId;
}