/*
 * advget.h: Define advanced get data functions.
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

#ifndef _ADVGET_H_
#define _ADVGET_H_

#include <istream>
#include <string>

// Get data from streams safely to prevent problems caused by different data types
template<typename T>
bool safe_get(std::istream& is, T& data)
{
    is >> data;
    if (is.fail())
    {
        is.clear();
        is.ignore(4096, '\n');
        return false;
    }
    else
        return true;
}

// Interactive input with prompt
template<typename T>
T interactive_safe_get(const std::string& prompt)
{
    T val;
    bool flag = false;
    do
    {
        cout << prompt;
        flag = safe_get(std::cin, val);
    } while (!flag);
    return val;
}

template<typename T>
T interactive_safe_get(const std::string& prompt, const T max, const T min)
{
    T val;
    bool flag = false;
    do
    {
        cout << prompt;
        flag = safe_get(std::cin, val);
    } while (!(flag && val <= max && val >= min));
    return val;
}

#endif // _ADVGET_H_
