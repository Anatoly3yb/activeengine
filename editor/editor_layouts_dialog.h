#ifndef EDITOR_LAYOUTS_DIALOG_H
#define EDITOR_LAYOUTS_DIALOG_H

#include "scene/gui/dialogs.h"

class LineEdit;
class ItemList;

class EditorLayoutsDialog : public ConfirmationDialog {
	GDCLASS(EditorLayoutsDialog, ConfirmationDialog);

	LineEdit *name;
	ItemList *layout_names;
	VBoxContainer *makevb;

	void _line_gui_input(const Ref<InputEvent> &p_event);

protected:
	static void _bind_methods();
	virtual void ok_pressed();
	virtual void _post_popup();

public:
	EditorLayoutsDialog();

	void set_name_line_enabled(bool p_enabled);
};

#endif // EDITOR_LAYOUTS_DIALOG_H
