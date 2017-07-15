#include "Reader.h"

#include <BRep_Builder.hxx>
#include <BRepTools.hxx>

#include <IGESControl_Reader.hxx>

Reader::Reader()
{
	this->aShape.Nullify();
}

Reader::Reader(const std::string& aFileName)
{
	if (ReadFile(aFileName) != ReaderStatus::Success)
	{
		this->aShape.Nullify();
	}
}

ReaderStatus Reader::ReadFile(const std::string& aFileName)
{
	this->aShape.Nullify();
	std::string extension = GetFileExtension(aFileName);

	if (extension == "")
	{
		return ReaderStatus::ExtensionNotFound;
	}
	else if (extension == "brep")
	{
		ReadBREP(aFileName);
	}
	else if (extension == "igs" || extension == "iges")
	{
		ReadIGES(aFileName);
	}
	else if (extension == "step" || extension == "stp" || extension == "p21")
	{
		return ReaderStatus::NotImplemented;
	}
	else
	{
		return ReaderStatus::UnknownFileFormat;
	}

	return ReaderStatus::Success;
}

TopoDS_Shape Reader::GetShape(void)
{
	return this->aShape;
}

ReaderStatus Reader::ReadBREP(const std::string& aFileName)
{
	std::filebuf aFileBuf;
	std::istream aStream(&aFileBuf);

	if (!aFileBuf.open(aFileName, ios::in))
	{
		return ReaderStatus::FileNotFound;
	}

	BRep_Builder aBuilder;
	BRepTools::Read(this->aShape, aStream, aBuilder);

	return ReaderStatus::Success;
}

ReaderStatus Reader::ReadIGES(const std::string& aFileName)
{
	IGESControl_Reader aReader;

	if (aReader.ReadFile(aFileName.c_str()) != IFSelect_RetDone)
	{
		return ReaderStatus::FileNotFound;
	}

	aReader.TransferRoots();
	this->aShape = aReader.OneShape();

	return ReaderStatus::Success;
}

std::string Reader::GetFileExtension(const std::string& aFileName)
{
	std::string extension = aFileName.substr(aFileName.find_last_of(".") + 1, aFileName.length());

	if (aFileName == extension)
	{
		extension = "";
	}

	for (unsigned int i = 0; i < extension.length(); i++) {
		extension[i] = tolower(extension[i]);
	}

	return extension;
}