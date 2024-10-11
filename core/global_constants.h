#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H

#include "core/string_name.h"

class GlobalConstants {
public:
	static int get_global_constant_count();
	static StringName get_global_constant_enum(int p_idx);
	static bool get_ignore_value_in_docs(int p_idx);
	static const char *get_global_constant_name(int p_idx);
	static int get_global_constant_value(int p_idx);
};

#endif // GLOBAL_CONSTANTS_H
