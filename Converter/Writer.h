#ifndef WRITER_H
#define WRITER_H

#include <TopoDS_Shape.hxx>

#include <StlAPI_Writer.hxx>

class Writer {
public:
	Writer();
	explicit Writer(const TopoDS_Shape&);

	void UseMirror(void);
	void SetPrecision(const double&);
	void SetShape(const TopoDS_Shape&);
	
	StlAPI_ErrorStatus WriteToFile(const std::string&);

private:
	TopoDS_Shape MakeYOZMirror(const TopoDS_Shape&);

	bool usingY0ZMirror;
	double precision;
	
	TopoDS_Shape aShape;
};

#endif // !WRITER_H