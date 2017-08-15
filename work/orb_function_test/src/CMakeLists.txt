#opencv

find_package(OpenCV REQUIRED )
include_directories ( ${OpenCV_INCLUDE_DIRS})

add_library( shared_lib GroundTruth.cpp )
TARGET_LINK_LIBRARIES( shared_lib
    ${OpenCV_LIBS}  )

add_library( readimage readimage.cpp )
TARGET_LINK_LIBRARIES( readimage
    ${OpenCV_LIBS}  )

include_directories ("/usr/include/eigen3")

add_executable (orb_feature_extract orb_feature_extract.cpp)
target_link_libraries(orb_feature_extract ${OpenCV_LIBS})

add_executable (orb_opencv_function orb_opencv_function.cpp)
target_link_libraries(orb_opencv_function shared_lib ${OpenCV_LIBS})

add_executable (stero_calibration stero_calibration.cc)
target_link_libraries(stero_calibration readimage ${OpenCV_LIBS})








