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

add_executable(util main.cpp)
if(${DIST_NAME} MATCHES "Ubuntu" AND ${DIST_VERSION} MATCHES "18.04")
  target_link_libraries(util PRIVATE
    project_options
    project_warnings
    Boost::program_options
    Boost::log
    Boost::log_setup
    TBBLIB
    )
else()
  target_link_libraries(util PRIVATE
    project_options
    project_warnings
    Boost::program_options
    Boost::log
    Boost::log_setup
    TBB::tbb
    )
endif()

target_compile_definitions(util PRIVATE BOOST_LOG_DYN_LINK)

add_executable(maxdegree maxd.cpp)
target_link_libraries(maxdegree PRIVATE
  project_options
  project_warnings
  Boost::program_options
  Boost::log
  Boost::log_setup
  )

target_compile_definitions(maxdegree PRIVATE BOOST_LOG_DYN_LINK)

add_executable(fg2gr fg2gr.cpp)
target_link_libraries(fg2gr PRIVATE
  project_options
  project_warnings
  Boost::program_options
  Boost::log
  Boost::log_setup
  )

target_compile_definitions(fg2gr PRIVATE BOOST_LOG_DYN_LINK)

add_executable(compare_gr compare_gr.cpp)
target_link_libraries(compare_gr PRIVATE
  project_options
  project_warnings
  Boost::program_options
  Boost::log
  Boost::log_setup
  )

target_compile_definitions(compare_gr PRIVATE BOOST_LOG_DYN_LINK)

add_executable(memusage memusage.cpp)
target_link_libraries(memusage PRIVATE
  project_options
  project_warnings
  Boost::program_options
  Boost::log
  Boost::log_setup
  )

target_compile_definitions(memusage PRIVATE BOOST_LOG_DYN_LINK)
