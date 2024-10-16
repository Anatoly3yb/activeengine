#include "skeleton_editor_plugin.h"

#include "scene/3d/collision_shape.h"
#include "scene/3d/physics_body.h"
#include "scene/3d/physics_joint.h"
#include "scene/resources/capsule_shape.h"
#include "scene/resources/sphere_shape.h"
#include "spatial_editor_plugin.h"

void SkeletonEditor::_on_click_option(int p_option) {
	if (!skeleton) {
		return;
	}

	switch (p_option) {
		case MENU_OPTION_CREATE_PHYSICAL_SKELETON: {
			create_physical_skeleton();
		} break;
	}
}

void SkeletonEditor::create_physical_skeleton() {
	UndoRedo *ur = EditorNode::get_singleton()->get_undo_redo();
	Node *owner = get_tree()->get_edited_scene_root();

	const int bc = skeleton->get_bone_count();

	if (!bc) {
		return;
	}

	Vector<BoneInfo> bones_infos;
	bones_infos.resize(bc);

	for (int bone_id = 0; bc > bone_id; ++bone_id) {
		const int parent = skeleton->get_bone_parent(bone_id);

		if (parent < 0) {
			bones_infos.write[bone_id].relative_rest = skeleton->get_bone_rest(bone_id);

		} else {
			const int parent_parent = skeleton->get_bone_parent(parent);

			bones_infos.write[bone_id].relative_rest = bones_infos[parent].relative_rest * skeleton->get_bone_rest(bone_id);

			/// create physical bone on parent
			if (!bones_infos[parent].physical_bone) {
				bones_infos.write[parent].physical_bone = create_physical_bone(parent, bone_id, bones_infos);

				ur->create_action(TTR("Create physical bones"), UndoRedo::MERGE_ALL);
				ur->add_do_method(skeleton, "add_child", bones_infos[parent].physical_bone);
				ur->add_do_reference(bones_infos[parent].physical_bone);
				ur->add_undo_method(skeleton, "remove_child", bones_infos[parent].physical_bone);
				ur->commit_action();

				bones_infos[parent].physical_bone->set_bone_name(skeleton->get_bone_name(parent));
				bones_infos[parent].physical_bone->set_owner(owner);
				bones_infos[parent].physical_bone->get_child(0)->set_owner(owner); // set shape owner

				/// Create joint between parent of parent
				if (-1 != parent_parent) {
					bones_infos[parent].physical_bone->set_joint_type(PhysicalBone::JOINT_TYPE_PIN);
				}
			}
		}
	}
}

PhysicalBone *SkeletonEditor::create_physical_bone(int bone_id, int bone_child_id, const Vector<BoneInfo> &bones_infos) {
	const Transform child_rest = skeleton->get_bone_rest(bone_child_id);

	real_t half_height(child_rest.origin.length() * 0.5);
	real_t radius(half_height * 0.2);

	CapsuleShape *bone_shape_capsule = memnew(CapsuleShape);
	bone_shape_capsule->set_height((half_height - radius) * 2);
	bone_shape_capsule->set_radius(radius);

	CollisionShape *bone_shape = memnew(CollisionShape);
	bone_shape->set_shape(bone_shape_capsule);

	Transform capsule_transform;
	bone_shape->set_transform(capsule_transform);

	Vector3 up = Vector3(0, 1, 0);
	if (up.cross(child_rest.origin).is_zero_approx()) {
		up = Vector3(0, 0, 1);
	}

	Transform body_transform;
	body_transform.set_look_at(Vector3(0, 0, 0), child_rest.origin, up);
	body_transform.origin = body_transform.basis.xform(Vector3(0, 0, -half_height));

	Transform joint_transform;
	joint_transform.origin = Vector3(0, 0, half_height);

	PhysicalBone *physical_bone = memnew(PhysicalBone);
	physical_bone->add_child(bone_shape);
	physical_bone->set_name("Physical Bone " + skeleton->get_bone_name(bone_id));
	physical_bone->set_body_offset(body_transform);
	physical_bone->set_joint_offset(joint_transform);
	return physical_bone;
}

void SkeletonEditor::edit(Skeleton *p_node) {
	skeleton = p_node;
}

void SkeletonEditor::_notification(int p_what) {
	if (p_what == NOTIFICATION_ENTER_TREE) {
		get_tree()->connect("node_removed", this, "_node_removed");
	}
}

void SkeletonEditor::_node_removed(Node *p_node) {
	if (p_node == skeleton) {
		skeleton = nullptr;
		options->hide();
	}
}

void SkeletonEditor::_bind_methods() {
	ClassDB::bind_method("_on_click_option", &SkeletonEditor::_on_click_option);
	ClassDB::bind_method("_node_removed", &SkeletonEditor::_node_removed);
}

SkeletonEditor::SkeletonEditor() {
	skeleton = nullptr;
	options = memnew(MenuButton);
	SpatialEditor::get_singleton()->add_control_to_menu_panel(options);

	options->set_text(TTR("Skeleton"));
	options->set_icon(EditorNode::get_singleton()->get_gui_base()->get_icon("Skeleton", "EditorIcons"));

	options->get_popup()->add_item(TTR("Create physical skeleton"), MENU_OPTION_CREATE_PHYSICAL_SKELETON);

	options->get_popup()->connect("id_pressed", this, "_on_click_option");
	options->hide();
}

SkeletonEditor::~SkeletonEditor() {}

void SkeletonEditorPlugin::edit(Object *p_object) {
	skeleton_editor->edit(Object::cast_to<Skeleton>(p_object));
}

bool SkeletonEditorPlugin::handles(Object *p_object) const {
	return p_object->is_class("Skeleton");
}

void SkeletonEditorPlugin::make_visible(bool p_visible) {
	if (p_visible) {
		skeleton_editor->options->show();
	} else {
		skeleton_editor->options->hide();
		skeleton_editor->edit(nullptr);
	}
}

SkeletonEditorPlugin::SkeletonEditorPlugin(EditorNode *p_node) {
	editor = p_node;
	skeleton_editor = memnew(SkeletonEditor);
	editor->get_viewport()->add_child(skeleton_editor);
}

SkeletonEditorPlugin::~SkeletonEditorPlugin() {}
