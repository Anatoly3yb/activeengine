#include "reparent_dialog.h"

#include "core/print_string.h"
#include "scene/gui/box_container.h"
#include "scene/gui/label.h"

void ReparentDialog::_notification(int p_what) {
	if (p_what == NOTIFICATION_ENTER_TREE) {
		connect("confirmed", this, "_reparent");
	}

	if (p_what == NOTIFICATION_EXIT_TREE) {
		disconnect("confirmed", this, "_reparent");
	}

	if (p_what == NOTIFICATION_DRAW) {
		//RID ci = get_canvas_item();
		//get_stylebox("panel","PopupMenu")->draw(ci,Rect2(Point2(),get_size()));
	}
}

void ReparentDialog::_cancel() {
	hide();
}
void ReparentDialog::_reparent() {
	if (tree->get_selected()) {
		emit_signal("reparent", tree->get_selected()->get_path(), keep_transform->is_pressed());
		hide();
	}
}

void ReparentDialog::set_current(const Set<Node *> &p_selection) {
	tree->set_marked(p_selection, false, false);
	//tree->set_selected(p_node->get_parent());
}

void ReparentDialog::_bind_methods() {
	ClassDB::bind_method("_reparent", &ReparentDialog::_reparent);
	ClassDB::bind_method("_cancel", &ReparentDialog::_cancel);

	ADD_SIGNAL(MethodInfo("reparent", PropertyInfo(Variant::NODE_PATH, "path"), PropertyInfo(Variant::BOOL, "keep_global_xform")));
}

ReparentDialog::ReparentDialog() {
	set_title(TTR("Reparent Node"));

	VBoxContainer *vbc = memnew(VBoxContainer);
	add_child(vbc);
	//set_child_rect(vbc);

	tree = memnew(SceneTreeEditor(false));
	tree->set_show_enabled_subscene(true);

	vbc->add_margin_child(TTR("Reparent Location (Select new Parent):"), tree, true);

	tree->get_scene_tree()->connect("item_activated", this, "_reparent");

	//Label *label = memnew( Label );
	//label->set_position( Point2( 15,8) );
	//label->set_text("Reparent Location (Select new Parent):");

	keep_transform = memnew(CheckBox);
	keep_transform->set_text(TTR("Keep Global Transform"));
	keep_transform->set_pressed(true);
	vbc->add_child(keep_transform);

	//vbc->add_margin_child("Options:",node_only);

	//cancel->connect("pressed", this,"_cancel");

	get_ok()->set_text(TTR("Reparent"));
}

ReparentDialog::~ReparentDialog() {
}
