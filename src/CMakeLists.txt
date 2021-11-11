set(sources
	"sxc_string.c"
	"sxc_point.c"
)

set(headers
	"sxc_string.h"
	"sxc_vector.h"
	"sxc_point.h"
)

add_library(${LIB_NAME}	"${sources}")

set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "${headers}")

