cmake_minimum_required (VERSION 3.8)

add_executable (hrcs "hrc.h" "hrc.cpp"   "auth/auth.h" "auth/auth.cpp" "tools.h" "tools.cpp"   "module.h" "v1_handler.h" "v1_handler.cpp")
set_target_properties(hrcs PROPERTIES DEBUG_POSTFIX "d") 
set_target_properties(hrcs PROPERTIES OUTPUT_NAME "hrcs.${FILENAME_SUFFIX}")
if (UNIX)
	TARGET_LINK_LIBRARIES(hrcs dl)
endif()
link_directories(${OUTDIR})
