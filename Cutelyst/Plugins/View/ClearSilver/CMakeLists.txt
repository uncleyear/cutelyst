set(CS_INCDIR_PFX "ClearSilver")

find_path(CLEARSILVER_SYSTEM_INCLUDE_DIR ${CS_INCDIR_PFX}/ClearSilver.h)
find_path(CLEARSILVER_UTIL_INCLUDE_DIR "util/neo_misc.h" PATH_SUFFIXES ${CS_INCDIR_PFX})

include_directories(
    ${CLEARSILVER_SYSTEM_INCLUDE_DIR}
    ${CLEARSILVER_UTIL_INCLUDE_DIR}
)

set(clearsilver_plugin_SRC
    clearsilver.cpp
    clearsilver_p.h
)

set(plugin_view_clearsilver_HEADERS
    clearsilver.h
)

add_library(cutelyst_view_clearsilver SHARED
    ${clearsilver_plugin_SRC}
)
add_library(CutelystQt5::View::ClearSilver ALIAS cutelyst_view_clearsilver)
set_property(TARGET cutelyst_view_clearsilver PROPERTY EXPORT_NAME View::ClearSilver)

set_target_properties(cutelyst_view_clearsilver PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${CUTELYST_API_LEVEL}
)

target_link_libraries(cutelyst_view_clearsilver
    PRIVATE cutelyst-qt5
    PRIVATE ${ClearSilver_CS}
    PRIVATE ${ClearSilver_Util}
)

install(TARGETS cutelyst_view_clearsilver EXPORT CutelystQt5Targets DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES ${plugin_view_clearsilver_HEADERS}
        DESTINATION include/cutelyst-qt5/Cutelyst/Plugins/View/ClearSilver
        COMPONENT View::ClearSilver
)
