#ifndef SHADER_COMPILER_GLES3_H
#define SHADER_COMPILER_GLES3_H

#include "core/pair.h"
#include "servers/visual/shader_language.h"
#include "servers/visual/shader_types.h"
#include "servers/visual_server.h"

class ShaderCompilerGLES3 {
public:
	struct IdentifierActions {
		Map<StringName, Pair<int *, int>> render_mode_values;
		Map<StringName, bool *> render_mode_flags;
		Map<StringName, bool *> usage_flag_pointers;
		Map<StringName, bool *> write_flag_pointers;

		Map<StringName, ShaderLanguage::ShaderNode::Uniform> *uniforms;
	};

	struct GeneratedCode {
		Vector<CharString> defines;
		Vector<StringName> texture_uniforms;
		Vector<ShaderLanguage::DataType> texture_types;
		Vector<ShaderLanguage::ShaderNode::Uniform::Hint> texture_hints;

		Vector<uint32_t> uniform_offsets;
		uint32_t uniform_total_size;
		String uniforms;
		String vertex_global;
		String vertex;
		String fragment_global;
		String fragment;
		String light;

		bool uses_fragment_time;
		bool uses_vertex_time;
	};

private:
	ShaderLanguage parser;

	struct DefaultIdentifierActions {
		Map<StringName, String> renames;
		Map<StringName, String> render_mode_defines;
		Map<StringName, String> usage_defines;
	};

	void _dump_function_deps(const ShaderLanguage::ShaderNode *p_node, const StringName &p_for_func, const Map<StringName, String> &p_func_code, String &r_to_add, Set<StringName> &added);
	String _dump_node_code(const ShaderLanguage::Node *p_node, int p_level, GeneratedCode &r_gen_code, IdentifierActions &p_actions, const DefaultIdentifierActions &p_default_actions, bool p_assigning, bool p_use_scope = true);

	const ShaderLanguage::ShaderNode *shader;
	const ShaderLanguage::FunctionNode *function;
	StringName current_func_name;
	StringName vertex_name;
	StringName fragment_name;
	StringName light_name;
	StringName time_name;

	Set<StringName> used_name_defines;
	Set<StringName> used_flag_pointers;
	Set<StringName> used_rmode_defines;
	Set<StringName> internal_functions;
	Set<StringName> fragment_varyings;

	DefaultIdentifierActions actions[VS::SHADER_MAX];

public:
	Error compile(VS::ShaderMode p_mode, const String &p_code, IdentifierActions *p_actions, const String &p_path, GeneratedCode &r_gen_code);

	ShaderCompilerGLES3();
};

#endif // SHADER_COMPILER_GLES3_H
