cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 OLD)
endif(COMMAND cmake_policy)

SET(wxWidgets_USE_LIBS base core)
SET(CMAKE_CXX_STANDARD 11) 
find_package(wxWidgets)
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})

        include_directories(../..)

        add_executable(main wxwidgets.cpp interface.hpp Amplitudeframe.cpp Settingframe.cpp)
        add_library(mathplot SHARED mathplot.cpp mathplot.h)
        # Under Windows, the target type must be WINDOWS, not CONSOLE
        if(WIN32 AND MSVC)
                set_target_properties(main PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
        endif(WIN32 AND MSVC)
        # Linux cross compiling to x86 from x86_64 distribution
        if(LINUX_64_32_CROSSCOMPILE)
                set_source_files_properties(wxwidgets.cpp PROPERTIES COMPILE_FLAGS "-m32 -DwxSIZE_T_IS_UINT -std=c++11")
                set_target_properties(main PROPERTIES LINK_FLAGS "-m32 -std=c++11")
        endif(LINUX_64_32_CROSSCOMPILE)
        target_link_libraries(main ${wxWidgets_LIBRARIES} mathplot)
endif(wxWidgets_FOUND)
