qt_add_executable(universalconverter
    main.cpp
    mainwindow.hpp
    mainwindow.cpp
)

target_link_libraries(universalconverter PRIVATE
    numericlogic
    Qt6::Widgets
)

set_target_properties(universalconverter PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)