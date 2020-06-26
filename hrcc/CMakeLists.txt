cmake_minimum_required (VERSION 3.8)

add_executable (hrcc "hrc.h" "hrc.cpp"  "../lib/helper.h")
set_target_properties(hrcc PROPERTIES DEBUG_POSTFIX "d") 
set_target_properties(hrcc PROPERTIES OUTPUT_NAME "hrcc.${FILENAME_SUFFIX}")
if (UNIX)
	TARGET_LINK_LIBRARIES(hrcc dl)
endif()
link_directories(${OUTDIR})
