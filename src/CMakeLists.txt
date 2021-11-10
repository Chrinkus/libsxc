set(sources
	"sxc_string.c"
)

set(headers
	"sxc_string.h"
)

add_library(${LIB_NAME}	"${sources}")

set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "${headers}")

