#include "util/loopbuf.h"
extern"C" {
#include <pthread.h>
#include <unistd.h>
};

#include <stdio.h>
#include <vector>
#include <iostream>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

using namespace std;

namespace hyper {
namespace util {
///////////////////////////////////////////////////////////////////////////////
//
// MEMBER FUNCTIONS OF CLoopBufBase

//
// Function Name:CLoopBufBase::CLoopBufBase()
//
// Comments: Default constructor of CLoopBufBase
//
CLoopBufBase::CLoopBufBase():m_bValid(false),m_pSharedBuffer(NULL)
{}

//
// End of MEMBER FUNCTIONS OF CLoopBufBase
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// MEMBER FUNCTIONS OF class CLoopBufInProcess

//
// Function Name:CLoopBufInProcess::CLoopBufInProcess(int bufferSize)
//
// Comments:
// CLoopBufInProcess Constructor. Create an internal buffer and semaphore.
//
CLoopBufInProcess::CLoopBufInProcess(int bufferSize)
{
	if (bufferSize<sizeof(SHARED_BUFFER))
	{
		// The buffersize is too small for the loop buffer operation
		return;	
	}
	m_pSharedBuffer=(PSHARED_BUFFER)new char[bufferSize];
	memset((void*)m_pSharedBuffer,0,bufferSize);
	if (!m_pSharedBuffer) return;

	//
	// Initialize the pthread semaphore
	//
	int res=sem_init(&m_Sem,0,1);
	if (res!=0)
	{
		delete []m_pSharedBuffer;
		m_pSharedBuffer=NULL;
		return;
	}

	NOTIFYBUFFER& loop_buffer=m_pSharedBuffer->notify_buffer;
	loop_buffer.TotalSize=bufferSize-sizeof(SHARED_BUFFER);
	loop_buffer.WIndex=0;
	loop_buffer.RIndex=0;
	loop_buffer.UnReadDataAvail=0;
	m_pSharedBuffer->ulSig=0xbeefdead;

	//
	// Now configure the header section of loopbuffer
	//
	m_bValid=true;
}

//
// Function Name:CLoopBufInProcess::~CLoopBufInProcess()
//
// Comments:
// Destructor
//
CLoopBufInProcess::~CLoopBufInProcess()
{
	delete []m_pSharedBuffer;
	if (IsValid())	sem_destroy(&m_Sem);
}

//
// Function Name:bool CLoopBufInProcess::Write(char* buffer, int size)
//
// Comments:
//
//  Write data to the loopbuffer
//
bool CLoopBufInProcess::Write(char* data, int datasize)
{
	if( !data || datasize <= 0)	return false;

	//
	// If loop buffer is full, return false
	//
	NOTIFYBUFFER& loop_buffer=m_pSharedBuffer->notify_buffer;

	unsigned long dataFieldSize=(datasize + 3)& ~3;
	unsigned long totalDataSize =  sizeof(unsigned long)+dataFieldSize;

 
	unsigned long CurrentWriteOffset=0;
	{
		AtomLock atomLock(m_Sem);
		if (loop_buffer.UnReadDataAvail+totalDataSize>loop_buffer.TotalSize)
		{
			return false;
		}

		//
		// Claim the write index and UnReadDataAvail at this point
		//
		CurrentWriteOffset=loop_buffer.WIndex;
		loop_buffer.UnReadDataAvail+=totalDataSize;
		
		loop_buffer.WIndex=(loop_buffer.WIndex+totalDataSize)%loop_buffer.TotalSize;
	}

 	
	//
	// Copy the data to the loop buffer
	//
 	unsigned long* pSizeField = (unsigned long*)( loop_buffer.buffer + CurrentWriteOffset );
 	//
	// Note, the *pSizeField must be 0 because its initial value is 0 and the 
	// entire data block is reset to 0 by the read function after the data 
	// block is read. Therefore, an available data block must have the size 
	// filed of 0. We can add debug function here. such as  ASSERT( *pSizeField == 0 );

	unsigned long DataWriteOffset=  (CurrentWriteOffset+sizeof(unsigned long))%loop_buffer.TotalSize;
 	if( DataWriteOffset + dataFieldSize > loop_buffer.TotalSize) 
	{
		unsigned long first_chunk_size = loop_buffer.TotalSize - DataWriteOffset;
		memcpy( loop_buffer.buffer + DataWriteOffset, data, first_chunk_size );
		memcpy( loop_buffer.buffer, data + first_chunk_size, dataFieldSize - first_chunk_size );
	}
	else
	{
		memcpy( loop_buffer.buffer + DataWriteOffset, data, dataFieldSize );
	}

	//
	// Claim the data size field with the data lengh
	//
	*pSizeField = dataFieldSize;
	return true;
}


//
// Function Name:bool CLoopBufInProcess::Read(vector<char>&)
//
// Comments:
//
//  Read data from the loopbuffer
//
bool CLoopBufInProcess::Read(vector<char>& retBuffer)
{
	NOTIFYBUFFER& loop_buffer=m_pSharedBuffer->notify_buffer;
	{
		AtomLock atomLock(m_Sem);
		if (loop_buffer.UnReadDataAvail==0) return false;
	}

	unsigned long entry_size = *(unsigned long*)(loop_buffer.buffer + loop_buffer.RIndex);
	if (!entry_size)
	{
		//
		// The write operation for this entry is not ready, return 0 bytes
		// to notify caller
		//
		retBuffer.resize(0);
		return true;
	}

	//
	// Clean up this entry
	//
	*(unsigned long*)(loop_buffer.buffer + loop_buffer.RIndex) = 0;

	// Copy the  data to a vector
	loop_buffer.RIndex = (loop_buffer.RIndex + sizeof(entry_size)) % loop_buffer.TotalSize;

	retBuffer.resize(entry_size);
	char* start = loop_buffer.buffer + loop_buffer.RIndex;
	char* end = loop_buffer.buffer + loop_buffer.RIndex + entry_size;

	if(end > loop_buffer.buffer + loop_buffer.TotalSize)
	{
		int remaining = loop_buffer.TotalSize - loop_buffer.RIndex;

		std::copy(start, loop_buffer.buffer + loop_buffer.TotalSize, retBuffer.begin());
		std::fill(start, loop_buffer.buffer + loop_buffer.TotalSize, 0);
		std::copy(loop_buffer.buffer, loop_buffer.buffer + entry_size - remaining, 	retBuffer.begin() + remaining);
		std::fill(loop_buffer.buffer, loop_buffer.buffer + entry_size - remaining,  0);
	}
	else
	{
		std::copy(start, end, retBuffer.begin());
		std::fill(start, end, 0);
	}

	// Advance the read index and update the UnReadDataAvail
	loop_buffer.RIndex = (loop_buffer.RIndex + entry_size) % loop_buffer.TotalSize;
	{
		AtomLock atomLock(m_Sem);
		loop_buffer.UnReadDataAvail-=(entry_size+sizeof(unsigned long));
	}
 	return true;
}


//
// End of MEMBER FUNCTIONS OF CLoopBufInProcess
//
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//
// Constructor
//

CLoopbufIPC::CLoopbufIPC(unsigned long size, key_t key,bool bshmOwner)
{
	m_bShmCreated=false;
	m_bSemCreated=false;

	if (size<sizeof(SHARED_BUFFER)) return;
	m_bOwner=bshmOwner;
	if (!AcquireSharedMemory(key,size)) return;
	m_bShmCreated=true;

	if (m_bOwner)
	{
		m_pSharedBuffer->ulSig=0xbeefdead;
		m_pSharedBuffer->notify_buffer.WIndex=0;
		m_pSharedBuffer->notify_buffer.RIndex=0;
		m_pSharedBuffer->notify_buffer.UnReadDataAvail=0;
		m_pSharedBuffer->notify_buffer.TotalSize=size-sizeof(SHARED_BUFFER);
		key_t semkey;
		if (!CreateSemaphore(semkey))
		{
			cout<<"Unable to create a new semaphore"<<endl;
			return;
		}
		m_bSemCreated=true;
		m_pSharedBuffer->atomKey=(unsigned long)semkey;
	}
	else
	{
		if (!OpenSemaphore((key_t)m_pSharedBuffer->atomKey)) return;
		m_bSemCreated=true;
	}
	m_bValid=true;
}

//
// Destructor
//

CLoopbufIPC::~CLoopbufIPC()
{
	if (m_bShmCreated)
	{
		shmdt(m_pSharedBuffer);
	}
	if (m_bOwner)
	{
		if (m_bSemCreated)
		{
			union semun {	int val;};
			semun sem_union;
			if (semctl(m_SemId,0, IPC_RMID, sem_union)==-1)
			{
				cout<<"Unable to delete semaphore value"<<endl;
			}
		}
		if (m_bShmCreated)
		{
			shmctl(m_ShmId, IPC_RMID,0);
		}
	}
}

//
// MEMBER FUNCTIONS OF class CLoopbufIPC
//

// Function Name: bool CLoopbufIPC::CreateSemaphore(key_t& key)
//
// Comments:
// Create a semaphore and return key value. m_SemId will keep the new semaphore
// value.

bool CLoopbufIPC::CreateSemaphore(key_t& key)
{
	int startValue=1234;
	m_SemId=semget((key_t)startValue,1,0666|IPC_CREAT|IPC_EXCL);
	int retry=0;
	while (m_SemId<0&&retry++<1000)
	{
		startValue++;
		m_SemId=semget((key_t)startValue,1,0666|IPC_CREAT|IPC_EXCL);
	}
	key=startValue;
	if (m_SemId>0)
	{
		union semun {int val;};
		semun sem_union;
		sem_union.val=1;
		if (semctl(m_SemId,0, SETVAL, sem_union)==-1)
		{
			cout<<"Unable to set semaphore value"<<endl;
		}	
	}
	return m_SemId>0; 
}

//
// Function Name: bool CLoopbufIPC::OpenSemaphore(key_t& key)
//
// Comments:
// Open a semaphore and return key value. m_SemId will keep the new semaphore
// value.

bool CLoopbufIPC::OpenSemaphore(key_t& key)
{	
	m_SemId=semget(key,1,0666|IPC_CREAT);
 	return m_SemId>0; 
}

//
// Function Name:bool CLoopbufIPC::
// AcquireSharedMemory(key_t key, unsigned long size)
//
// Comments:
//

bool CLoopbufIPC::AcquireSharedMemory(key_t key, unsigned long size)
{
   //  Use the 0666|IPC_CREAT makes CTRL-C works for the simple test program that does not clean up the 
   // the shared memory resource.
   // int flag= m_bOwner? 0666|IPC_CREAT|IPC_EXCL:0666|IPC_CREAT;
	int flag= 0666|IPC_CREAT;
	m_ShmId=shmget(key,size,flag);
	if (m_ShmId==-1)return false;
	m_pSharedBuffer=(PSHARED_BUFFER)shmat(m_ShmId,(void*)0,0);
	if ((void*)m_pSharedBuffer==(void*)-1)
	{
		return false;
	}
	return true;
}


//
// Function Name:bool CLoopbufIPC::Write(char* buffer, int size)
//
// Comments:
//
//  Write data to the loopbuffer
//
bool CLoopbufIPC::Write(char* data, int datasize)
{
	if( !data || datasize <= 0)	return false;

	//
	// If loop buffer is full, return false
	//
	NOTIFYBUFFER& loop_buffer=m_pSharedBuffer->notify_buffer;

	unsigned long dataFieldSize=(datasize + 3)& ~3;
	unsigned long totalDataSize =  sizeof(unsigned long)+dataFieldSize;

 
	unsigned long CurrentWriteOffset=0;
	{
		AtomLock atomLock(m_SemId);
		if (loop_buffer.UnReadDataAvail+totalDataSize>loop_buffer.TotalSize)
		{
			return false;
		}

		//
		// Claim the write index and UnReadDataAvail at this point
		//
		CurrentWriteOffset=loop_buffer.WIndex;
		loop_buffer.UnReadDataAvail+=totalDataSize;
		
		loop_buffer.WIndex=(loop_buffer.WIndex+totalDataSize)%loop_buffer.TotalSize;
	}

 	
	//
	// Copy the data to the loop buffer
	//
 	unsigned long* pSizeField = (unsigned long*)( loop_buffer.buffer + CurrentWriteOffset );
 	//
	// Note, the *pSizeField must be 0 because its initial value is 0 and the 
	// entire data block is reset to 0 by the read function after the data 
	// block is read. Therefore, an available data block must have the size 
	// filed of 0. We can add debug function here. such as  ASSERT( *pSizeField == 0 );

	unsigned long DataWriteOffset=  (CurrentWriteOffset+sizeof(unsigned long))%loop_buffer.TotalSize;
 	if( DataWriteOffset + dataFieldSize > loop_buffer.TotalSize) 
	{
		unsigned long first_chunk_size = loop_buffer.TotalSize - DataWriteOffset;
		memcpy( loop_buffer.buffer + DataWriteOffset, data, first_chunk_size );
		memcpy( loop_buffer.buffer, data + first_chunk_size, dataFieldSize - first_chunk_size );
	}
	else
	{
		memcpy( loop_buffer.buffer + DataWriteOffset, data, dataFieldSize );
	}

	//
	// Claim the data size field with the data lengh
	//
	*pSizeField = dataFieldSize;
	return true;
}


//
// Function Name:bool CLoopbufIPC::Read(vector<char>&)
//
// Comments:
//
//  Read data from the loopbuffer
//
bool CLoopbufIPC::Read(vector<char>& retBuffer)
{
	NOTIFYBUFFER& loop_buffer=m_pSharedBuffer->notify_buffer;
	{
		AtomLock atomLock(m_SemId);
		if (loop_buffer.UnReadDataAvail==0) return false;
	}

	unsigned long entry_size = *(unsigned long*)(loop_buffer.buffer + loop_buffer.RIndex);
	if (!entry_size)
	{
		//
		// The write operation for this entry is not ready, return 0 bytes
		// to notify caller
		//
		retBuffer.resize(0);
		return true;
	}

	//
	// Clean up this entry
	//
	*(unsigned long*)(loop_buffer.buffer + loop_buffer.RIndex) = 0;

	// Copy the  data to a vector
	loop_buffer.RIndex = (loop_buffer.RIndex + sizeof(entry_size)) % loop_buffer.TotalSize;

	retBuffer.resize(entry_size);
	char* start = loop_buffer.buffer + loop_buffer.RIndex;
	char* end = loop_buffer.buffer + loop_buffer.RIndex + entry_size;

	if(end > loop_buffer.buffer + loop_buffer.TotalSize)
	{
		int remaining = loop_buffer.TotalSize - loop_buffer.RIndex;

		std::copy(start, loop_buffer.buffer + loop_buffer.TotalSize, retBuffer.begin());
		std::fill(start, loop_buffer.buffer + loop_buffer.TotalSize, 0);
		std::copy(loop_buffer.buffer, loop_buffer.buffer + entry_size - remaining, 	retBuffer.begin() + remaining);
		std::fill(loop_buffer.buffer, loop_buffer.buffer + entry_size - remaining,  0);
	}
	else
	{
		std::copy(start, end, retBuffer.begin());
		std::fill(start, end, 0);
	}

	// Advance the read index and update the UnReadDataAvail
	loop_buffer.RIndex = (loop_buffer.RIndex + entry_size) % loop_buffer.TotalSize;
	{
		AtomLock atomLock(m_SemId);
		loop_buffer.UnReadDataAvail-=(entry_size+sizeof(unsigned long));
	}
 	return true;
}
}
}