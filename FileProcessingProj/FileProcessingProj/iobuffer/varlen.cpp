// varlen.cc

#include "varlen.h"
#include <string.h>

//class VariableLengthBuffer

// public members

VariableLengthBuffer :: VariableLengthBuffer (int maxBytes)
 // construct with a maximum of maxFields
: IOBuffer (maxBytes)
{
	Init ();
}

void VariableLengthBuffer :: Clear ()
// clear fields from buffer
{
	IOBuffer::Clear();
}

int VariableLengthBuffer :: Read (istream & stream)
// write the number of bytes in the buffer field definitions
// the record length is represented by an unsigned short value
{
	if (stream.eof()) return -1;
	int recaddr = (int)stream . tellg ();
	Clear ();
	unsigned short bufferSize;
	stream . read ((char *)&bufferSize, sizeof(bufferSize));
	if (! stream . good ()){stream.clear(); return -1;}
	BufferSize = bufferSize;
	if (BufferSize > MaxBytes) return -1; // buffer overflow
	stream . read (Buffer, BufferSize);
	if (! stream . good ()){stream.clear(); return -1;}
	return recaddr;
}


int VariableLengthBuffer :: Write (ostream & stream) const
// write the length and buffer into the stream
{
	int recaddr = (int)stream . tellp ();
	unsigned short bufferSize;
	bufferSize = BufferSize;
	stream . write ((char *)&bufferSize, sizeof(bufferSize));
	if (!stream) return -1;
	stream . write (Buffer, BufferSize);
	if (! stream . good ()) return -1;
	return recaddr;
}

const char * headerStr = "Variable";
//const int headerSize = strlen (headerStr);
const int headerSize = 8;

int VariableLengthBuffer :: ReadHeader (istream & stream)
// read the header and check for consistency
{
	char str[headerSize+1];
	int result;
	// read the IOBuffer header
	result = IOBuffer::ReadHeader (stream);
	if (!result) return FALSE;
	// read the header string
	stream . read (str, headerSize);
	if (!stream.good()) return FALSE;
	if (strncmp (str, headerStr, headerSize) != 0) return FALSE;
	// read and check the record description
	return (int)stream . tellg ();
}

int VariableLengthBuffer :: WriteHeader (ostream & stream) const
// write a buffer header to the beginning of the stream
// A header consists of the 
//	IOBUFFER header	
//	header string
//	Variable sized record of length fields
//		that describes the file records
{
	int result;
	// write the parent (IOBuffer) header
	result = IOBuffer::WriteHeader (stream);
	if (!result) return FALSE;
	// write the header string
	stream . write (headerStr, headerSize);
	if (!stream . good ()) return FALSE;
	// write the record description
	return (int)stream . tellp();
}

void VariableLengthBuffer :: Print (ostream & stream) const
{
	IOBuffer::Print (stream);
}

int VariableLengthBuffer :: Init ()
 // construct with a maximum of maxFields
{
	Clear();
	return TRUE;
}

