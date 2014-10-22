cmake_minimum_required(VERSION 3.0)

project(wearAnalyzer)

find_package(Qt5 REQUIRED Gui Widgets)
set(OpenCV_DIR "D:/libs/opencv")
find_package(OpenCV REQUIRED core highgui imgproc)

set(VTK_DIR "D:/libs/VTK/lib/cmake/vtk-6.2")
find_package(VTK REQUIRED)

file(GLOB sources "SRC/*.cpp")
file(GLOB headers "Include/*.h")
file(GLOB forms "*UIs/*.ui") 


QT5_WRAP_UI(UIS ${forms})
QT5_WRAP_CPP(MOC ${sources} ${headers})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

source_group("Forms" 		FILES ${forms})
source_group("UI Headers" 	FILES ${UIS})
source_group("MOC'd files" 	FILES ${MOC})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BUILD_DIR})
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Qt5Gui_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Qt5OpenGL_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}) 
INCLUDE_DIRECTORIES(${VTK_INCLUDE_DIRS})
INCLUDE(${VTK_USE_FILE}) 

ADD_EXECUTABLE(wearAnalyzer ${sources} ${headers} ${MOC} ${UIS})

TARGET_LINK_LIBRARIES(wearAnalyzer 
	Qt5::Gui
	Qt5::Widgets
	Qt5::Core
	opencv_highgui 
	opencv_imgproc 
	opencv_core
	${vtkGUISupportQtOpenGL_LIBRARIES}
	${VTK_LIBRARIES}
	)
