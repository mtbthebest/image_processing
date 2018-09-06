cmake_minimum_required(VERSION 3.12)
set( PROJECT_NAME "image_processing" )
set(CMAKE_CXX_STANDARD 14)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package( OpenCV 2.4.8 REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

if( OpenCV_FOUND )
    list( APPEND ThirdParty_LIBS ${OpenCV_LIBS} )
    include_directories( ${OpenCV_INCLUDE_DIRS} )
endif( OpenCV_FOUND )

#set(SOURCE_FILES load_image.cpp)
#set(SOURCE_FILES manipulate_pixels.cpp)
#set(SOURCE_FILES manipulate_color.cpp colordetector.cpp)
#set(SOURCE_FILES huesaturation.cpp)
#set(SOURCE_FILES grabcut.cpp)
#set(SOURCE_FILES histogram.cpp)
#set(SOURCE_FILES contentFinder.cpp )
#set(SOURCE_FILES finder.cpp)
set(SOURCE_FILES retrieve.cpp imageComparator.h)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#add_subdirectory(images)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})




