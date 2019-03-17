//
// Created by cwl on 19-2-11.
//

#ifndef STUDY_COMPLICATIONCPP_H
#define STUDY_COMPLICATIONCPP_H

#include <bits/stdc++.h>
#include "config.h"
#include "mydocker.h"

enum class ComplicationStatus : unsigned int {
    FILE_NOT_EXIT,
    ERROR,
    SUCCESS
};

class complication_cpp {
public:
    complication_cpp() = default;
    complication_cpp(std::string filename):cppfile_name(filename) {}

    void setComplicationFileName(std::string filename) {
        this->cppfile_name = filename;
    }

    std::string getComplicationComonmend(std::string parm = " -std=c++11 ") {
        std::string cmd = " g++ ";
                    cmd += this->cppfile_name;
                    cmd += parm;
        return cmd;
    }

    ComplicationStatus build(RealResult &result) {
        std::string test = DEFAULT_JUDGE_PATH;
        mydocker::changeRunDir(DEFAULT_JUDGE_PATH);
        //system(" pwd ");
        //system(" ls ");
        system("make -s 1>msg.log 2>error.log ");
        std::ifstream file("./error.log");
        std::string tmp;
        while(!file.eof()) {
            getline(file, tmp);
            result.message += tmp;
        }
        std::cout << "build message: [" << result.message << "]" << std::endl;
        file.open("./error.log");
        tmp = "";
        while(!file.eof()) {
            getline(file, tmp);
            result.message += tmp;
        }
        std::cout << "build message: [" << result.message << "]" << std::endl;
        return ComplicationStatus::SUCCESS;
    }

private:
    std::string cppfile_name;
};

#endif //STUDY_COMPLICATIONCPP_H
