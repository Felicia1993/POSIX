#include <pthread.h>
#include "errors.h"
#include <time.h>

typedef struct my_struct_tag{
	pthread_mutex_t mutex;/*Protects access to value*/
	pthread_cond_t cond;/*Signals change to value*/
	int value;/*Access protected by mutex*/
}my_struct_t;

my_struct_t data={
	PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, 0};

int hibernation = 1;//Default to 1 second

/*
Thread start routine. It will set the main thread's predicate and signal the condition variable.
*/
/*
wait_thread睡眠一段时间以允许主线程在被唤醒之前条件变量等待操作，设置共享的谓词(data.value),然后发信号给条件变量。Wait_thread线程等待的时间由hibernation
变量控制，默认是1秒
*/
void* wait_thread(void *arg){
	int status;
	sleep(hibernation);
	status = pthread_mutex_lock(&data.mutex);
	if(status != 0)
		errno_abort(status, "Lock mutex");

	data.value = 1;
	status = pthread_cond_signal(&data->cond, NULL);
	if(status != 0)
		err_abort(status, "signal condition");
	status = pthread_mutex_unlock(&data.mutex);
	if(status != 0)
		err_abort(status, "Unlock mutex");
	return NULL;
	
}

int main(){
	int status;
	pthread_t wait_thread_id;
	struct timespec timeout;
	
	return 0;
}
