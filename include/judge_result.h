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

std::ostream &operator << (std::ostream &os, const RealResult &res) {

    std::string msg = "";
    switch (res.result) {
        case JudgeResult::Pending : msg = "Pending"; break;
        case JudgeResult::Judging : msg = "Judging"; break;
        case JudgeResult::Accepted : msg = "Accept"; break;
        case JudgeResult::Wrong_Answer : msg = "Wrong_Answer"; break;
        case JudgeResult::Runtime_Error : msg = "Runtime_Error"; break;
        case JudgeResult::Time_Limit_Exceeded : msg = "Time_Limit_Exceeded"; break;
        case JudgeResult::Memory_Limit_Exceeded : msg = "Memory_Limit_Exceeded"; break;
        case JudgeResult::Output_Limit_Exceeded : msg = "Output_Limit_Exceeded"; break;
        case JudgeResult::Complication_Error : msg = "Complication_Error"; break;
        case JudgeResult::Presentation_Error : msg = "Presentation_Error"; break;
        case JudgeResult::System_Error : msg = "System_Error"; break;
    }

    os << "Result: " << msg << std::endl;
    os << "Memery: " << res.tot_memery << "KB" << std::endl;
    os << "Times : " << res.tot_time << "MS" ;
    return os;
}

#endif //STUDY_JUDGERESULT_H
