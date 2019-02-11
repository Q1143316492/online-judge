//
// Created by cwl on 19-2-11.
// 比较多的lambda表达式定义的函数，因为最开始是函数内定义的小功能
// 后来整合出来，就没有修改了。
#pragma once

#include <bits/stdc++.h>
#include <unistd.h>

namespace util {

    void helloworld() {
        std::cout << "hello world" << std::endl;
    }

    auto isnum = [](char ch) -> bool {
        return ch >= '0' && ch <= '9';
    };

    auto split_string = [](std::string str) -> std::vector<std::string> {
        std::vector<std::string> vec;
        char* ttr = new char[str.size() + 1];
        for(int i = 0; i < str.size(); i++ ) {
            ttr[i] = str[i];
            if(ttr[i] == 9 || ttr[i] == 32) {   // ' ' or '\t'
                ttr[i] = 0;
            }
        }
        ttr[str.size()] = 0;
        for(int i = 0; i < str.size(); i++ ) {
            if((i == 0 && ttr[i] != 0) || (ttr[i - 1] == 0 && ttr[i] != 0)) {
                vec.push_back(ttr + i);
            }
        }
        delete []ttr;
        return vec;
    };


    auto int_to_string = [](int num) -> std::string {
        char str[20] = {0};
        int top = 0;
        if(num == 0) {
            return std::string("0");
        } else {
            while(num) {
                str[top++] = num % 10 + '0';
                num /= 10;
            }
            str[top] = 0;
            std::string number(str);
            std::reverse(number.begin(), number.end());
            return number;
        }
    };

    auto string_to_int = [](std::string number, int default_val = 0) -> int {
        int num = 0;
        for(int i = 0; i < number.size(); i++ ) {
            if(util::isnum(number[i])) {
                num = num * 10 + number[i] - '0';
            } else {
                return default_val;
            }
        }
        return num;
    };

    void start_bash(std::string bash = "/bin/bash") {
        char *c_bash = new char[bash.length() + 1];
        strcpy(c_bash, bash.c_str());
        char* const child_args[] = { c_bash, NULL };
        execv(child_args[0], child_args);
        delete []c_bash;
    }
}
