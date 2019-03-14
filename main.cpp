#include <bits/stdc++.h>
#include "include/OnlineJudge.h"
#include "include/ComplicationCpp.h"
#include "include/mydocker.h"
#include "include/config.h"

int main(int argc, char *argv[])
{

    std::cout << "========================Judging begin=========================" << std::endl;

    if(argc != 6) {
        std::cout << "========================Judging end=========================" << std::endl;
        exit(0);
    }

    int pid = fork();

    std::string time = argv[1];                            //代码时间限制
    std::string path = PROJECT_PATH + argv[2];             //代码可执行程序
    std::string input_file = PROJECT_PATH + argv[3];       //标准输入测试案例
    std::string output_file = PROJECT_PATH + argv[4];      //用户输出测试案例
    std::string answer_file = PROJECT_PATH + argv[5];      //标准答案

    RealResult result;

    Problem problem(time, path, input_file, output_file, answer_file);

    if(pid < 0) {
        exit(0);
    }

    if(pid == 0) {
        OnlineJudge::child_program(getpid(), problem);
    } else {
        result.begin_time = std::chrono::system_clock::now();
        OnlineJudge::father_program(getpid(), pid, problem, result);
        std::cout << result << std::endl;
    }

    std::cout << "========================Judging end=========================" << std::endl;

    return 0;
}