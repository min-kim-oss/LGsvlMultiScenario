# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_agentController_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED agentController_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(agentController_FOUND FALSE)
  elseif(NOT agentController_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(agentController_FOUND FALSE)
  endif()
  return()
endif()
set(_agentController_CONFIG_INCLUDED TRUE)

# output package information
if(NOT agentController_FIND_QUIETLY)
  message(STATUS "Found agentController: 0.0.0 (${agentController_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'agentController' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${agentController_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(agentController_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${agentController_DIR}/${_extra}")
endforeach()
