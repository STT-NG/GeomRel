set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB HEADERS api/*.h)
file(GLOB SOURCES src/*.cpp)

source_group("Source Files" FILES ${SOURCES})
source_group("Header Files" FILES ${HEADERS})

add_library(GeomRel STATIC
  ${SOURCES}
  ${HEADERS}
)

set_target_properties(GeomRel PROPERTIES PUBLIC_HEADER api/geomrel.h)

target_include_directories(GeomRel PUBLIC api/)

install(TARGETS GeomRel DESTINATION lib)
#install(FILES api/geomrel.h DESTINATION include/GeomRel)
