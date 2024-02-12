# if module1 is a library, use add_library() instead
#add_library(core
#  iuserinterface.cpp
#  game.cpp
#)
target_sources(core PRIVATE ./document.cpp)
target_compile_features(core PUBLIC cxx_std_20) # or whatever language standard you are using
target_include_directories(core PUBLIC include)
if(EXAMPLE_PROJECT_BUILD_TESTING)
  add_subdirectory(tests)
endif()
