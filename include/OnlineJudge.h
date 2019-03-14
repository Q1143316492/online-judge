//
// Created by cwl on 19-2-11.
//

#ifndef STUDY_ONLINEJUDGE_H
#define STUDY_ONLINEJUDGE_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/ptrace.h>
#include "Problem.h"
#include "util.h"
#include "judgeResult.h"

using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

class OnlineJudge {
public:

    static void father_program(const int this_pid, const int child_pid, Problem problem, RealResult &result) {
        listen_child_program(child_pid, problem, result);
    }

    static void child_program(const int this_pid, Problem problem) {
        //ptrace(PTRACE_TRACEME, 0, NULL, NULL);                   // 让父进程监控此子进程
        set_user_limit(problem);                                 // set problem limit
        set_freopen(problem.input_file, problem.output_file);    // set file freopen
        util::start_bash(problem.pathname.c_str());              //run user problem
    }

private:

    static void set_freopen(std::string input, std::string output) {
        freopen(input.c_str(), "r", stdin);
        freopen(output.c_str(), "w", stdout);
    }

    static void set_user_limit(Problem problem) {
        struct rlimit *r = new rlimit();
        r->rlim_cur = problem.time_limit;
        r->rlim_max = problem.time_limit;
        setrlimit(RLIMIT_CPU, r);
        setrlimit(RLIMIT_CORE, NULL);   //禁止创建core文件, 内核转存文件, 因为好像没什么用
    }

    static void listen_child_program(const int child_pid, Problem &problem, RealResult &result) {

        int status = 0;
        struct rusage use;
        result.tot_memery = get_progress_memery(child_pid);

        int wait_pid = wait4(child_pid, &status, 0, &use);

        result.end_time = system_clock::now();
        result.tot_time = duration_cast<milliseconds>(result.end_time - result.begin_time).count();


        /**
         * ptrace(PTRACE_KILL, pid, NULL, NULL);
         * ptrace(PTRACE_GETREGS, pid, NULL, &reg); //一次性读取所有的寄存器的内容
         * ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
         * */

        // WIFEXITED(status) 这个宏用来指出子进程是否为正常退出的，如果是，它会返回一个非零值
        // WEXITSTATUS(status) 当WIFEXITED返回非零值时，我们可以用这个宏来提取子进程的返回值

        // exit success spj
        if(WIFEXITED(status)) {
            //std::cout << "WIFEXITED = " << WEXITSTATUS(status) << std::endl;

            if(result.tot_memery > DEFAULT_MEMERY) {
                ptrace(PTRACE_KILL, child_pid, NULL, NULL);         //干掉子进程
                result.result = JudgeResult::Memory_Limit_Exceeded;
            } else if(Problem::check_answer(problem.output_file.c_str(), problem.answer_file.c_str())) {
                result.result = JudgeResult::Accepted;
            } else {
                result.result = JudgeResult::Wrong_Answer;
            }
            return ;
        }

        // exit fail

        if(WIFSIGNALED(status)) {
            switch WTERMSIG(status) {
                case SIGXCPU:   // TLE
                    result.result = JudgeResult::Time_Limit_Exceeded;
                break;
                case SIGKILL:   // TLE
                    result.result = JudgeResult::Time_Limit_Exceeded;
                break;
                case SIGXFSZ:   // OLE
                    result.result = JudgeResult::Output_Limit_Exceeded;
                break;
                default:        // RE
                    result.result = JudgeResult::Runtime_Error;
                break;
            }
        }


        if(result.result == JudgeResult::Accepted) {
            std::cout << "Accept" << std::endl;
        }
        if(result.result == JudgeResult::Wrong_Answer) {
            std::cout << "Wrong answer" << std::endl;
        }
        if(result.result == JudgeResult::Time_Limit_Exceeded) {
            std::cout << "Time limit except" << std::endl;
        }
        if(result.result == JudgeResult::Runtime_Error) {
            std::cout << "Running time error" << std::endl;
        }
        if(result.result == JudgeResult::Output_Limit_Exceeded) {
            std::cout << "Output limit except" << std::endl;
        }
    }

    //
    // 根据进程id, 读取/proc/pid/status文件获取内存消耗
    //
    static int get_progress_memery(const int pid) {
        //VmPeak:   290748 kB
        auto show = [](std::vector<std::string>vec) {
            puts("");
            for(auto &str: vec) {
                std::cout << "[" << str << "]";
            }
        };

        std::string path = "/proc/";
        path += util::int_to_string(pid);
        path += "/status";

        std::ifstream fp(path);
        std::string line;
        std::string goal = "VmPeak:";
        while(getline(fp, line)) {
            std::vector<std::string>vec = util::split_string(line);
            if(vec.size() == 3 && vec[0] == goal) {
                return util::string_to_int(vec[1], INF);
            }
        }
        return INF;
    }
};

#endif //STUDY_ONLINEJUDGE_H
