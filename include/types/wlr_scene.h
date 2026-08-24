#ifndef TYPES_WLR_SCENE_H
#define TYPES_WLR_SCENE_H

#include <wlr/types/wlr_scene.h>

struct wlr_scene *scene_node_get_root(struct wlr_scene_node *node);

void scene_node_get_size(struct wlr_scene_node *node, int *width, int *height);

void scene_surface_set_clip(struct wlr_scene_surface *surface, struct wlr_box *clip);

bool scene_color_management_is_scanout_allowed(
	const struct wlr_output_image_description *img_desc,
	enum wlr_color_transfer_function transfer_function,
	enum wlr_color_named_primaries primaries);

#endif
