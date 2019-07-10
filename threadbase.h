#ifndef THREADBASE_H_
#define THREADBASE_H_

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <iostream>
#include <cstring>

class Semaphore {
protected:
	sem_t*					m_handle;
public:
	Semaphore() {
		m_handle = new sem_t();
		sem_init(m_handle, 0, 1);
	}
	virtual ~Semaphore() {
		if(m_handle)
		{
			sem_destroy(m_handle);
			delete m_handle;
			m_handle =NULL;
		}
	}

	bool Lock() {
		sem_wait(m_handle);
		return true;
	}
	bool UnLock() {
		sem_post(m_handle);
		return true;
	}
	bool IsLocked( ) {
		int sval = -1;
		sem_getvalue(m_handle, &sval);
		return (sval==0);
	}
};

class ThreadBase {
private:
	pthread_t 			m_ThreadHandle;
	/*	Description		- Handle the POSIX thread's attributes.
	 */
	pthread_attr_t     	m_ThreadAttribute;
	/*	Description		- Storing the thread's name.
	 */
	char 				m_ThreadName[64];
	/*	Description		- Helper function to start the thread.
	 */
	static
	void *Dispatch(void *arg) {
		ThreadBase *pThread(static_cast<ThreadBase *>(arg));
		std::cout<<"in "<<pThread->GetThreadName()<< " Dispatch \n";
		pThread->Run();
		return NULL;
	}

public:
	/*	Description		- Default constructor.
	 */
	ThreadBase() : m_ThreadHandle (0) {
		m_ThreadName[0] = 0 ;
		pthread_attr_init(&m_ThreadAttribute);
	}
	virtual ~ThreadBase() {
		pthread_attr_destroy(&m_ThreadAttribute);
	}
	char* GetThreadName() {
		return m_ThreadName;
	}

	bool Start(const char* thread_name) {
		int err = pthread_create(&m_ThreadHandle, &m_ThreadAttribute, &Dispatch, this);
		
		// err will give 
		if (err) {
			std::cerr << "BaseThread: failed to Start." << std::endl;
			return false;
		}
		//Give it a name 
		strcpy(m_ThreadName,thread_name);
		//std::cout<<"in "<<this->GetThreadName()<< " Start \n";
		return true;
	}

	virtual void OnRun() {
		std::cout << GetThreadName() <<" says: Hello" << std::endl;
	}

	virtual void Run() {
		OnRun();

	}

	void Join()
	{
		//std::cout<<"join hi ";
		void * ret;
		if(pthread_join(m_ThreadHandle, &ret)!=0){
			std::cout<<"Cannot join threads, Error \n";
		}
		//std::cout<<"join bye ";
	}
};

#endif /* THREADBASE_H_ */
