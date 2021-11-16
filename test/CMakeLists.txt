include_directories("${PROJECT_SOURCE_DIR}/src")

# List of test files
set(test_files
	# string
	"tests_string_init.c"
	"tests_string_push.c"
	"tests_string_getline.c"
	# vector
	"tests_vector_init.c"
	"tests_vector_push.c"
	"tests_vector_push_types.c"
	"tests_vector_foreach.c"
	"tests_vector_copy.c"
	"tests_vector_find.c"
	"tests_vector_types.c"
	# point
	"tests_point_cmp.c"
	# utils
	"tests_charcount.c"
	"tests_charmap.c"
)

string(LENGTH "tests_" test_prefix_len)

foreach(file IN LISTS test_files)
	get_filename_component(file_we "${file}" NAME_WE)
	string(SUBSTRING "${file_we}" ${test_prefix_len} -1 func)
	set(command_name "${func}_test")

	add_executable("${command_name}" "${file}")
	target_link_libraries("${command_name}" PRIVATE "${LIB_NAME}")
	add_test(NAME "${func}" COMMAND "${command_name}")
endforeach()

