#ifndef SIMPLE_TYPE_H
#define SIMPLE_TYPE_H

/* Batch of specializations to obtain the actual simple type */

template <class T>
struct GetSimpleTypeT {
	typedef T type_t;
};

template <class T>
struct GetSimpleTypeT<T &> {
	typedef T type_t;
};

template <class T>
struct GetSimpleTypeT<T const> {
	typedef T type_t;
};

#endif // SIMPLE_TYPE_H
