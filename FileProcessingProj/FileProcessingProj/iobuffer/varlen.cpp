// varlen.cc

#include "varlen.h"
#include <string.h>

using namespace std;

namespace iobuffer
{

	//class VariableLengthBuffer

	// public members

	VariableLengthBuffer::VariableLengthBuffer(int maxBytes)
		// construct with a maximum of maxFields
		: IOBuffer(maxBytes)
	{
		Init();
	}

	void VariableLengthBuffer::Clear()
		// clear fields from buffer
	{
		IOBuffer::Clear();
	}

	int VariableLengthBuffer::Read(istream & stream)
		// write the number of bytes in the buffer field definitions
		// the record length is represented by an unsigned short value
	{
		int recaddr;

		if (stream.eof()) return -1;
		recaddr = (int)stream.tellg();
		Clear();
		unsigned short bufferSize;
		stream.read((char *)&bufferSize, sizeof(bufferSize));
		if (!stream.good()) { stream.clear(); return -1; }
		BufferSize = bufferSize;
		if (BufferSize > MaxBytes) return -1; // buffer overflow
		stream.read(Buffer, BufferSize);
		if (!stream.good()) { stream.clear(); return -1; }
			
		// Deleted data.
		if (Buffer[0] == '*')
			return -2-recaddr;
		else
			return recaddr;
	}


	int VariableLengthBuffer::Write(ostream & stream) const
		// write the length and buffer into the stream
	{
		int recaddr = (int)stream.tellp();
		unsigned short bufferSize;
		bufferSize = BufferSize;
		stream.write((char *)&bufferSize, sizeof(bufferSize));
		if (!stream) return -1;
		stream.write(Buffer, BufferSize);
		if (!stream.good()) return -1;
		return recaddr;
	}

	void VariableLengthBuffer::Delete(std::ostream & stream) const
	{
		stream.seekp(2, ios::cur);
		stream.write("*", 1);
	}

	void VariableLengthBuffer::Reserve(std::ostream & stream, unsigned short record_size) const
	{
		stream.write((char *)&record_size, sizeof(record_size));
		stream.write("*", 1);
	}

	const char * headerStr = "Variable";
	//const int headerSize = strlen (headerStr);
	const int headerSize = 8;

	int VariableLengthBuffer::ReadHeader(istream & stream)
		// read the header and check for consistency
	{
		char str[headerSize + 1];
		int result;
		// read the IOBuffer header
		result = IOBuffer::ReadHeader(stream);
		if (!result) return FALSE;
		// read the header string
		stream.read(str, headerSize);
		if (!stream.good()) return FALSE;
		if (strncmp(str, headerStr, headerSize) != 0) return FALSE;
		// read and check the record description
		return (int)stream.tellg();
	}

	int VariableLengthBuffer::WriteHeader(ostream & stream) const
		// write a buffer header to the beginning of the stream
		// A header consists of the 
		//	IOBUFFER header	
		//	header string
		//	Variable sized record of length fields
		//		that describes the file records
	{
		int result;
		// write the parent (IOBuffer) header
		result = IOBuffer::WriteHeader(stream);
		if (!result) return FALSE;
		// write the header string
		stream.write(headerStr, headerSize);
		if (!stream.good()) return FALSE;
		// write the record description
		return (int)stream.tellp();
	}

	void VariableLengthBuffer::Print(ostream & stream) const
	{
		IOBuffer::Print(stream);
	}

	int VariableLengthBuffer::Init()
		// construct with a maximum of maxFields
	{
		Clear();
		return TRUE;
	}

}