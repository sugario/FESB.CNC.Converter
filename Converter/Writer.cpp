#include <BRep_Builder.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

#include <TopoDS_Compound.hxx>

#include <string>

#include "Writer.h"

Writer::Writer() {
    this->aShape.Nullify();
    this->precision = 0.0001;
    this->usingY0ZMirror = false;
}

Writer::Writer(const TopoDS_Shape &aShape) {
    this->aShape = aShape;

    this->precision = 0.0001;
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
    if (this->aShape.IsNull()) {
        return StlAPI_ErrorStatus::StlAPI_MeshIsEmpty;
    }

    TopoDS_Compound aCompound;
    BRep_Builder aBuilder;

    aBuilder.MakeCompound(aCompound);
    aBuilder.Add(aCompound, this->aShape);

    if (this->usingY0ZMirror) {
        TopoDS_Shape aMirroredShape = this->MakeYOZMirror(this->aShape);
        aBuilder.Add(aCompound, aMirroredShape);
    }

    StlAPI_Writer myStlWriter;
    BRepMesh_IncrementalMesh(aCompound, this->precision);

    return myStlWriter.Write(aCompound, aFileName.c_str());
}

TopoDS_Shape Writer::MakeYOZMirror(const TopoDS_Shape& aShape) {
    gp_Trsf aTrsf = gp_Trsf();
    aTrsf.SetMirror(gp::YOZ());

    return BRepBuilderAPI_Transform(aShape, aTrsf).Shape();
}
