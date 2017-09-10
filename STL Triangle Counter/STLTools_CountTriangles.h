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

#ifndef STLTOOLS_COUNT_TRIANGLES_H
#define STLTOOLS_COUNT_TRIANGLES_H

#include <string>

namespace STLTools {

#define ERROR_WHILE_READING -1;

enum Format {
    ASCII,
    BINARY,
    NotSTL,
    Unknown
};

bool IsASCII(const std::string&);

bool IsBinary(const std::string&);

int GetFormat(const std::string&);

int ReadNumberOfTrianglesFromASCII(const std::string&);

int ReadNumberOfTrianglesFromBinary(const std::string&);

int ReadNumberOfTriangles(const std::string&);

}  // namespace STLTools

#endif  // !STLTOOLS_COUNT_TRIANGLES_H
