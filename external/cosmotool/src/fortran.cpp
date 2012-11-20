#include "config.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "fortran.hpp"

using namespace std;
using namespace CosmoTool;

UnformattedRead::UnformattedRead(const string& fname)
  throw(NoSuchFileException)
{
  f = new ifstream(fname.c_str());
  if (!*f)
    throw NoSuchFileException();

  swapOrdering = false;
  cSize = Check_32bits;
  checkPointRef = checkPointAccum = 0;
}

UnformattedRead::UnformattedRead(const char *fname)
  throw(NoSuchFileException)
{
  f = new ifstream(fname);
  if (!*f)
    throw NoSuchFileException();
  swapOrdering = false;
  cSize = Check_32bits;
  checkPointRef = checkPointAccum = 0;
}


UnformattedRead::~UnformattedRead()
{
  delete f;
}

// Todo implement primitive description
void UnformattedRead::setOrdering(Ordering o)
{
  if (o == LittleEndian)
    {
    }
}

void UnformattedRead::setCheckpointSize(CheckpointSize cs)
{
  cSize = cs;
}
    
void UnformattedRead::skip(int64_t off)
  throw (InvalidUnformattedAccess)
{
  if (checkPointAccum == 0 && checkPointRef == 0)
    {
      // We are not in a checked block
      f->seekg(off, ios::cur);
      return;
    }
  if (off < 0)
    throw InvalidUnformattedAccess();
  
  if ((checkPointAccum+off) > checkPointRef)
       throw InvalidUnformattedAccess();

  f->seekg(off, ios::cur);
  checkPointAccum += off;
}

void UnformattedRead::beginCheckpoint()
  throw (InvalidUnformattedAccess,EndOfFileException)
{
  if (checkPointAccum != 0)
    throw InvalidUnformattedAccess();
  
  checkPointRef = (cSize == Check_32bits) ? 4 : 8;
  checkPointAccum = 0;  

  checkPointRef = (cSize == Check_32bits) ? readInt32() : readInt64();
  checkPointAccum = 0;

  if (f->eof())
    throw EndOfFileException();
}

void UnformattedRead::endCheckpoint(bool autodrop)
  throw (InvalidUnformattedAccess)
{
  if (checkPointRef != checkPointAccum)
    {
      if (!autodrop || checkPointAccum > checkPointRef)
	throw InvalidUnformattedAccess();
      f->seekg(checkPointRef-checkPointAccum, ios::cur);
    }

  int64_t oldCheckPoint = checkPointRef;

  checkPointRef = (cSize == Check_32bits) ? 4 : 8;
  checkPointAccum = 0;
  checkPointRef = (cSize == Check_32bits) ? readInt32() : readInt64();
  
  if (oldCheckPoint != checkPointRef)
    throw InvalidUnformattedAccess();

  checkPointAccum = checkPointRef = 0;
}

void UnformattedRead::readOrderedBuffer(void *buffer, int size)
      throw (InvalidUnformattedAccess)
{
  if ((checkPointAccum+size) > checkPointRef)
       throw InvalidUnformattedAccess();

  f->read((char *)buffer, size);
  
  if (swapOrdering)
    {
      char *cb = (char *)buffer;
      for (int i = 0; i < size/2; i++)
	swap(cb[i], cb[size-i-1]);
    }
  checkPointAccum += size;
}
  
double UnformattedRead::readReal64()
  throw (InvalidUnformattedAccess)
{
  union
  {
    char b[8];
    double d;
  } a;

  readOrderedBuffer(&a, 8);

  return a.d;
}

float UnformattedRead::readReal32()
  throw (InvalidUnformattedAccess)
{
  union
  {
    char b[4];
    float f;
  } a;

  readOrderedBuffer(&a, 4);

  return a.f;
}

int32_t UnformattedRead::readInt32()
  throw (InvalidUnformattedAccess)
{
  union
  {
    char b[4];
    int32_t i;
  } a;

  readOrderedBuffer(&a, 4);

  return a.i;
}

