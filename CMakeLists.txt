cmake_minimum_required(VERSION 3.14)

project(POC_QtPDF_use LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_FIND_DEBUG_MODE 1)   # this is to debug find_package function

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Pdf REQUIRED)

set(HEADER_FILES
    d_pdf_document.h
    d_pdf_image.h
    inc_pdf_doc.h
)

set(SOURCE_FILES
    d_pdf_document.cpp
    d_pdf_image.cpp
    main.cpp
)

set(RESOURCE_FILES
    qml.qrc
)

if(ANDROID)
    add_library(POC_QtPDF_use SHARED ${HEADER_FILES} ${SOURCE_FILES} ${RESOURCE_FILES})
else()
    add_executable(POC_QtPDF_use ${HEADER_FILES} ${SOURCE_FILES} ${RESOURCE_FILES})
endif()

target_compile_definitions(POC_QtPDF_use
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(POC_QtPDF_use
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Pdf)
