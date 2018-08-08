#g++ src.cpp src2.cpp -o excecutable `pkg-config opencv --cflags --libs`

cmake_minimum_required(VERSION 2.8)

project( Computer_Vision_Algorithm )
set(
CMAKE_RUNTIME_OUTPUT_DIRECTORY 
../bin#${CMAKE_HOME_DIRECTORY}/bin
)

#find_package(OpenCV 3.2 REQUIRED)
find_package(OpenCV REQUIRED)

add_executable( cvalgorithm ../src/main.cpp ../src/polycolor.cpp ../src/space.cpp ../src/test.cpp )
add_executable( suma ../src/suma.cpp )

target_link_libraries( cvalgorithm ${OpenCV_LIBS} )
target_link_libraries( suma ${OpenCV_LIBS} )
