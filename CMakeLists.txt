cmake_minimum_required(VERSION 3.16)
include(CMakePrintHelpers)
project(MireaApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.9 REQUIRED COMPONENTS Quick
      Qml
      QuickControls2
      Svg
)

qt_standard_project_setup()

qt_add_executable(ScheduleApplication
      src/main.cpp
)

qt_add_qml_module(ScheduleApplication
      URI MireaApp
      VERSION 1.0
      SOURCES
            ./src/main.cpp
            ./src/SocketCall.h          ./src/SocketCall.cpp
            ./src/Searcher.h            ./src/Searcher.cpp
            ./src/JsonParser.h          ./src/JsonParser.cpp
            ./src/ServerCall.h           ./src/ServerCall.cpp
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
set_target_properties(ScheduleApplication PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ScheduleApplication
      MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
      MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
      MACOSX_BUNDLE TRUE
      WIN32_EXECUTABLE TRUE


)

target_link_libraries(ScheduleApplication
    PRIVATE
        Qt6::Quick
        Qt6::Qml
        Qt6::QuickControls2
        Qt6::Svg
)
set(ANDROID_SSL_PATH "/home/username/Android/android_openssl")
if (ANDROID)
      include(${ANDROID_SSL_PATH}/android_openssl.cmake)
      cmake_print_variables(ANDROID_SSL_PATH)
endif()
if (ANDROID)
      add_android_openssl_libraries(ScheduleApplication)
endif()

include(GNUInstallDirs)
install(TARGETS ScheduleApplication
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

set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/qml ${CMAKE_BINARY_DIR}/imports CACHE STRING "" FORCE)
