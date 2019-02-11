#include "include/OnlineJudge.h"

int main(int argc, char *argv[])
{
    std::cout << "========================Judging begin=========================" << std::endl;

    if(argc != 6) {
        std::cout << "========================Judging begin=========================" << std::endl;
        exit(0);
    }

    /** run.sh
     *  g++ main.cpp -std=c++11
        mv a.out main
        #time_limit user_problem std_in user_in std:out
        ./main 2 ./user_pro/user_ac ./user_pro/1.in ./user_pro/user.out ./user_pro/1.out
        ./main 2 ./user_pro/user_wa ./user_pro/1.in ./user_pro/user.out ./user_pro/1.out
        ./main 2 ./user_pro/user_tle ./user_pro/1.in ./user_pro/user.out ./user_pro/1.out
        ./main 2 ./user_pro/user_re ./user_pro/1.in ./user_pro/user.out ./user_pro/1.out
        ./main 2 ./user_pro/user_tle_2 ./user_pro/1.in ./user_pro/user.out ./user_pro/1.out
     * */

    int pid = fork();

    std::string time = argv[1];             //代码时间限制
    std::string path = argv[2];             //代码编译后路径
    std::string input_file = argv[3];       //标准输入测试案例
    std::string output_file = argv[4];      //用户输出测试案例
    std::string answer_file = argv[5];      //标准答案

    Problem problem(time, path, input_file, output_file, answer_file);

    if(pid < 0) {
        exit(0);
    }

    if(pid == 0) {
        OnlineJudge::child_program(getpid(), problem);
    } else {
        RealResult result;
        result.begin_time = std::chrono::system_clock::now();
        OnlineJudge::father_program(getpid(), pid, problem, result);
    }

    std::cout << "========================Judging end=========================" << std::endl;

    return 0;
}