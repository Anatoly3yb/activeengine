#ifndef GRADIENT_EDITOR_PLUGIN_H
#define GRADIENT_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/gui/gradient_edit.h"

class GradientEditor : public GradientEdit {
	GDCLASS(GradientEditor, GradientEdit);

	bool editing;
	Ref<Gradient> gradient;

	void _gradient_changed();
	void _ramp_changed();

protected:
	static void _bind_methods();

public:
	virtual Size2 get_minimum_size() const;
	void set_gradient(const Ref<Gradient> &p_gradient);
	GradientEditor();
};

class EditorInspectorPluginGradient : public EditorInspectorPlugin {
	GDCLASS(EditorInspectorPluginGradient, EditorInspectorPlugin);

public:
	virtual bool can_handle(Object *p_object);
	virtual void parse_begin(Object *p_object);
};

class GradientEditorPlugin : public EditorPlugin {
	GDCLASS(GradientEditorPlugin, EditorPlugin);

public:
	virtual String get_name() const { return "ColorRamp"; }

	GradientEditorPlugin(EditorNode *p_node);
};

#endif // GRADIENT_EDITOR_PLUGIN_H
