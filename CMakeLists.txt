cmake_minimum_required(VERSION 2.8.3)
project(epuck_listener)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)
find_package(Qt4 COMPONENTS
    QtCore
    QtGui REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES test1
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include(${QT_USE_FILE})
include_directories(${catkin_INCLUDE_DIRS})

add_executable(epuck_listener epuck_listener.cpp
    CommThread.cpp SerialComm.cpp CommThread.h SerialComm.h)
target_link_libraries(epuck_listener
    ${catkin_LIBRARIES}
    ${QT_LIBRARIES}
)
install(TARGETS epuck_listener
  RUNTIME DESTINATION bin
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
