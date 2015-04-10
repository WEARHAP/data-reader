cmake_minimum_required(VERSION 2.8.3)
project(pisa_hand_publisher)


#set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR} )

FIND_PATH(SERIAL_INCLUDE_DIR SerialStream.h
   /usr/include
   /usr/local/include

)



find_package(catkin REQUIRED tf
	COMPONENTS
  roscpp
  rospy
  std_msgs
  tf)

#find_package(/usr/include/eigen3/Eigen)

#include_directories(/usr/include/eigen3/Eigen)


#add_executable(forth_hand_publisher src/forth_hand_publisher.cpp) #erano discommentate
#target_link_libraries( forth_hand_publisher ${catkin_LIBRARIES} -lserial ) #erano discommentate

catkin_package()

## Declare a cpp executable
add_executable(pisa_hand_publisher_node 
	src/pisa_hand_publisher.cpp
	)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
#add_dependencies(forth_hand_publisher_node 
#	my_utility
#	)

## Specify libraries to link a library or executable target against
target_link_libraries(pisa_hand_publisher_node
#	my_utility
	-lserial
	 #src/iNEMO_Compass.c
     #${PROJECT_NAME}
    ${catkin_LIBRARIES}
)




