find_package(Boost REQUIRED COMPONENTS program_options log log_setup)

cmake_host_system_information(RESULT DIST_NAME QUERY DISTRIB_NAME)
cmake_host_system_information(RESULT DIST_VERSION QUERY DISTRIB_VERSION_ID)
if(${DIST_NAME} MATCHES "Ubuntu" AND ${DIST_VERSION} MATCHES "18.04")
  # On Ubuntu 18.04, we can not link tbb using find_package
  MESSAGE(STATUS "Linux dist: ubuntu 18.04")
  set(TBB_SHARED_OBJECT   "/usr/lib/x86_64-linux-gnu/libtbb.so")
  add_library(TBBLIB SHARED IMPORTED)
  set_target_properties(TBBLIB PROPERTIES
    IMPORTED_LOCATION "${TBB_SHARED_OBJECT}"
    INTERFACE_INCLUDE_DIRECTORIES "/usr/include")
else()
  find_package(TBB REQUIRED)
endif()

# FG Compile Time Options
set(OPT_WR_WINDOW 40 CACHE STRING "WR Window Size")
set(OPT_COALESCE_GAP 5 CACHE STRING "vertex gap before splitting new WR's")
option(USE_TIMING_INSTRUMENTATION "Measure spin and function timing" On)
option(VERTEX_COALESCING "Adjacency list coalescing." On)
configure_file("build_options.hpp.in" "${CMAKE_CURRENT_BINARY_DIR}/build_options.hpp")

add_library(FAMGraph
  vertex_table.cpp
  connection_utils.cpp
  communication_runtime.cpp
  server_runtime.cpp
  client_runtime.cpp
  )

target_include_directories(FAMGraph
  PRIVATE
  "${CMAKE_CURRENT_BINARY_DIR}"
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  ) 

if(${DIST_NAME} MATCHES "Ubuntu" AND ${DIST_VERSION} MATCHES "18.04")
  target_link_libraries(FAMGraph PRIVATE
    project_options
    project_warnings
    Boost::program_options
    Boost::log
    Boost::log_setup
    TBBLIB
    rdmacm
    ibverbs
    pthread
    numa)
else()
  target_link_libraries(FAMGraph PRIVATE
    project_options
    project_warnings
    Boost::program_options
    Boost::log
    Boost::log_setup
    TBB::tbb
    rdmacm
    ibverbs
    pthread
    numa)
endif()

target_compile_definitions(FAMGraph PRIVATE BOOST_LOG_DYN_LINK)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE
  project_options
  project_warnings
  FAMGraph
  Boost::program_options
  Boost::log
  Boost::log_setup
  )
target_compile_definitions(main PRIVATE BOOST_LOG_DYN_LINK)
