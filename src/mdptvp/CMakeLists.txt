# This allows includes to be done relative to the "project", i.e. "mdptvp/...".
include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

qt5_wrap_ui(libmdptvp_ui_moc 
    mainwindow.ui 
    filelist/filelistwidget.ui
    media/playercontrolsbox.ui
    media/mediainfobox.ui
)

set(libmdptvp_HEADERS 
    mainwindow.h 
    filelist/filelistmodel.h 
    filelist/filelistwidget.h
    media/playercontrolsbox.h
)

add_library(libmdptvp STATIC
    mainwindow.cpp
    filelist/filelistwidget.cpp
    filelist/filelistmodel.cpp
    media/playercontrolsbox.cpp
    ${libmdptvp_HEADERS}
    ${libmdptvp_ui_moc}

    filelist/filelist.h
    filelist/filelist.cpp
    filelist/filelistmodel.h
    filelist/filelistmodel.cpp

    media/playercore.h
    media/playercore.cpp
    media/videowidget.h
    media/videowidget.cpp
    media/mediainfobox.h
    media/mediainfobox.cpp

    gui/displaylistmodel.h
    gui/displaylistmodel.cpp
    gui/util.h
    gui/util.cpp
)    

target_link_libraries(libmdptvp Qt5::Widgets ${LIBVLCQT_LIBRARY} ${LIBVLCQT_WIDGETS_LIBRARY})

target_include_directories(libmdptvp PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)
