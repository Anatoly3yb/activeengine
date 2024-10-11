#ifndef REPARENT_DIALOG_H
#define REPARENT_DIALOG_H

#include "editor/scene_tree_editor.h"
#include "scene/gui/button.h"
#include "scene/gui/check_box.h"
#include "scene/gui/check_button.h"
#include "scene/gui/dialogs.h"
#include "scene/gui/line_edit.h"
/**
@author Juan Linietsky <reduzio@gmail.com>
*/
class ReparentDialog : public ConfirmationDialog {
	GDCLASS(ReparentDialog, ConfirmationDialog);

	SceneTreeEditor *tree;
	CheckBox *keep_transform;

	void _reparent();
	void _cancel();

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void set_current(const Set<Node *> &p_selection);

	ReparentDialog();
	~ReparentDialog();
};

#endif // REPARENT_DIALOG_H
