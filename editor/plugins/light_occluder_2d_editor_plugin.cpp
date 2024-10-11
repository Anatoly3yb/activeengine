#include "light_occluder_2d_editor_plugin.h"

Ref<OccluderPolygon2D> LightOccluder2DEditor::_ensure_occluder() const {
	Ref<OccluderPolygon2D> occluder = node->get_occluder_polygon();
	if (!occluder.is_valid()) {
		occluder = Ref<OccluderPolygon2D>(memnew(OccluderPolygon2D));
		node->set_occluder_polygon(occluder);
	}
	return occluder;
}

Node2D *LightOccluder2DEditor::_get_node() const {
	return node;
}

void LightOccluder2DEditor::_set_node(Node *p_polygon) {
	node = Object::cast_to<LightOccluder2D>(p_polygon);
}

bool LightOccluder2DEditor::_is_line() const {
	Ref<OccluderPolygon2D> occluder = node->get_occluder_polygon();
	if (occluder.is_valid()) {
		return !occluder->is_closed();
	} else {
		return false;
	}
}

int LightOccluder2DEditor::_get_polygon_count() const {
	Ref<OccluderPolygon2D> occluder = node->get_occluder_polygon();
	if (occluder.is_valid()) {
		return occluder->get_polygon().size();
	} else {
		return 0;
	}
}

Variant LightOccluder2DEditor::_get_polygon(int p_idx) const {
	Ref<OccluderPolygon2D> occluder = node->get_occluder_polygon();
	if (occluder.is_valid()) {
		return occluder->get_polygon();
	} else {
		return Variant(Vector<Vector2>());
	}
}

void LightOccluder2DEditor::_set_polygon(int p_idx, const Variant &p_polygon) const {
	Ref<OccluderPolygon2D> occluder = _ensure_occluder();
	occluder->set_polygon(p_polygon);
}

void LightOccluder2DEditor::_action_set_polygon(int p_idx, const Variant &p_previous, const Variant &p_polygon) {
	Ref<OccluderPolygon2D> occluder = _ensure_occluder();
	undo_redo->add_do_method(occluder.ptr(), "set_polygon", p_polygon);
	undo_redo->add_undo_method(occluder.ptr(), "set_polygon", p_previous);
}

bool LightOccluder2DEditor::_has_resource() const {
	return node && node->get_occluder_polygon().is_valid();
}

void LightOccluder2DEditor::_create_resource() {
	if (!node) {
		return;
	}

	undo_redo->create_action(TTR("Create Occluder Polygon"));
	undo_redo->add_do_method(node, "set_occluder_polygon", Ref<OccluderPolygon2D>(memnew(OccluderPolygon2D)));
	undo_redo->add_undo_method(node, "set_occluder_polygon", Variant(REF()));
	undo_redo->commit_action();

	_menu_option(MODE_CREATE);
}

LightOccluder2DEditor::LightOccluder2DEditor(EditorNode *p_editor) :
		AbstractPolygon2DEditor(p_editor) {
	node = nullptr;
}

LightOccluder2DEditorPlugin::LightOccluder2DEditorPlugin(EditorNode *p_node) :
		AbstractPolygon2DEditorPlugin(p_node, memnew(LightOccluder2DEditor(p_node)), "LightOccluder2D") {
}
