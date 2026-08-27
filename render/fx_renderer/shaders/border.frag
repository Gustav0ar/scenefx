#extension GL_OES_standard_derivatives : enable

#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif

varying vec4 v_color;
varying vec2 v_texcoord;

uniform vec2 clip_size;
uniform vec2 clip_position;
uniform float clip_radius_top_left;
uniform float clip_radius_top_right;
uniform float clip_radius_bottom_left;
uniform float clip_radius_bottom_right;

uniform float inner_width;
uniform float outer_width;
uniform vec4 inner_color;

float rounded_rect_distance(vec2 size, vec2 position,
		float radius_tl, float radius_tr, float radius_bl, float radius_br);

float antialias_width(float distance) {
	vec2 gradient = vec2(dFdx(distance), dFdy(distance));
	return max(length(gradient), 1.0) * 0.5;
}

float content_distance() {
	return rounded_rect_distance(
		clip_size,
		clip_position,
		clip_radius_top_left,
		clip_radius_top_right,
		clip_radius_bottom_left,
		clip_radius_bottom_right
	);
}

void main() {
	float distance = content_distance();
	float antialias = antialias_width(distance);
	float total_width = inner_width + outer_width;

	float inner_coverage = smoothstep(-antialias, antialias, distance);
	float outer_coverage =
		1.0 - smoothstep(-antialias, antialias, distance - total_width);
	float outer_mix = outer_width > 0.0
		? smoothstep(
			inner_width - antialias,
			inner_width + antialias,
			distance
		)
		: 0.0;
	vec4 color = mix(inner_color, v_color, outer_mix);
	gl_FragColor = color * min(inner_coverage, outer_coverage);
}
