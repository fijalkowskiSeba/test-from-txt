#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <cstdlib>
#include "Task.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "No path to file / too many arguments";
    }
    std::string file_path = argv[1];
    // std::cout<<file_path;

    std::vector<Task> tasks;

    std::ifstream my_file;
    my_file.open(file_path);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::string line = "";
    if (my_file.is_open())
    {
        std::string question = "";
        std::vector<std::string> answers = std::vector<std::string>();
        int answers_count = 0;
        std::string correct_answer;

        char counter = 'A';
        while (std::getline(my_file, line))
        {

            if (line[0] != '-')
            {
                if (answers.size() != 0)
                {
                    std::shuffle(answers.begin(), answers.end(), gen);
                    Task new_task(question, answers, answers_count, correct_answer);
                    tasks.push_back(new_task);
                    answers_count = 0;
                    answers.clear();
                }

                // std::cout << line + "\n";
                counter = 'A';

                question = line;
            }
            else
            {
                line.erase(0, 2);
                // std::cout << counter;
                // std::cout << ". " + line + "\n";
                if (counter == 'A')
                {
                    correct_answer = line;
                }
                answers.push_back(line);
                answers_count++;
                counter += 1;
            }
            // std::cout << line + "\n";
        }
        Task new_task(question, answers, answers_count, correct_answer);
        tasks.push_back(new_task);
        answers_count = 0;
        answers.clear();
    }

    std::shuffle(tasks.begin(), tasks.end(), gen);

    std::cout << "Loaded " << tasks.size() << " questions\n";

    // Game starts here
    int game_size = 0;
    std::cout << "How many questions?\n";
    std::cin >> game_size;
    int points = 0;
    if (game_size < 1 || game_size > tasks.size())
    {
        std::cout << "Incorrect size !!!\n";
        return (1);
    }

    int game = 0;
    for (auto task : tasks)
    {
        game++;
        std::cout << "\033[1;34m" << task.question << "\033[0m\n";
        char counter = 'A';
        char correct_answer = '0';
        for (auto answer : task.answers)
        {
            if (answer == task.correct_answer)
            {
                correct_answer = counter;
            }

            std::cout << counter << ". " << answer << "\n";
            counter++;
        }
        char user_answer;
        std::cin >> user_answer;
        user_answer = std::toupper(user_answer);
        char x;
        if (user_answer == correct_answer)
        {
            std::cout << "\033[1;32mPoprawna odpowiedz\033[0m\n";
            points++;
            system("pause");
            system("cls");
        }
        else
        {
            std::cout << "\033[1;31mPoprawna odpowiedz to " << correct_answer << "\033[0m\n";
            system("pause");
            system("cls");
        }

        if (game == game_size)
        {
            break;
        }
    }

    std::cout << "Game over\n"
              << "Score: " << points << " / ";
    std::cout << std::to_string(game_size);
}
