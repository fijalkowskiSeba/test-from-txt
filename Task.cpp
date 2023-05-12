#include "Task.hpp"

Task::Task(std::string question, std::vector<std::string> answers, int answers_count, std::string correct_answer)
    : question(question), answers(answers), answers_count(answers_count), correct_answer(correct_answer)
{
}
