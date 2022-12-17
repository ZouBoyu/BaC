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
#include <stdexcept>
#include <cstring>
#include <cstdlib>

#include "configure.h"
#include "program.h"
#include "advget.h"

using std::cout;
using std::endl;

program::program(int t_argc, char** t_argv) :
    argc(t_argc), argv(t_argv), game(nullptr), current_dir(""), ts("")
{
    option_proc(); // Process options
}

// Output infomation of the application
void program::output_info()
{
    cout << ts("Bulls and Cows Game") << endl;
    cout << ts("Version") << ": " << PROJECT_VERSION << '-' << PROJECT_RELEASE_TYPE
         << '(' << PROJECT_BUILDER << ')' << endl;
    cout << ts("Licensed under the Apache License Version 2.0") << endl;
    cout << ts("Current Language") << ": " << ts.get_language() << endl;
}

// Set attribute of the game
void program::set_game_attribute()
{
    // Get digits of the number
    unsigned short len = interactive_safe_get(
        ts("Input digits of the number") + " (0-9): ", 9, 1);

    // Allocate a bac object and have it owned by std::unique_ptr
    game = std::make_unique<bac>(len);

    // Generate answer of game
    game->generate();
}
// Start the game
int program::exec()
{
    set_game_attribute();
    bool exit = false;
    while (!exit)
    {
        unsigned num = interactive_safe_get<unsigned>(ts("Input") + "> ");
        bac::judge_result result{ 0, 0 };

        // Compare num with the answer and save the result
        try
        {
            result = game->judge(num);
        }
        catch (const std::invalid_argument& err)
        {
            std::cerr << "Error:" << err.what() << '\n';
        }

        if (result.A != game->get_length())
        {
            cout << ts("Count:") + ' ' << game->get_count() << endl;
            cout << ts("Result:") + " *" << result.A << "A" << result.B << "B*" << endl;
        }
        else
        {
            // Game over
            cout << "====================" << endl;
            cout << ts("Congratulation! RIGHT!") << endl;
            cout << ts("Final count:") + ' ' << game->get_count() << endl;
            cout << ts("Input Q/q to quit, N/n to restart.") << endl;
            // Reset standard input stream
            std::cin.clear();
            std::cin.ignore(4096, '\n');
            do
            {
                char ch = '\0';
                safe_get(std::cin, ch);

                // Quit or Restart
                if (ch == 'q' || ch == 'Q')
                {
                    exit = true;    // Exit in next cycle
                    break;
                }
                else if (ch == 'n' || ch == 'N')
                {
                    set_game_attribute();
                    break;
                }
            } while (true);
            continue;
        }
    }

    return EXIT_SUCCESS;    // success exit
}

void program::option_proc()
{
    bool exit = false;
    if (argc == 0)
        throw std::invalid_argument("Error: 'argc' can not be 0!");

    std::string path(argv[0]);
    char separator = '\0';
#ifdef _WIN32
    // A Windows path: "C:\\Users\\user\\data"
    separator = '\\';
#else
    // A Unix-like path: "/home/user/data"
    separator = '/';
#endif // _WIN32
    current_dir = path.substr(0, path.find_last_of(separator)); // Get the directory path
    ts.load(current_dir + separator + "language");

    if (argc == 1)
        return;

    // Foreach in argv
    for (char* arg = argv[1]; arg != argv[0] + argc; ++arg)
    {
        // Compare the argument with option

        if (!strcmp(arg, "-h") || !strcmp(arg, "--help"))
        {
            cout << ts("Help:") << endl;
            cout << "--------------------" << endl;
            cout << ts("The computer will generate a number without repeating digits.");
            cout << ts("Every time you guess,")
                 << ts("the computer will output []A[]B according to this number.")
                 << endl;
            cout << ts("The number before A is the number of correct number,")
                 << ts("The number before B is the number of value correct but postion wrong.")
                 << endl;
            cout << ts("For example: Answer: 5834 Input: 5346 Output: 1A2B")
                 << endl;
            cout << "--------------------" << endl;
            cout << ts("Option:") << endl;
            cout << " -h, --help    " << ts("View help") << endl;
            cout << "--------------------" << endl;
            std::exit(3);
        }
        else
        {
            std::cerr << ts("Unkown option") + ": \"" << arg << "\"!" << endl;
            std::exit(EXIT_FAILURE);
        }
    }
}
