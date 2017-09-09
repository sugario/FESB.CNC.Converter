#ifndef READER_H
#define READER_H

#include <IFSelect_ReturnStatus.hxx>
#include <TopoDS_Shape.hxx>

#include <string>

class Reader {
public:
    Reader();
    explicit Reader(const std::string&);

    IFSelect_ReturnStatus ReadFile(const std::string&);

    TopoDS_Shape GetShape();

private:
    IFSelect_ReturnStatus ReadBREP(const std::string&);
    IFSelect_ReturnStatus ReadIGES(const std::string&);
    IFSelect_ReturnStatus ReadSTEP(const std::string&);

    std::string GetFileExtension(const std::string&);

    TopoDS_Shape aShape;
};

#endif  // !READER_H
