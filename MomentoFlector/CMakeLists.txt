# CMakeList.txt : CMake project for MomentoFlector, include source and define
# project specific logic here.
#

# Add source to this project's executable.
file(GLOB MomentoFlector_sources ./**.cpp)
set(MomentoFlector ${MomentoFlector_sources})
add_executable (MomentoFlector ${MomentoFlector_sources})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MomentoFlector PROPERTY CXX_STANDARD 20)
endif()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/results)