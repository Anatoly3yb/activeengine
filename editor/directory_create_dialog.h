#ifndef DIRECTORY_CREATE_DIALOG_H
#define DIRECTORY_CREATE_DIALOG_H

#include "scene/gui/dialogs.h"

class Label;
class LineEdit;
class PanelContainer;

class DirectoryCreateDialog : public ConfirmationDialog {
	GDCLASS(DirectoryCreateDialog, ConfirmationDialog);

	String base_dir;

	Label *label = nullptr;
	LineEdit *dir_path = nullptr;

	PanelContainer *status_panel = nullptr;
	Label *status_label = nullptr;

	String _validate_path(const String &p_path) const;

	void _on_dir_path_changed(const String &p_text);

protected:
	static void _bind_methods();
	void _notification(int p_what);

	virtual void ok_pressed();
	virtual void _post_popup();

public:
	void config(const String &p_base_dir);

	DirectoryCreateDialog();
};

#endif // DIRECTORY_CREATE_DIALOG_H
