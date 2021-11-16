set(sources
	"sxc_string.c"
	"sxc_point.c"
	"sxc_utils.c"
)

set(headers
	"${CMAKE_CURRENT_SOURCE_DIR}/sxc_string.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/sxc_vector.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/sxc_vector_types.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/sxc_point.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/sxc_utils.h"
)

add_library(${LIB_NAME}	SHARED "${sources}")

set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "${headers}")

