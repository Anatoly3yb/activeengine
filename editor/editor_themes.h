#ifndef EDITOR_THEMES_H
#define EDITOR_THEMES_H

#include "scene/resources/texture.h"
#include "scene/resources/theme.h"

Ref<Theme> create_editor_theme(Ref<Theme> p_theme = nullptr);

Ref<Theme> create_custom_theme(Ref<Theme> p_theme = nullptr);

Ref<ImageTexture> create_unscaled_default_project_icon();

#endif // EDITOR_THEMES_H
