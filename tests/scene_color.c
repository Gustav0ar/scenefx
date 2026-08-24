#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <wlr/types/wlr_output.h>

#include "types/wlr_scene.h"

static bool check(bool condition, const char *message) {
	if (!condition) {
		fprintf(stderr, "FAIL: %s\n", message);
	}
	return condition;
}

int main(void) {
	const struct wlr_output_image_description hdr = {
		.transfer_function = WLR_COLOR_TRANSFER_FUNCTION_ST2084_PQ,
		.primaries = WLR_COLOR_NAMED_PRIMARIES_BT2020,
	};
	bool ok = true;

	ok &= check(!scene_color_management_is_scanout_allowed(NULL, 0, 0),
		"untagged SDR requires composition");
	ok &= check(scene_color_management_is_scanout_allowed(NULL,
		WLR_COLOR_TRANSFER_FUNCTION_GAMMA22,
		WLR_COLOR_NAMED_PRIMARIES_SRGB),
		"explicit legacy SDR can use direct scanout");
	ok &= check(!scene_color_management_is_scanout_allowed(NULL,
		WLR_COLOR_TRANSFER_FUNCTION_SRGB,
		WLR_COLOR_NAMED_PRIMARIES_SRGB),
		"sRGB transfer requires conversion for a legacy SDR output");
	ok &= check(scene_color_management_is_scanout_allowed(&hdr,
		WLR_COLOR_TRANSFER_FUNCTION_ST2084_PQ,
		WLR_COLOR_NAMED_PRIMARIES_BT2020),
		"matching HDR content can use direct scanout");
	ok &= check(!scene_color_management_is_scanout_allowed(&hdr,
		WLR_COLOR_TRANSFER_FUNCTION_GAMMA22,
		WLR_COLOR_NAMED_PRIMARIES_SRGB),
		"mismatched HDR content requires composition");

	return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
