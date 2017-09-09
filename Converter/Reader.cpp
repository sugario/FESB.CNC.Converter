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

#include <BRep_Builder.hxx>
#include <BRepTools.hxx>

#include <IGESControl_Reader.hxx>
#include <STEPControl_Reader.hxx>

#include <string>

#include "../Converter/Reader.h"

Reader::Reader() {
    this->aShape.Nullify();
}

Reader::Reader(const std::string& aFileName) {
    if (ReadFile(aFileName) != IFSelect_ReturnStatus::IFSelect_RetDone) {
        this->aShape.Nullify();
    }
}

IFSelect_ReturnStatus Reader::ReadFile(const std::string& aFileName) {
    this->aShape.Nullify();
    std::string extension = GetFileExtension(aFileName);

    if (extension == "") {
        return IFSelect_ReturnStatus::IFSelect_RetFail;
    } else if (extension == "brep") {
        return ReadBREP(aFileName);
    } else if (extension == "igs" || extension == "iges") {
        return ReadIGES(aFileName);
    } else if (extension == "step" ||
        extension == "stp" ||
        extension == "p21") {
        return ReadSTEP(aFileName);
    } else {
        return IFSelect_ReturnStatus::IFSelect_RetError;
    }
}

TopoDS_Shape Reader::GetShape(void) {
    return this->aShape;
}

IFSelect_ReturnStatus Reader::ReadBREP(const std::string& aFileName) {
    std::filebuf aFileBuf;
    std::istream aStream(&aFileBuf);

    if (!aFileBuf.open(aFileName, ios::in)) {
        return IFSelect_ReturnStatus::IFSelect_RetError;
    }

    BRep_Builder aBuilder;
    BRepTools::Read(this->aShape, aStream, aBuilder);

    return IFSelect_ReturnStatus::IFSelect_RetDone;
}

IFSelect_ReturnStatus Reader::ReadIGES(const std::string& aFileName) {
    IGESControl_Reader aReader;

    if (aReader.ReadFile(aFileName.c_str()) != IFSelect_RetDone) {
        return IFSelect_ReturnStatus::IFSelect_RetError;
    }

    aReader.TransferRoots();
    this->aShape = aReader.OneShape();

    return IFSelect_ReturnStatus::IFSelect_RetDone;
}

IFSelect_ReturnStatus Reader::ReadSTEP(const std::string& aFileName) {
    STEPControl_Reader aReader;

    if (aReader.ReadFile(aFileName.c_str()) != IFSelect_RetDone) {
        return IFSelect_ReturnStatus::IFSelect_RetError;
    }

    aReader.TransferRoots();
    this->aShape = aReader.OneShape();

    return IFSelect_ReturnStatus::IFSelect_RetDone;
}

std::string Reader::GetFileExtension(const std::string& aFileName) {
    std::string extension = aFileName.substr(aFileName.find_last_of(".") + 1,
        aFileName.length());

    if (aFileName == extension) {
        extension = "";
    }

    for (unsigned int i = 0; i < extension.length(); i++) {
        extension[i] = tolower(extension[i]);
    }

    return extension;
}
