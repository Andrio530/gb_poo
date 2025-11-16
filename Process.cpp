#include "Process.h"
#include "ProcessQueue.h"
int Process::next_pid = 1;

Process::Process(int pid_override)
{
    if (pid_override >= 0)
    {
        pid = pid_override;
        if (pid_override >= next_pid)
            next_pid = pid_override + 1;
    }
    else
        pid = next_pid++;
}
int Process::getPid() const { return pid; }
