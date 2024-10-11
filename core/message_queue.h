#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "core/local_vector.h"
#include "core/object.h"
#include "core/os/thread_safe.h"

class MessageQueue {
	_THREAD_SAFE_CLASS_

	enum {
		TYPE_CALL,
		TYPE_NOTIFICATION,
		TYPE_SET,
		FLAG_SHOW_ERROR = 1 << 14,
		FLAG_MASK = FLAG_SHOW_ERROR - 1

	};

	struct Message {
		ObjectID instance_id;
		StringName target;
		int16_t type;
		union {
			int16_t notification;
			int16_t args;
		};
	};

	struct Buffer {
		LocalVector<uint8_t> data;
		uint64_t end = 0;
	};

	Buffer buffers[2];
	int read_buffer = 0;
	int write_buffer = 1;
	uint64_t max_allowed_buffer_size = 0;

	struct BufferSizeMonitor {
		uint32_t max_size = 0;
		uint32_t flush_count = 0;

		// Only used for performance statistics.
		uint32_t max_size_overall = 0;
	} _buffer_size_monitor;

	void _call_function(Object *p_target, const StringName &p_func, const Variant *p_args, int p_argcount, bool p_show_error);
	void _update_buffer_monitor();

	static MessageQueue *singleton;

	bool flushing;

public:
	static MessageQueue *get_singleton();

	Error push_call(ObjectID p_id, const StringName &p_method, const Variant **p_args, int p_argcount, bool p_show_error = false);
	Error push_call(ObjectID p_id, const StringName &p_method, VARIANT_ARG_LIST);
	Error push_notification(ObjectID p_id, int p_notification);
	Error push_set(ObjectID p_id, const StringName &p_prop, const Variant &p_value);

	Error push_call(Object *p_object, const StringName &p_method, VARIANT_ARG_LIST);
	Error push_notification(Object *p_object, int p_notification);
	Error push_set(Object *p_object, const StringName &p_prop, const Variant &p_value);

	void statistics();
	void flush();

	bool is_flushing() const;

	int get_max_buffer_usage() const;
	int get_current_buffer_usage() const;

	MessageQueue();
	~MessageQueue();
};

#endif // MESSAGE_QUEUE_H
