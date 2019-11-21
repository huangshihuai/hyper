#pragma once

namespace hyper {
namespace util {
//
// Define a ring buffer class 
//
// The ringbuf can be used in multithreads or multiprocess communication
//

#define THROW_RING_BUF_CREATION_ERROR		0x1000L

typedef struct _NOTIFYBUFFER
{
	unsigned long TotalSize;							// Amount of data currently in buffer
	unsigned long WIndex;							// write count - this increments but is never reset
	unsigned long RIndex;							// read point - this is only changed by sysman
	unsigned long UnReadDataAvail;							// how many entries?  
	char buffer[4];						// Our actual entries, put 4 bytes for the bytes alignment.
} NOTIFYBUFFER;

typedef struct _SHARED_BUFFER
{
	unsigned long		ulSig;			// 0xbeefdead
	unsigned long       atomKey;        // For IPC only
	NOTIFYBUFFER		notify_buffer;

} SHARED_BUFFER, *PSHARED_BUFFER;

class CLoopBufBase
{
public:
	CLoopBufBase();
	virtual ~CLoopBufBase(){}
	inline bool IsValid() const {return m_bValid;}
	virtual bool Write(char* buffer, int size)=0;
	virtual bool Read(vector<char>&)=0;

protected: 
	PSHARED_BUFFER m_pSharedBuffer;
	bool m_bValid;
};
 
class CLoopBufInProcess:public CLoopBufBase
{
public:
	explicit CLoopBufInProcess(int bufferSize);  
	~CLoopBufInProcess();

	bool Write(char* buffer, int size);
	bool Read(vector<char>&);

	class AtomLock
	{
		public:
		explicit AtomLock(sem_t s):m_Sem(s)		{sem_wait(&m_Sem); }
		~AtomLock()		{sem_post(&m_Sem);}
		private:
		sem_t m_Sem;
	};
					
private:

//
// Hide the default consturctor, copy constructor, operator=
//
	CLoopBufInProcess();
	CLoopBufInProcess& operator=(CLoopBufInProcess const&);
	CLoopBufInProcess(CLoopBufInProcess const&);
	CLoopBufInProcess(CLoopBufInProcess &);
	sem_t m_Sem;
};


class CLoopbufIPC:public CLoopBufBase
{
public:
	CLoopbufIPC(unsigned long size, key_t key,bool bshmOwner);
	~CLoopbufIPC();
	bool Write(char* buffer, int size);
	bool Read(vector<char>&);

	class AtomLock
	{
		public:
		explicit AtomLock(int s):m_SemId(s)		
		{
			sembuf sem_b;
			sem_b.sem_num=0;
			sem_b.sem_op=-1;
			sem_b.sem_flg=SEM_UNDO;
			if (semop(m_SemId,&sem_b,1)==-1)
			{
				cout<<"P Semaphore failed"<<endl;
			}
		}
		
		~AtomLock()	
		{
			sembuf sem_b;
			sem_b.sem_num=0;
			sem_b.sem_op=1;
			sem_b.sem_flg=SEM_UNDO;
			if (semop(m_SemId,&sem_b,1)==-1)
			{
				cout<<"V Semaphore failed"<<endl;
			}
		}	 
		private:
		int m_SemId;
	};

protected:

	bool CreateSemaphore(key_t& key);
	bool OpenSemaphore(key_t& key);
	bool AcquireSharedMemory(key_t key, unsigned long size);

private:
	//hide default constructor, operator=, and copy constructor
	CLoopbufIPC();
	CLoopbufIPC& operator=(CLoopbufIPC const&);
	CLoopbufIPC(CLoopbufIPC const &);
	bool m_bOwner;
	int m_SemId;
	int m_ShmId;

	bool m_bShmCreated;
	bool m_bSemCreated;
};

}
}