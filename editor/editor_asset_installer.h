#ifndef EDITOR_ASSET_INSTALLER_H
#define EDITOR_ASSET_INSTALLER_H

#include "scene/gui/dialogs.h"
#include "scene/gui/tree.h"
class EditorAssetInstaller : public ConfirmationDialog {
	GDCLASS(EditorAssetInstaller, ConfirmationDialog);

	Tree *tree;
	Label *asset_contents;
	String package_path;
	String asset_name;
	AcceptDialog *error;
	Map<String, TreeItem *> status_map;
	bool updating;
	void _update_subitems(TreeItem *p_item, bool p_check, bool p_first = false);
	void _uncheck_parent(TreeItem *p_item);
	void _item_edited();
	virtual void ok_pressed();

protected:
	static void _bind_methods();

public:
	void open(const String &p_path, int p_depth = 0);

	void set_asset_name(const String &p_asset_name);
	String get_asset_name() const;

	EditorAssetInstaller();
};

#endif // EDITOR_ASSET_INSTALLER_H