int64_t UnformattedRead::readInt64()
  throw (InvalidUnformattedAccess)
{
  union
  {
    char b[8];
    int64_t i;
  } a;

  readOrderedBuffer(&a, 8);

  return a.i;
}

//// UnformattedWrite

UnformattedWrite::UnformattedWrite(const string& fname)
  throw(NoSuchFileException)
{
  f = new ofstream(fname.c_str());
  if (!*f)
    throw NoSuchFileException();

  swapOrdering = false;
  cSize = Check_32bits;
  checkPointRef = checkPointAccum = 0;
}

UnformattedWrite::UnformattedWrite(const char *fname)
  throw(NoSuchFileException)
{
  f = new ofstream(fname);
  if (!*f)
    throw NoSuchFileException();
  swapOrdering = false;
  cSize = Check_32bits;
  checkPointRef = checkPointAccum = 0;
}


UnformattedWrite::~UnformattedWrite()
{
  delete f;
}

// Todo implement primitive description
void UnformattedWrite::setOrdering(Ordering o)
{
  if (o == LittleEndian)
    {
    }
}

void UnformattedWrite::setCheckpointSize(CheckpointSize cs)
{
  cSize = cs;
}
    
void UnformattedWrite::beginCheckpoint()
  throw (InvalidUnformattedAccess,FilesystemFullException)
{
  if (checkPointAccum != 0)
    throw InvalidUnformattedAccess();
  
  checkPointRef = f->tellp();
  if (cSize == Check_32bits)
    writeInt32(0);
  else
    writeInt64(0);

  checkPointAccum = 0;

  if (!*f)
    throw FilesystemFullException();
}

void UnformattedWrite::endCheckpoint()
  throw (InvalidUnformattedAccess,FilesystemFullException)
{
  if (checkPointAccum == 0)
    throw InvalidUnformattedAccess();

  streampos curPos = f->tellp();

  int64_t deltaPos = curPos-checkPointRef;

  deltaPos -= (cSize == Check_32bits) ? 4 : 8;
  // This is a sanity check.
  if (checkPointAccum != deltaPos)
    throw InvalidUnformattedAccess();

  uint64_t saveAccum = checkPointAccum;

  f->seekp(checkPointRef);
  if (cSize == Check_32bits)
    writeInt32(saveAccum);
  else
    writeInt64(saveAccum);

  f->seekp(curPos);
  if (cSize == Check_32bits)
    writeInt32(saveAccum);
  else
    writeInt64(saveAccum);

  checkPointAccum = checkPointRef = 0;
}

void UnformattedWrite::writeOrderedBuffer(void *buffer, int size)
  throw (FilesystemFullException)
{
  f->write((char *)buffer, size);
  
  if (swapOrdering)
    {
      char *cb = (char *)buffer;
      for (int i = 0; i < size/2; i++)
	swap(cb[i], cb[size-i-1]);
    }
  checkPointAccum += size;

  if (!*f)
    throw FilesystemFullException();
}
  
void UnformattedWrite::writeReal64(double d)
  throw (FilesystemFullException)
{
  union
  {
    char b[8];
    double d;
  } a;

  a.d = d;

  writeOrderedBuffer(&a, 8);
}

void UnformattedWrite::writeReal32(float f)
  throw (FilesystemFullException)
{
  union
  {
    char b[4];
    float f;
  } a;
  
  a.f = f;

  writeOrderedBuffer(&a, 4);
}

void UnformattedWrite::writeInt32(int32_t i)
  throw (FilesystemFullException)
{
  union
  {
    char b[4];
    int32_t i;
  } a;

  a.i = i;
  writeOrderedBuffer(&a, 4);
}

void UnformattedWrite::writeInt64(int64_t i)
  throw (FilesystemFullException)
{
  union
  {
    char b[8];
    int64_t i;
  } a;

  a.i = i;
  writeOrderedBuffer(&a, 8);
}

void UnformattedWrite::writeInt8(int8_t i)
  throw (FilesystemFullException)
{
  union { char b; int8_t i; } a;

  a.i = i;
  writeOrderedBuffer(&a, 1);
}