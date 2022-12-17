/*
 * translate.cpp: Define interfaces for multilingual translation.
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

#include <algorithm>
#include <iostream>

#include "translate.h"

using std::string;

translate::translate(const string& file_path) : ifs(file_path)
{
    load(file_path);    // Load the translation
}

bool translate::load(const std::string& file_path)
{
    // Clean up old data
    ifs.close();

    ifs.open(file_path);
    if (ifs)
    {
        status = true;
        language = operator()("^LANGUAGE");
    }
    else
    {
        // Can not open the translation
        status = false;
        language = "Unkown";
    }
    return status;
}

std::string translate::operator()(const std::string& text)
{
    ifs.clear();
    ifs.seekg(0);
    string str;
    while (std::getline(ifs, str))
    {
        // Judge whether it is a comment
        if (str[0] == '#')
            continue;
        
        size_t index = str.find('@');
        if (index == str.npos)
        {
            // Can not find character '@' in current line
            continue;
        }
        if (str.substr(0, index) == text)
        {
            return str.substr(index + 1, str.size());
        }
    }
    return text;
}
