#ifndef EDITOR_RUN_NATIVE_H
#define EDITOR_RUN_NATIVE_H

#include "scene/gui/box_container.h"
#include "scene/gui/dialogs.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/rich_text_label.h"

class EditorRunNative : public HBoxContainer {
	GDCLASS(EditorRunNative, HBoxContainer);

	RichTextLabel *result_dialog_log;
	AcceptDialog *result_dialog;

	Map<int, MenuButton *> menus;
	bool first;
	bool deploy_dumb;
	bool deploy_debug_remote;
	bool debug_collisions;
	bool debug_navigation;
	bool debug_shader_fallbacks;

	int resume_idx;
	int resume_platform;

	void _run_native(int p_idx, int p_platform);

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	void set_deploy_dumb(bool p_enabled);
	bool is_deploy_dumb_enabled() const;

	void set_deploy_debug_remote(bool p_enabled);
	bool is_deploy_debug_remote_enabled() const;

	void set_debug_collisions(bool p_debug);
	bool get_debug_collisions() const;

	void set_debug_navigation(bool p_debug);
	bool get_debug_navigation() const;

	void set_debug_shader_fallbacks(bool p_debug);
	bool get_debug_shader_fallbacks() const;

	void resume_run_native();

	EditorRunNative();
};

#endif // EDITOR_RUN_NATIVE_H
