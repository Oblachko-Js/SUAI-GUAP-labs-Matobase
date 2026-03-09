# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/applab9sheka_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/applab9sheka_autogen.dir/ParseCache.txt"
  "applab9sheka_autogen"
  )
endif()
