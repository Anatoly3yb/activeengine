#ifndef SELF_LIST_H
#define SELF_LIST_H

#include "core/error_macros.h"
#include "core/typedefs.h"

template <class T>
class SelfList {
public:
	class List {
		SelfList<T> *_first;
		SelfList<T> *_last;

	public:
		void add(SelfList<T> *p_elem) {
			ERR_FAIL_COND(p_elem->_root);

			p_elem->_root = this;
			p_elem->_next = _first;
			p_elem->_prev = nullptr;

			if (_first) {
				_first->_prev = p_elem;

			} else {
				_last = p_elem;
			}

			_first = p_elem;
		}

		void add_last(SelfList<T> *p_elem) {
			ERR_FAIL_COND(p_elem->_root);

			p_elem->_root = this;
			p_elem->_next = nullptr;
			p_elem->_prev = _last;

			if (_last) {
				_last->_next = p_elem;

			} else {
				_first = p_elem;
			}

			_last = p_elem;
		}

		void remove(SelfList<T> *p_elem) {
			ERR_FAIL_COND(p_elem->_root != this);
			if (p_elem->_next) {
				p_elem->_next->_prev = p_elem->_prev;
			}

			if (p_elem->_prev) {
				p_elem->_prev->_next = p_elem->_next;
			}

			if (_first == p_elem) {
				_first = p_elem->_next;
			}

			if (_last == p_elem) {
				_last = p_elem->_prev;
			}

			p_elem->_next = nullptr;
			p_elem->_prev = nullptr;
			p_elem->_root = nullptr;
		}

		_FORCE_INLINE_ SelfList<T> *first() { return _first; }
		_FORCE_INLINE_ const SelfList<T> *first() const { return _first; }
		_FORCE_INLINE_ List() {
			_first = nullptr;
			_last = nullptr;
		}
		_FORCE_INLINE_ ~List() { ERR_FAIL_COND(_first != nullptr); }
	};

private:
	List *_root;
	T *_self;
	SelfList<T> *_next;
	SelfList<T> *_prev;

public:
	_FORCE_INLINE_ bool in_list() const { return _root; }
	_FORCE_INLINE_ void remove_from_list() {
		if (_root) {
			_root->remove(this);
		}
	}
	_FORCE_INLINE_ SelfList<T> *next() { return _next; }
	_FORCE_INLINE_ SelfList<T> *prev() { return _prev; }
	_FORCE_INLINE_ const SelfList<T> *next() const { return _next; }
	_FORCE_INLINE_ const SelfList<T> *prev() const { return _prev; }
	_FORCE_INLINE_ T *self() const { return _self; }

	_FORCE_INLINE_ SelfList(T *p_self) {
		_self = p_self;
		_next = nullptr;
		_prev = nullptr;
		_root = nullptr;
	}

	_FORCE_INLINE_ ~SelfList() {
		if (_root) {
			_root->remove(this);
		}
	}
};

#endif // SELF_LIST_H
