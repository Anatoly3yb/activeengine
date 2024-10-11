#ifndef PACKED_SCENE_EDITOR_PLUGIN_H
#define PACKED_SCENE_EDITOR_PLUGIN_H

#include "editor/editor_inspector.h"
#include "editor/editor_plugin.h"
#include "scene/gui/box_container.h"

class PackedSceneEditor : public VBoxContainer {
	GDCLASS(PackedSceneEditor, VBoxContainer);

	Ref<PackedScene> packed_scene;
	Button *open_scene_button;

	void _on_open_scene_pressed();

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	PackedSceneEditor(Ref<PackedScene> &p_packed_scene);
};

class EditorInspectorPluginPackedScene : public EditorInspectorPlugin {
	GDCLASS(EditorInspectorPluginPackedScene, EditorInspectorPlugin);

public:
	virtual bool can_handle(Object *p_object);
	virtual void parse_begin(Object *p_object);
};

class PackedSceneEditorPlugin : public EditorPlugin {
	GDCLASS(PackedSceneEditorPlugin, EditorPlugin);

public:
	PackedSceneEditorPlugin(EditorNode *p_editor);
};

#endif // PACKED_SCENE_EDITOR_PLUGIN_H
