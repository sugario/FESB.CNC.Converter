# FESB.CNC.Converter
Convert supported CAD formats into native stereolithography file format (.stl).

*Created as a part of [FESB](https://eng.fesb.unist.hr/) (Faculty of Electrical Engineering, Mechanical Engineering and Naval Architecture in Split) university project
and built using [Open CASCADE Technology](https://www.opencascade.com/).*

## Input formats supported
- Boundary representation (BREP)
- The Initial Graphics Exchange Specification (IGES)
- Standard for the Exchange of Product model data (ISO 10303, STEP)

## Usage
    Converter.exe

        -i [ --infile ] arg     Name of file to convert
        -o [ --outfile ] arg    Name of file generated after conversion
        --precision arg         Real number that defines line deflection of model
                                during conversion (smaller number will result in better
                                resolution of final model)
        -m                      Combine shape with its YOZ mirror
        -h [ --help ]           Print help(usage) messages

## Prerequisite
OCCT installation is mandatory (64-bit version provided in *3rdparty/opencascade-7.3.0/install*).
1. go to provided folder
2. extract *install.zip*
3. install *opencascade-7.3.0-vc14-64*

After doing these steps, head to installed OCCT folder and add each tool in the folder to environment variables.
These should include:
> ffmpeg; freeimage; freetype; opencascade; qt; tbb; tcltk; vtk

## Configure Visual Studio to use OCCT
    1. Open project properties (Right lick on Project -> Properties)
    2. Include Files Path (C++ =>General => Additional Include Directories) : Include folder path of the Opencascde
    3. Library Files Path (Linker => General => Additional Library Directories) : Add Lib folder path of the Opencascade
    4.* Additional Dependencies (Linker => Input => Additional Dependencies) : Add OCCT Lib Names

* - may not be needed

### Full list of OCCT 7.3.0 Lib names that are used or may be used in future
```
TKBin.lib;TKBinL.lib;TKBinTObj.lib;TKBinXCAF.lib;TKBO.lib;TKBool.lib;TKBRep.lib;TKCAF.lib;TKCDF.lib;TKD3DHost.lib;TKDCAF.lib;TKDFBrowser.lib;TKDraw.lib;TKernel.lib;TKFeat.lib;TKFillet.lib;TKG2d.lib;TKG3d.lib;TKGeomAlgo.lib;TKGeomBase.lib;TKHLR.lib;TKIGES.lib;TKIVtk.lib;TKIVtkDraw.lib;TKLCAF.lib;TKMath.lib;TKMesh.lib;TKMeshVS.lib;TKOffset.lib;TKOpenGl.lib;TKPrim.lib;TKQADraw.lib;TKService.lib;TKShapeView.lib;TKShHealing.lib;TKStd.lib;TKStdL.lib;TKSTEP.lib;TKSTEP209.lib;TKSTEPAttr.lib;TKSTEPBase.lib;TKSTL.lib;TKTInspector.lib;TKTInspectorAPI.lib;TKTObj.lib;TKTObjDRAW.lib;TKToolsDraw.lib;TKTopAlgo.lib;TKTopTest.lib;TKTreeModel.lib;TKV3d.lib;TKVCAF.lib;TKView.lib;TKViewerTest.lib;TKVInspector.lib;TKVRML.lib;TKXCAF.lib;TKXDEDRAW.lib;TKXDEIGES.lib;TKXDESTEP.lib;TKXMesh.lib;TKXml.lib;TKXmlL.lib;TKXmlTObj.lib;TKXmlXCAF.lib;TKXSBase.lib;TKXSDRAW.lib;
```
