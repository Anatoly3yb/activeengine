#ifndef THREADED_CALLABLE_QUEUE_H
#define THREADED_CALLABLE_QUEUE_H

#include "core/local_vector.h"
#include "core/ordered_hash_map.h"
#include "core/os/mutex.h"
#include "core/os/semaphore.h"
#include "core/os/thread.h"

#include <functional>

template <class K>
class ThreadedCallableQueue {
public:
	using Job = std::function<void()>;

private:
	bool exit;
	Thread thread;
	BinaryMutex mutex;
	Semaphore sem;
	OrderedHashMap<K, Job> queue;

	static void _thread_func(void *p_user_data);

public:
	void enqueue(K p_key, Job p_job);
	void cancel(K p_key);

	ThreadedCallableQueue();
	~ThreadedCallableQueue();
};

template <class K>
void ThreadedCallableQueue<K>::_thread_func(void *p_user_data) {
	ThreadedCallableQueue *self = static_cast<ThreadedCallableQueue *>(p_user_data);

	while (true) {
		self->sem.wait();
		self->mutex.lock();
		if (self->exit) {
			self->mutex.unlock();
			break;
		}

		typename OrderedHashMap<K, Job>::Element E = self->queue.front();
		// Defense about implementation bugs (excessive posts)
		if (!E) {
			ERR_PRINT("Semaphore unlocked, the queue is empty. Bug?");
			self->mutex.unlock();
			// --- Defense end
		} else {
			LocalVector<Job> jobs;
			jobs.push_back(E.value());
			self->queue.erase(E);
			self->mutex.unlock();

			for (uint32_t i = 0; i < jobs.size(); i++) {
				jobs[i]();
			}
		}
	}

	self->mutex.lock();
	for (typename OrderedHashMap<K, Job>::Element E = self->queue.front(); E; E = E.next()) {
		Job job = E.value();
		job();
	}
	self->mutex.unlock();
}

template <class K>
void ThreadedCallableQueue<K>::enqueue(K p_key, Job p_job) {
	MutexLock lock(mutex);
	ERR_FAIL_COND(exit);
	ERR_FAIL_COND(queue.has(p_key));
	queue.insert(p_key, p_job);
	sem.post();
}

template <class K>
void ThreadedCallableQueue<K>::cancel(K p_key) {
	MutexLock lock(mutex);
	ERR_FAIL_COND(exit);
	if (queue.erase(p_key)) {
		sem.wait();
	}
}

template <class K>
ThreadedCallableQueue<K>::ThreadedCallableQueue() :
		exit(false) {
	thread.start(&_thread_func, this);
}

template <class K>
ThreadedCallableQueue<K>::~ThreadedCallableQueue() {
	exit = true;
	sem.post();
	thread.wait_to_finish();
}

#endif // THREADED_CALLABLE_QUEUE_H
