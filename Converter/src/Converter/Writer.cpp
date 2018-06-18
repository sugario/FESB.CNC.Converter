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
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

#include <TopoDS_Compound.hxx>

#include <string>

#include <Converter/Writer.h>
#include "Converter/StlAPI_ErrorStatus.h"

Writer::Writer() {
    this->aShape.Nullify();
    this->precision = 0.1;
    this->usingY0ZMirror = false;
}

Writer::Writer(const TopoDS_Shape &aShape) : aShape {aShape} {
    this->precision = 0.1;
    this->usingY0ZMirror = false;
}

void Writer::UseMirror(void) {
    this->usingY0ZMirror = true;
}

void Writer::SetPrecision(const double& precision) {
    if (precision > 0) {
        this->precision = precision;
    }
}

void Writer::SetShape(const TopoDS_Shape& aShape) {
    this->aShape = aShape;
}

StlAPI_ErrorStatus Writer::WriteToFile(const std::string& aFileName) {
    printf("[Writer] Trying to write file \"%s\"\n", aFileName.c_str());

    if (this->aShape.IsNull()) {
        return StlAPI_ErrorStatus::StlAPI_MeshIsEmpty;
    }

    TopoDS_Compound aCompound;
    BRep_Builder aBuilder;

    aBuilder.MakeCompound(aCompound);
    aBuilder.Add(aCompound, this->aShape);

    if (this->usingY0ZMirror) {
        printf("[Writer] Appending Y0Z mirror\n");
        TopoDS_Shape aMirroredShape = this->MakeYOZMirror(this->aShape);
        aBuilder.Add(aCompound, aMirroredShape);
    }

    StlAPI_Writer myStlWriter;
    BRepMesh_IncrementalMesh(aCompound, this->precision);

    printf("[Writer] Current precision: %lf\n", this->precision);

    // UPDATE TO 7.3.0 (SHOULD RETURN BOOL)
    myStlWriter.Write(aCompound, aFileName.c_str());
    return StlAPI_ErrorStatus::StlAPI_StatusOK;
}

TopoDS_Shape Writer::MakeYOZMirror(const TopoDS_Shape& aShape) {
    gp_Trsf aTrsf = gp_Trsf();
    aTrsf.SetMirror(gp::YOZ());

    return BRepBuilderAPI_Transform(aShape, aTrsf).Shape();
}
