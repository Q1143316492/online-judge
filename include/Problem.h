//
// Created by cwl on 19-2-11.
//

#ifndef STUDY_PROBLEM_H
#define STUDY_PROBLEM_H

#include <bits/stdc++.h>
#include "util.h"

const int INF = 0x7FFFFFFF;
const int DEFAULT_MEMERY = 1024 * 1024 * 128; // 默认内存限制 128 MB

class Problem {
public:
    int memery_limit;   //kb
    int time_limit;     //s
    std::string pathname;
    std::string input_file;
    std::string output_file;
    std::string answer_file;

    Problem() = default;
    Problem(std::string &input_time, std::string &path,
            std::string &input_file, std::string &output_file, std::string &answer_file) {
        time_limit = util::string_to_int(input_time);
        memery_limit = DEFAULT_MEMERY;
        pathname = path;
        this->input_file = input_file;
        this->output_file = output_file;
        this->answer_file = answer_file;
    }

    //
    // 完全一致为AC否则WA
    //
    static bool check_answer(const char* answer_file1, const char* answer_file2) {
        std::ifstream input1(answer_file1);
        std::ifstream input2(answer_file2);
        if(!input1.is_open() || !input2.is_open()) {
            return false;
        }
        while(1) {
            if(input1.eof() && input2.eof()) {
                return true;
            }
            if(input1.eof() || input2.eof()) {
                return false;
            }
            if(input1.get() != input2.get()) {
                return false;
            }
        }
        return true;    //避免clang++等编译器报错
    }

};


#endif //STUDY_PROBLEM_H
