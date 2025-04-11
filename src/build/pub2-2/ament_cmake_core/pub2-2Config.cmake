# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_pub2-2_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED pub2-2_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(pub2-2_FOUND FALSE)
  elseif(NOT pub2-2_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(pub2-2_FOUND FALSE)
  endif()
  return()
endif()
set(_pub2-2_CONFIG_INCLUDED TRUE)

# output package information
if(NOT pub2-2_FIND_QUIETLY)
  message(STATUS "Found pub2-2: 0.0.0 (${pub2-2_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'pub2-2' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${pub2-2_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(pub2-2_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${pub2-2_DIR}/${_extra}")
endforeach()
