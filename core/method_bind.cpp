// object.h needs to be the first include *before* method_bind.h
// FIXME: Find out why and fix potential cyclical dependencies.
#include "core/object.h"

#include "method_bind.h"

PropertyInfo MethodBind::get_argument_info(int p_argument) const {
	ERR_FAIL_INDEX_V(p_argument, get_argument_count(), PropertyInfo());

	PropertyInfo info = _gen_argument_type_info(p_argument);
#ifdef DEBUG_METHODS_ENABLED
	info.name = p_argument < arg_names.size() ? String(arg_names[p_argument]) : String("arg" + itos(p_argument));
#endif
	return info;
}

PropertyInfo MethodBind::get_return_info() const {
	return _gen_argument_type_info(-1);
}

void MethodBind::_set_const(bool p_const) {
	_const = p_const;
}

void MethodBind::_set_returns(bool p_returns) {
	_returns = p_returns;
}

StringName MethodBind::get_name() const {
	return name;
}
void MethodBind::set_name(const StringName &p_name) {
	name = p_name;
}

#ifdef DEBUG_METHODS_ENABLED
void MethodBind::set_argument_names(const Vector<StringName> &p_names) {
	arg_names = p_names;
}
Vector<StringName> MethodBind::get_argument_names() const {
	return arg_names;
}

#endif

void MethodBind::set_default_arguments(const Vector<Variant> &p_defargs) {
	default_arguments = p_defargs;
	default_argument_count = default_arguments.size();
}

void MethodBind::_generate_argument_types(int p_count) {
	set_argument_count(p_count);

	Variant::Type *argt = memnew_arr(Variant::Type, p_count + 1);
	argt[0] = _gen_argument_type(-1); // return type

	for (int i = 0; i < p_count; i++) {
		argt[i + 1] = _gen_argument_type(i);
	}

	argument_types = argt;
}

MethodBind::MethodBind() {
	static int last_id = 0;
	method_id = last_id++;
	hint_flags = METHOD_FLAGS_DEFAULT;
	argument_count = 0;
	default_argument_count = 0;
	argument_types = nullptr;
	_const = false;
	_returns = false;
}

MethodBind::~MethodBind() {
	if (argument_types) {
		memdelete_arr(argument_types);
	}
}
