color_test = executable(
	'color-test',
	'color.c',
	dependencies: scenefx_deps,
	include_directories: [scenefx_inc, include_directories('..')],
	link_with: lib_scenefx,
)

foreach case_name : [
	'null-transform',
	'pq-roundtrip',
	'bt2020-to-srgb',
	'fp16-blending',
	'fp16-blur',
]
	test(
		'color-' + case_name,
		color_test,
		args: case_name,
	)
endforeach
