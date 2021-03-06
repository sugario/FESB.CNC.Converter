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

#ifndef READER_H
#define READER_H

#include <IFSelect_ReturnStatus.hxx>
#include <TopoDS_Shape.hxx>

#include <ShapeAnalysis_ShapeContents.hxx>

#include <string>

class Reader {
 public:
    Reader();
    explicit Reader(const std::string&);

    IFSelect_ReturnStatus ReadFile(const std::string&);

    TopoDS_Shape GetShape(void);

 private:
    IFSelect_ReturnStatus ReadBREP(const std::string&);
    IFSelect_ReturnStatus ReadIGES(const std::string&);
    IFSelect_ReturnStatus ReadSTEP(const std::string&);

    std::string GetFileExtension(const std::string&);
    ShapeAnalysis_ShapeContents GetShapeAnalizer(void);

    ShapeAnalysis_ShapeContents analizer;
    TopoDS_Shape aShape;
};

#endif  // !READER_H
