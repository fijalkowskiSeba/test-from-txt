#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <vector>

class Task
{
public:
    std::string question;
    std::vector<std::string> answers;
    int answers_count;
    std::string correct_answer;

    Task(std::string question, std::vector<std::string> answers, int answers_count, std::string correct_answer);
};

#endif // TASK_HPP
