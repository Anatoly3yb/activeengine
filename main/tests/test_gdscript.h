#ifndef TEST_GDSCRIPT_H
#define TEST_GDSCRIPT_H

#include "core/os/main_loop.h"

namespace TestGDScript {

enum TestType {
	TEST_TOKENIZER,
	TEST_PARSER,
	TEST_COMPILER,
	TEST_BYTECODE,
};

MainLoop *test(TestType p_type);
} // namespace TestGDScript

#endif // TEST_GDSCRIPT_H
