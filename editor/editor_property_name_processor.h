#ifndef EDITOR_PROPERTY_NAME_PROCESSOR_H
#define EDITOR_PROPERTY_NAME_PROCESSOR_H

#include "scene/main/node.h"

class EditorPropertyNameProcessor : public Node {
	GDCLASS(EditorPropertyNameProcessor, Node);

	static EditorPropertyNameProcessor *singleton;

	mutable Map<String, String> capitalize_string_cache;
	Map<String, String> capitalize_string_remaps;
	LocalVector<String> stop_words; // Exceptions that shouldn't be capitalized.

	// Capitalizes property path segments.
	String _capitalize_name(const String &p_name) const;

public:
	// Matches `interface/inspector/capitalize_properties` editor setting.
	enum Style {
		STYLE_RAW,
		STYLE_CAPITALIZED,
		STYLE_LOCALIZED,
	};

	static EditorPropertyNameProcessor *get_singleton() { return singleton; }

	static Style get_default_inspector_style();
	static Style get_settings_style();
	static Style get_tooltip_style(Style p_style);

	static bool is_localization_available();

	// Turns property path segment into the given style.
	String process_name(const String &p_name, Style p_style) const;

	EditorPropertyNameProcessor();
	~EditorPropertyNameProcessor();
};

#endif // EDITOR_PROPERTY_NAME_PROCESSOR_H
