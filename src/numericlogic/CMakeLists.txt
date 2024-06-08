qt_add_library(numericlogic STATIC
    bigint.hpp
    bigint.cpp
    bigfraction.hpp
    bigfraction.cpp
)
target_link_libraries(numericlogic PRIVATE Qt6::Core)
target_include_directories(numericlogic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})