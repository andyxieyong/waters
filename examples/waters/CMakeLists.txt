# Include Environment-based settings.
include(${CMAKE_CURRENT_DOURCE_DIR}../common_settings.txt)

# Create the executable.
add_executable(waters waters.cpp wkernel.cpp wtask.cpp builder.cpp weibullvar.cpp Task2.cpp Runnable2.cpp Label2.cpp strtools.cpp tinyxml/tinyxml2.cpp)

# Indicate that the executable needs metasim and rtlib library.
target_link_libraries( waters rtlib ${metasim_LIBRARY} )
