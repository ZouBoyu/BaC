/*
 * program.h: Declare interfaces of the program.
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

#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <memory>

#include "bac.h"
#include "translate.h"

class program
{
public:
    program(int t_argc, char** t_argv);
    void output_info(); // Output infomation of the application
    void set_game_attribute();  // Set attribute of the game
    int exec(); // Execute

private:
    int argc;
    char** argv;
    std::unique_ptr<bac> game;
    std::string current_dir;
    translate ts;

    // Get directory path from a file path
    std::string get_dir_path(const std::string& path);
    void option_proc();    // Process options
};

#endif // _PROGRAM_H_