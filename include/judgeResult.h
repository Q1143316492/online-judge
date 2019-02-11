//
// Created by cwl on 19-2-11.
//

#ifndef STUDY_JUDGERESULT_H
#define STUDY_JUDGERESULT_H

enum class JudgeResult : unsigned int {
    Pending,                //等待评测
    Judging,                //正在评测
    Accepted,               //答案正确
    Wrong_Answer,           //答案错误
    Runtime_Error,          //运行错误
    Time_Limit_Exceeded,    //运行超时
    Memory_Limit_Exceeded,  //内存超限
    Output_Limit_Exceeded,  //输出超限制
    Complication_Error,     //编译错误
    Presentation_Error,      //格式错误
    System_Error
};

struct RealResult {
    RealResult() {
        this->message = std::string("");
        this->tot_time = INF;
        this->tot_memery = DEFAULT_MEMERY;
        this->result = JudgeResult::Pending;
    }
    int tot_time;       //ms
    int tot_memery;     //kb
    std::string message;
    JudgeResult result;
    std::chrono::system_clock::time_point begin_time;
    std::chrono::system_clock::time_point end_time;

};

#endif //STUDY_JUDGERESULT_H
