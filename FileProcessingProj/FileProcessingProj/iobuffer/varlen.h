// fvarlen.h
#ifndef VARLEN_H
#define VARLEN_H

#include <stdlib.h>
#include <iostream>
#include "iobuffer.h"

namespace iobuffer
{

	class VariableLengthBuffer : public IOBuffer
		// Abstract class designed to support variablelength records
		// Fields may be of a variety of types
		//   
	{
	public:
		VariableLengthBuffer(int MaxBytes = 1000);
		VariableLengthBuffer(const VariableLengthBuffer & buffer) // copy constructor
			: IOBuffer(buffer) {}

		void Clear(); // clear fields from buffer
		int Read(std::istream &);
		int Write(std::ostream &) const;
		int ReadHeader(std::istream &); // write a buffer to the stream
		int WriteHeader(std::ostream &) const; // write a buffer to the stream
		int PackFixLen(void *, int);
		int PackDelimeted(void *, int);
		int PackLength(void *, int);
		void Print(std::ostream &) const;
		int SizeOfBuffer() const; // return current size of buffer
		int Init();
	protected:
	};

}

#endif
