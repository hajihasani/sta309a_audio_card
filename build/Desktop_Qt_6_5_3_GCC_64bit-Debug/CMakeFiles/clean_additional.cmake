# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/sta309a_audio_card_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/sta309a_audio_card_autogen.dir/ParseCache.txt"
  "sta309a_audio_card_autogen"
  )
endif()
