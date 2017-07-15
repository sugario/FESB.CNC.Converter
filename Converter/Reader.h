#ifndef READER_H
#define READER_H

#include <IFSelect_ReturnStatus.hxx>
#include <TopoDS_Shape.hxx>

class Reader
{
public:
	Reader();
	Reader(const std::string&);

	IFSelect_ReturnStatus ReadFile(const std::string&);

	TopoDS_Shape GetShape();

private:
	IFSelect_ReturnStatus ReadBREP(const std::string&);
	IFSelect_ReturnStatus ReadIGES(const std::string&);

	std::string GetFileExtension(const std::string&);

	TopoDS_Shape aShape;
};

#endif // !READER_H