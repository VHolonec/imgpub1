cmake_minimum_required(VERSION 3.8)
project(imagepublisher)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS imgcodecs)
find_package(rclcpp REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(imagepublisher_node imagepublisher_node.cpp)
target_link_libraries(imagepublisher_node PRIVATE
  cv_bridge::cv_bridge
  opencv_imgcodecs
  rclcpp::rclcpp
)

install(TARGETS imagepublisher_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
