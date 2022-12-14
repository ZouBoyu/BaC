/*
 * program.cpp: Def interfaces of the program.
 * Copyright 2022 Zou Boyu
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "configure.h"
#include "program.h"
#include "advget.h"

using std::cout;
using std::endl;

program::program(int t_argc, char** t_argv)
{
    argc = t_argc;
    argv = t_argv;
    option_proc(); // Process options
}

void program::option_proc()
{
    bool exit = false;
    if (argc <= 1)
        return; // Return if no arguments
    for (char* arg = argv[1]; arg != argv[0] + argc; ++arg)
    {
        // Compare the argument with option
        if (!strcmp(arg, "-h") || !strcmp(arg, "--help"))
        {
            cout << "帮助(Help): " << endl;
            cout << "--------------------" << endl;
            cout << "    计算机将生成没有重复数的数字， 您来猜。" << endl;
            cout << "每次猜测数字，计算机就根据这个数字输出[]A[]B，"
                << "其中A前面的数字表示数值和位置正确的数值的个数，"
                << "而B前的数字表示数字正确而位置不对的数值的个数。" << endl;
            cout << "例如：正确答案为 5834，而猜的人猜 5346，则输出是 1A2B。" << endl;
            cout << "--------------------" << endl;
            cout << "选项(Option): " << endl;
            cout << " -h, --help    显示帮助" << endl;
            cout << "--------------------" << endl;
            exit = true;
        }
        else
        {
            std::cerr << "Unkown option: \"" << arg << "\"" << endl;
            exit = true;
        }
    }
    if (exit == true)
    {
        std::exit(2);   // Exit the program
    }
}

// Output infomation of the application
void program::output_info()
{
    cout << "猜数字游戏(Bulls and Cows Game)" << endl;
    cout << "版本(Version): " << PROJECT_VERSION << '-' << PROJECT_RELEASE_TYPE
        << " (" << PROJECT_BUILDER << ")" << endl;
    cout << "根据Apache许可证2.0版许可" << endl
        << "Licensed under the Apache License Version 2.0" << endl;
}

// Set attribute of the game
void program::set_game_attribute()
{
    // Get digits of the number
    unsigned short len = interactive_safe_get(
        "输入数字位数(Input digits of the number) (0-9): ", 9, 1);

    // Allocate a bac object and have it owned by std::unique_ptr
    game = std::make_unique<bac>(len);

    // Generate answer of game
    game->generate();
}
// Start the game
int program::start_game()
{
    set_game_attribute();
    while (true)
    {
        unsigned num = interactive_safe_get<unsigned>("输入(Input) > ");
        bac::judge_result result{ 0, 0 };

        // Compare num with the answer and save the result
        try
        {
            result = game->judge(num);
        }
        catch (const std::invalid_argument& err)
        {
            std::cerr << err.what() << '\n';
        }

        if (result.A == game->get_length())
        {
            // Game over
            cout << "====================" << endl;
            cout << "恭喜! 正确！" << endl;
            cout << "Congratulation! RIGHT!" << endl;
            cout << "总计数(Final count): " << game->get_count() << endl;
            cout << "Q/q退出，N/n重新开始(Input Q/q to quit, N/n to restart)" << endl;
            // Quit or Restart
            std::cin.clear();
            std::cin.ignore(4096, '\n');
            char ch = std::cin.get();
            if (ch == 'q' || ch == 'Q')
            {
                break;
            }
            else if (ch == 'n' || ch == 'N')
            {
                set_game_attribute();
                continue;
            }
        }
        cout << "计数(Count): " << game->get_count() << endl;
        cout << "结果(Result): *" << result.A << "A" << result.B << "B*" << endl;
    }

    return EXIT_SUCCESS;    // success exit
}
