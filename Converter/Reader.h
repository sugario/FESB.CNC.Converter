#ifndef READER_H
#define READER_H

#include <iostream>

#include <TopoDS_Shape.hxx>

enum ReaderStatus : int {
	UnknownError,
	FileNotFound,
	ExtensionNotFound,
	UnknownFileFormat,
	NotImplemented,
	Success
};

class Reader
{
public:
	Reader();
	Reader(const std::string&);

	ReaderStatus ReadFile(const std::string&);

	TopoDS_Shape GetShape();

private:
	ReaderStatus ReadBREP(const std::string&);
	ReaderStatus ReadIGES(const std::string&);

	std::string GetFileExtension(const std::string&);

	TopoDS_Shape aShape;
};

#endif // !READER_H