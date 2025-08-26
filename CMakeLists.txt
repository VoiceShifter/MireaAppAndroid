cmake_minimum_required(VERSION 3.16)

project(MireaApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.9 REQUIRED COMPONENTS Quick
      Qml
      QuickControls2
      Svg
)

qt_standard_project_setup()

qt_add_executable(appTest
      src/main.cpp
)

qt_add_qml_module(appTest
      URI MireaApp
      VERSION 1.0
      SOURCES
            ./src/main.cpp
            ./src/SocketCall.h          ./src/SocketCall.cpp
            ./src/Searcher.h            ./src/Searcher.cpp
            ./src/JsonParser.h          ./src/JsonParser.cpp
            ./src/LoginCall.h           ./src/LoginCall.cpp
            ./src/Schedule.hpp          ./src/Schedule.cpp
            ./src/SubjectSystem.hpp     ./src/SubjectSystem.cpp
            ./src/Reseter.hpp           ./src/Reseter.cpp
      QML_FILES
            ./qml/LoginPage.qml
            ./qml/Main.qml
            ./qml/MyDir/ColorsNSizes.qml
            ./qml/MyDir/Icons/home.svg
            ./qml/MyDir/MyDrawer.qml
            ./qml/Schedule.qml
            ./qml/MyDir/Subject.qml
            ./qml/Attendance.qml
            ./qml/MyDir/AttendanceLine.qml
            ./qml/MyDir/qmldir
            ./qml/Teachers.qml
            ./qml/SubjectPage.qml
            ./qml/MyDir/File.qml
      RESOURCES
            ./src/data/Teachers.txt
            ./src/data/Cache.txt  
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
#QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
set_target_properties(appTest PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTest
      MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
      MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
      MACOSX_BUNDLE TRUE
      WIN32_EXECUTABLE TRUE


)

target_link_libraries(appTest
    PRIVATE
        Qt6::Quick
        Qt6::Qml
        Qt6::QuickControls2
        Qt6::Svg
)
if (ANDROID)
      include(${CMAKE_SOURCE_DIR}/android_openssl/android_openssl.cmake)
endif()
if (ANDROID)
      add_android_openssl_libraries(appTest)
endif()

include(GNUInstallDirs)
install(TARGETS appTest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# Copy data files to the asset folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/data DESTINATION ${CMAKE_BINARY_DIR}/android/assets)
set(Directory "Files")
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${Directory})
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Students)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${Directory}/Subjects)


list(APPEND QML_DIRS "F:/Qt/Tools/QtCreator/bin/qml")
list(APPEND QML_DIRS "F:/Qt/6.5.3/msvc2019_64/qml")
set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/qml ${CMAKE_BINARY_DIR}/imports CACHE STRING "" FORCE)
