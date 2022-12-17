/*
 * bac.h: Declare interfaces about Bulls and Cows game.
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

#ifndef _BAC_H_
#define _BAC_H_

 // declare interface

class bac
{
public:
    struct judge_result
    {
        unsigned A;
        unsigned B;
    };
    bac() = default;
    bac(unsigned short t_len);

    inline unsigned get_answer() { return answer; }
    inline unsigned get_count() { return count; }
    inline unsigned short get_length() { return length; }

    void generate();    // Generate four digits with different numbers
    judge_result judge(unsigned t_num);    // Compare parameters with answers

private:
    unsigned answer = 0;
    unsigned count = 0;
    const unsigned short length = 4;
};

#endif // _BAC_H_
