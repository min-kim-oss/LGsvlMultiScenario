cmake_minimum_required(VERSION 3.5)
project(agentController)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_auto REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcl_interfaces REQUIRED)
find_package(lgsvl_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

include_directories(include)

ament_auto_add_library(AgentController SHARED
  src/agentController.cpp
)

target_compile_features(AgentController PRIVATE cxx_std_17)
ament_target_dependencies(AgentController rclcpp rcl_interfaces
   lgsvl_msgs std_msgs)
target_include_directories(AgentController
  PUBLIC
  #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  #$<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_executable(AgentController_node src/agentController_node.cpp)
ament_target_dependencies(AgentController_node rclcpp)
target_link_libraries(AgentController_node AgentController)



ament_auto_add_library(P2AgentController SHARED
  src/p2AgentController.cpp
)

target_compile_features(P2AgentController PRIVATE cxx_std_17)
ament_target_dependencies(P2AgentController rclcpp rcl_interfaces
   lgsvl_msgs std_msgs)
target_include_directories(P2AgentController
  PUBLIC
  #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  #$<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_executable(P2AgentController_node src/p2AgentController_node.cpp)
ament_target_dependencies(P2AgentController_node rclcpp)
target_link_libraries(P2AgentController_node P2AgentController)


install(TARGETS
  AgentController
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS
  AgentController_node
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS
  P2AgentController
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS
  P2AgentController_node
  DESTINATION lib/${PROJECT_NAME})



ament_package()
