/*
 * bac.cpp: Define interfaces about Bulls and Cows game.
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
#include <vector>
#include <list>
#include <random>

#include "bac.h"

bac::bac(unsigned short t_len) :
    answer(0), count(0), length(t_len >= 10 || t_len <= 0 ? 4 : t_len)
{
    // Check value of the number
    if (t_len >= 10 || t_len <= 0)
        throw std::invalid_argument("Argument too big or small!");
}

unsigned bac::get_answer()
{
    return answer;
}

unsigned bac::get_count()
{
    return count;
}

unsigned short bac::get_length()
{
    return length;
}

void bac::generate()
{
    answer = 0;
    count = 0;

    // Random sorting of numbers from 0 to 9
    std::list<unsigned short> num = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::random_device rd;  // Non-deterministic generator

    // Set answer
    for (unsigned i = 1; i <= length; ++i)
    {
        unsigned n = rd() % num.size();
        auto it = num.begin();
        for (unsigned j = 1; j <= n; ++j)
            ++it;

        // Avoid the number starting with 0
        if (i == 1 && *it == 0)
            ++it;

        answer *= 10;
        answer += *it;
        num.erase(it);
    }
}

bac::judge_result bac::judge(unsigned t_num)
{
    judge_result result = { 0, 0 };
    unsigned t_ans = answer;
    std::vector<unsigned short> user, ans;

    // Check digits of the number
    unsigned digit = 0, tmp = t_num;
    while (tmp != 0)
    {
        ++digit;
        tmp /= 10;
    }
    if (digit != length)
    {
        throw std::invalid_argument("Digits of the number is error!");
        return result;
    }

    ++count;

    // Decomposition four digits
    for (size_t i = 0; i < length; ++i)
    {
        user.push_back(t_num % 10);
        t_num /= 10;
        ans.push_back(t_ans % 10);
        t_ans /= 10;
    }

    // Compare arrays
    for (size_t i = 0; i < length; ++i)
    {
        for (size_t j = 0; j < length; ++j)
        {
            if (user.at(i) == ans.at(j))
            {
                if (i == j)
                    ++result.A;
                else
                    ++result.B;
            }
        }
    }
    return result;
}
