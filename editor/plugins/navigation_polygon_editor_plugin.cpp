#include "navigation_polygon_editor_plugin.h"

Ref<NavigationPolygon> NavigationPolygonEditor::_ensure_navpoly() const {
	Ref<NavigationPolygon> navpoly = node->get_navigation_polygon();
	if (!navpoly.is_valid()) {
		navpoly = Ref<NavigationPolygon>(memnew(NavigationPolygon));
		node->set_navigation_polygon(navpoly);
	}
	return navpoly;
}

Node2D *NavigationPolygonEditor::_get_node() const {
	return node;
}

void NavigationPolygonEditor::_set_node(Node *p_polygon) {
	node = Object::cast_to<NavigationPolygonInstance>(p_polygon);
}

int NavigationPolygonEditor::_get_polygon_count() const {
	Ref<NavigationPolygon> navpoly = node->get_navigation_polygon();
	if (navpoly.is_valid()) {
		return navpoly->get_outline_count();
	} else {
		return 0;
	}
}

Variant NavigationPolygonEditor::_get_polygon(int p_idx) const {
	Ref<NavigationPolygon> navpoly = node->get_navigation_polygon();
	if (navpoly.is_valid()) {
		return navpoly->get_outline(p_idx);
	} else {
		return Variant(Vector<Vector2>());
	}
}

void NavigationPolygonEditor::_set_polygon(int p_idx, const Variant &p_polygon) const {
	Ref<NavigationPolygon> navpoly = _ensure_navpoly();
	navpoly->set_outline(p_idx, p_polygon);
	navpoly->make_polygons_from_outlines();
}

void NavigationPolygonEditor::_action_add_polygon(const Variant &p_polygon) {
	Ref<NavigationPolygon> navpoly = _ensure_navpoly();
	undo_redo->add_do_method(navpoly.ptr(), "add_outline", p_polygon);
	undo_redo->add_undo_method(navpoly.ptr(), "remove_outline", navpoly->get_outline_count());
	undo_redo->add_do_method(navpoly.ptr(), "make_polygons_from_outlines");
	undo_redo->add_undo_method(navpoly.ptr(), "make_polygons_from_outlines");
}

void NavigationPolygonEditor::_action_remove_polygon(int p_idx) {
	Ref<NavigationPolygon> navpoly = _ensure_navpoly();
	undo_redo->add_do_method(navpoly.ptr(), "remove_outline", p_idx);
	undo_redo->add_undo_method(navpoly.ptr(), "add_outline_at_index", navpoly->get_outline(p_idx), p_idx);
	undo_redo->add_do_method(navpoly.ptr(), "make_polygons_from_outlines");
	undo_redo->add_undo_method(navpoly.ptr(), "make_polygons_from_outlines");
}

void NavigationPolygonEditor::_action_set_polygon(int p_idx, const Variant &p_previous, const Variant &p_polygon) {
	Ref<NavigationPolygon> navpoly = _ensure_navpoly();
	undo_redo->add_do_method(navpoly.ptr(), "set_outline", p_idx, p_polygon);
	undo_redo->add_undo_method(navpoly.ptr(), "set_outline", p_idx, p_previous);
	undo_redo->add_do_method(navpoly.ptr(), "make_polygons_from_outlines");
	undo_redo->add_undo_method(navpoly.ptr(), "make_polygons_from_outlines");
}

bool NavigationPolygonEditor::_has_resource() const {
	return node && node->get_navigation_polygon().is_valid();
}

void NavigationPolygonEditor::_create_resource() {
	if (!node) {
		return;
	}

	undo_redo->create_action(TTR("Create Navigation Polygon"));
	undo_redo->add_do_method(node, "set_navigation_polygon", Ref<NavigationPolygon>(memnew(NavigationPolygon)));
	undo_redo->add_undo_method(node, "set_navigation_polygon", Variant(REF()));
	undo_redo->commit_action();

	_menu_option(MODE_CREATE);
}

NavigationPolygonEditor::NavigationPolygonEditor(EditorNode *p_editor) :
		AbstractPolygon2DEditor(p_editor) {
	node = nullptr;
}

NavigationPolygonEditorPlugin::NavigationPolygonEditorPlugin(EditorNode *p_node) :
		AbstractPolygon2DEditorPlugin(p_node, memnew(NavigationPolygonEditor(p_node)), "NavigationPolygonInstance") {
}
