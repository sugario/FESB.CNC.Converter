# FESB.CNC.Converter
Convert chosen CAD formats into native stereolithography file format (.stl). <br/><br/> 
*Created as a part of FESB (Faculty of Electrical Engineering, Mechanical Engineering and Naval Architecture in Split) university project, 
and built using Open CASCADE Technology.*
[FESB](https://eng.fesb.unist.hr/) - [OCCT](https://www.opencascade.com/)

## Formats supported
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
        
## Configure Visual Studio to use OCCT
    0. Configure environment variables
        Add OCCT bin folder path to "Path" variable. Find every 3rd party's bin folder (that has it) and add it too.
    1. Open project properties (Right lick on Project -> Properties)
    2. Include Files Path (C++ =>General => Additional Include Directories) : Include folder path of the Opencascde
    3. Library Files Path (Linker => General => Additional Library Directories) : Add Lib folder path of the Opencascade
    4. Additional Dependencies (Linker => Input => Additional Dependencies) : Add OCCT Lib Names
    
### Full list of OCCT 7.1.0 Lib names that are used or may be used in future
```
TKBin.lib;TKBinL.lib;TKBinTObj.lib;TKBinXCAF.lib;TKBO.lib;TKBool.lib;TKBRep.lib;TKCAF.lib;TKCDF.lib;TKDCAF.lib;TKernel.lib;TKFeat.lib;TKFillet.lib;TKGeomAlgo.lib;TKGeomBase.lib;TKHLR.lib;TKIGES.lib;TKLCAF.lib;TKMath.lib;TKMesh.lib;TKMeshVS.lib;TKOffset.lib;TKOpenGl.lib;TKPrim.lib;TKService.lib;TKShHealing.lib;TKStd.lib;TKStdL.lib;TKSTEP.lib;TKSTEP209.lib;TKSTEPAttr.lib;TKSTEPBase.lib;TKSTL.lib;TKTObj.lib;TKTopAlgo.lib;TKTopTest.lib;TKV3d.lib;TKVCAF.lib;TKVRML.lib;TKXCAF.lib;TKXDEIGES.lib;TKXDESTEP.lib;TKXMesh.lib;TKXml.lib;TKXmlL.lib;TKXmlTObj.lib;TKXSBase.lib
```
