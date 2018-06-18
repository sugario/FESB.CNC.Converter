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

#include <fstream>
#include <string>

#include <STLTools/STLTools_CountTriangles.h>

namespace stltools {

bool IsASCII(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        return false;
    }

    std::string line;
    std::getline(file, line);
    line = line.substr(0, line.find(" "));

    if (line != "solid") {
        file.close();
        return false;
    }


    while (std::getline(file, line)) {
        line = line.substr(0, line.find(" "));
        if (line == "endsolid") {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool IsBinary(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary);
    int fileLength;
    int numberOfTriangles;

    if (!file.is_open()) {
        return false;
    }

    file.seekg(0, file.end);
    fileLength = static_cast<int>(file.tellg());

    file.seekg(80);
    file.read(reinterpret_cast<char*>(&numberOfTriangles),
              sizeof(numberOfTriangles));

    file.close();

    if (fileLength < 84 || fileLength != (84 + (numberOfTriangles * 50))) {
        return false;
    }

    return true;
}

int GetFormat(const std::string& fileName) {
    std::string extension = fileName.substr(fileName.find_last_of(".") + 1);
    for (unsigned int i = 0; i < extension.length(); i++) {
        extension[i] = toupper(extension[i]);
    }

    if (extension != "STL") {
        return Format::NotSTL;
    } else if (IsASCII(fileName)) {
        return Format::ASCII;
    } else if (IsBinary(fileName)) {
        return Format::BINARY;
    }

    return Format::Unknown;
}

int ReadNumberOfTrianglesFromASCII(const std::string& fileName) {
    int counter = 0;
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("endfacet") != std::string::npos) {
                counter++;
            }
        }

        file.close();
    }

    return counter;
}

int ReadNumberOfTrianglesFromBinary(const std::string& fileName) {
    int numberOfTriangles = 0;
    std::ifstream file(fileName, std::ios::binary);

    if (file.is_open()) {
        file.seekg(80);
        file.read(reinterpret_cast<char*>(&numberOfTriangles),
                  sizeof(numberOfTriangles));

        file.close();
    }

    return numberOfTriangles;
}

int ReadNumberOfTriangles(const std::string& fileName) {
    int format = GetFormat(fileName);

    if (format == Format::ASCII) {
        return ReadNumberOfTrianglesFromASCII(fileName);
    } else if (format == Format::BINARY) {
        return ReadNumberOfTrianglesFromBinary(fileName);
    } else {
        return ERROR_WHILE_READING;
    }
}

}  // namespace stltools
