# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\metodik_invaders2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\metodik_invaders2_autogen.dir\\ParseCache.txt"
  "metodik_invaders2_autogen"
  )
endif()
