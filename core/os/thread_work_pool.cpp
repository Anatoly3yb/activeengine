#include "thread_work_pool.h"

#include "core/os/os.h"

void ThreadWorkPool::_thread_function(void *p_user) {
	ThreadData *thread = static_cast<ThreadData *>(p_user);
	while (true) {
		thread->start.wait();
		if (thread->exit.load()) {
			break;
		}
		thread->work->work();
		thread->completed.post();
	}
}

void ThreadWorkPool::init(int p_thread_count) {
	ERR_FAIL_COND(threads != nullptr);
	if (p_thread_count < 0) {
		p_thread_count = OS::get_singleton()->get_default_thread_pool_size();
	}

	thread_count = p_thread_count;
	threads = memnew_arr(ThreadData, thread_count);

	for (uint32_t i = 0; i < thread_count; i++) {
		threads[i].exit.store(false);
		threads[i].thread.start(&ThreadWorkPool::_thread_function, &threads[i]);
	}
}

void ThreadWorkPool::finish() {
	if (threads == nullptr) {
		return;
	}

	for (uint32_t i = 0; i < thread_count; i++) {
		threads[i].exit.store(true);
		threads[i].start.post();
	}
	for (uint32_t i = 0; i < thread_count; i++) {
		threads[i].thread.wait_to_finish();
	}

	memdelete_arr(threads);
	threads = nullptr;
}

ThreadWorkPool::~ThreadWorkPool() {
	finish();
}
