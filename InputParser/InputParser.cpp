/*
 *
 * Copyright 2017 Tino Melvan
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <vector>
#include <string>

#include "../InputParser/InputParser.h"

InputParser::InputParser(const int& argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        this->aToken.push_back(std::string(argv[i]));
    }
}

const std::string& InputParser::GetCommandOption(const std::string& option) {
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->aToken.begin(), this->aToken.end(), option);

    if (itr != this->aToken.end() && ++itr != this->aToken.end()) {
        if (!Contains(this->aUsedToken, *itr)) {
            this->aUsedToken.push_back(*itr);
        }

        return *itr;
    }

    static const std::string str("");
    return str;
}

bool InputParser::CommandOptionExists(const std::string& option) {
    if (Contains(this->aToken, option)) {
        if (!Contains(this->aUsedToken, option)) {
            this->aUsedToken.push_back(option);
        }

        return true;
    }

    return false;
}

bool InputParser::UsedAllCommands(void) {
    return this->aToken.size() == this->aUsedToken.size();
}

bool InputParser::Contains(const std::vector<std::string>& token,
                           const std::string& argument) {
    std::vector<std::string>::const_iterator itr;
    itr = std::find(token.begin(), token.end(), argument);

    if (itr != token.end()) {
        return true;
    }

    return false;
}
