#ifndef BIT_MAP_EDITOR_PLUGIN_H
#define BIT_MAP_EDITOR_PLUGIN_H

#include "editor/editor_plugin.h"
#include "scene/resources/bit_map.h"

class BitMapEditor : public VBoxContainer {
	GDCLASS(BitMapEditor, VBoxContainer);

	TextureRect *texture_rect = nullptr;
	Label *size_label = nullptr;

public:
	void setup(const Ref<BitMap> &p_bitmap);

	BitMapEditor();
};

class EditorInspectorPluginBitMap : public EditorInspectorPlugin {
	GDCLASS(EditorInspectorPluginBitMap, EditorInspectorPlugin);

public:
	virtual bool can_handle(Object *p_object);
	virtual void parse_begin(Object *p_object);
};

class BitMapEditorPlugin : public EditorPlugin {
	GDCLASS(BitMapEditorPlugin, EditorPlugin);

public:
	BitMapEditorPlugin(EditorNode *p_editor);
};

#endif // BIT_MAP_EDITOR_PLUGIN_H
