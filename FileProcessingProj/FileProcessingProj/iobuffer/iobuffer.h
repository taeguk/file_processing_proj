// iobuffer.h
#ifndef IOBUFFER_H
#define IOBUFFER_H
#include <stdlib.h>
#include <iostream>

#ifndef FALSE
#define FALSE (0)
#define TRUE (1)
#endif

using namespace std;

class IOBuffer 
// An abstract base class for file buffers
// Record variables can be packed into and extracted from a buffer.
// Input and Output of packed buffers 
// When each field has a value, the buffer can be written into an ostream.
// 
// operations are provided to allow values to be associated with the fields (Pack)
//	and to fetch the values of fields (Unpack)
// 
{  public:
	IOBuffer (int maxBytes = 1000); // a maximum of maxBytes
	IOBuffer & operator = (const IOBuffer &);
	virtual void Clear (); // clear fields from buffer
	virtual int Pack (const void * field, int size = -1) = 0; // set the value of the next field of the buffer;
	virtual int Unpack (void * field, int maxbytes = -1) = 0; // extract the value of the next field of the buffer
	virtual void Print (ostream &) const;
 	int Init (int maxBytes);
	// the read and write operations return the address of the record
	// sequential read and write operations
	virtual int Read (istream &) = 0; // read a buffer from the stream
	virtual int Write (ostream &) const = 0; // write a buffer to the stream

	// these are the direct access read and write operations
	virtual int DRead (istream &, int recref); // read specified record
	virtual int DWrite (ostream &, int recref) const; // write specified record

	// these header operations return the number of bytes in the header
	virtual int ReadHeader (istream &); // write a buffer to the stream
	virtual int WriteHeader (ostream &) const; // write a buffer to the stream

 protected:
	int Initialized; // TRUE if buffer is initialized
	char * Buffer; // character array to hold field values
	int BufferSize; // sum of the sizes of packed fields
	int MaxBytes; // maximum number of characters in the buffer
	int NextByte; // index of next byte to be packed/unpacked
	int Packing; // TRUE if in packing mode, FALSE, if unpacking
};

// field packing operations
// pack a field into a buffer
int PackFixed (char * buffer, void * field, int size = -1);
int PackDelimeted (char *buffer, void * field, int size = -1);
int PackLength (char * buffer, void * field, int size = -1);

#endif
