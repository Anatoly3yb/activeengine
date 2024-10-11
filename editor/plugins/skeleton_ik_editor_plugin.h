#ifndef SKELETON_IK_EDITOR_PLUGIN_H
#define SKELETON_IK_EDITOR_PLUGIN_H

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"

class SkeletonIK;

class SkeletonIKEditorPlugin : public EditorPlugin {
	GDCLASS(SkeletonIKEditorPlugin, EditorPlugin);

	SkeletonIK *skeleton_ik;

	Button *play_btn;
	EditorNode *editor;

	void _play();

protected:
	static void _bind_methods();

public:
	virtual String get_name() const { return "SkeletonIK"; }
	bool has_main_screen() const { return false; }
	virtual void edit(Object *p_object);
	virtual bool handles(Object *p_object) const;
	virtual void make_visible(bool p_visible);

	SkeletonIKEditorPlugin(EditorNode *p_node);
	~SkeletonIKEditorPlugin();
};

#endif // SKELETON_IK_EDITOR_PLUGIN_H
