#ifndef EDITOR_TRANSLATION_H
#define EDITOR_TRANSLATION_H

#include "core/ustring.h"
#include "core/vector.h"

Vector<String> get_editor_locales();
void load_editor_translations(const String &p_locale);
void load_doc_translations(const String &p_locale);

#endif // EDITOR_TRANSLATION_H
