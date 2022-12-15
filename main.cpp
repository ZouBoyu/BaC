/*
 * main.cpp: Define the entry point for the application.
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

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#include "program.h"

int main(int argc, char** argv)
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);  // Using UTF-8 on Windows
#endif
    program prog(argc, argv);
    prog.output_info();
    return prog.start_game();
}
