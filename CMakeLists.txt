cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project (BPP_texture3D)
if(CMAKE_CONFIGURATION_TYPES)
	message("Multi-configuration generator")
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" 
	CACHE STRING "My multi config types" FORCE)
else()
	message("Single-configuration generator")
endif()	

add_definitions(-D_CRT_SECURE_NO_WARNINGS)	
add_definitions(-D_SCL_SECURE_NO_WARNINGS)	
find_package (PCL 1.7.2 REQUIRED)

#SET(Kinect_DIR "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409")
#SET(OpenCV_DIR "C:/opencv249/build")
#find_package( OpenCV REQUIRED )

# (${PCL_INCLUDE_DIRS} ${Kinect_DIR}/inc)
include_directories (${PCL_INCLUDE_DIRS})
link_directories    (${PCL_LIBRARY_DIRS})
add_definitions     (${PCL_DEFINITIONS})

find_package (VTK REQUIRED)
include(${VTK_USE_FILE})

file(GLOB project_c *.c)
file(GLOB project_SOURCES *.cpp)
file(GLOB project_HEADERS *.h)
file(GLOB project_FORMS *.ui)

set   (VTK_LIBRARIES)

QT5_WRAP_CPP (project_HEADERS_MOC MainWindow.h)
QT5_WRAP_UI  (project_FORMS_HEADERS ${project_FORMS})

ADD_DEFINITIONS (${QT_DEFINITIONS})
ADD_EXECUTABLE  (BPP_texture3D 
${project_c} 
${project_SOURCES} 
${project_HEADERS}
${project_HEADERS_MOC}
${project_FORMS_HEADERS}
)

TARGET_LINK_LIBRARIES (BPP_texture3D ${PCL_LIBRARIES} ${VTK_LIBRARIES})
qt5_use_modules (BPP_texture3D Widgets)