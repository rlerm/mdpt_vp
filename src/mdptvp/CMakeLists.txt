# This allows includes to be done relative to the "project", i.e. "mdptvp/...".
include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

add_library(libmdptvp STATIC
    mainwindow.cpp
    mainwindow.h 
    mainwindow.ui 

    filelist/filelist.cpp
    filelist/filelist.h
    filelist/filelistmodel.cpp
    filelist/filelistmodel.h 
    filelist/filelistwidget.cpp
    filelist/filelistwidget.h
    filelist/filelistwidget.ui

    gui/displaylistmodel.cpp
    gui/displaylistmodel.h
    gui/util.cpp
    gui/util.h

    media/mediainfobox.cpp
    media/mediainfobox.h
    media/mediainfobox.ui
    media/playercontrolsbox.cpp
    media/playercontrolsbox.h
    media/playercontrolsbox.ui
    media/playercore.cpp
    media/playercore.h
    media/videowidget.cpp
    media/videowidget.h

    util/text.cpp
    util/text.h
)    

target_link_libraries(libmdptvp 
    Qt5::Core
    Qt5::Widgets 
    ${LIBVLCQT_LIBRARY} 
    ${LIBVLCQT_WIDGETS_LIBRARY} 
)

# add_dependencies(libmdptvp
    # resources
# )

target_include_directories(libmdptvp PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)
