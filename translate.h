/*
 * translate.h: Declare interfaces for multilingual translation.
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

#ifndef _TRANSLATE_H_

#include <string>
#include <fstream>

class translate
{
public:
    translate(const std::string& file_path);
    bool load(const std::string& file_path);  // Open the translation
    std::string operator()(const std::string& text); // Get translation by text
    inline bool get_status() { return status; }   // Get status
    inline std::string get_language() { return language; } // Get language
private:
    bool status;
    std::string language;   // Language of the translation
    std::ifstream ifs;
};

#endif // _TRANSLATE_H_