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
    gui/aboutdialog.cpp
    gui/aboutdialog.h
    gui/aboutdialog.ui

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

    util/gui.cpp
    util/gui.h
    util/text.cpp
    util/text.h
)

target_link_libraries(libmdptvp
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    ${LIBVLCQT_LIBRARY}
    ${LIBVLCQT_WIDGETS_LIBRARY}
)

target_include_directories(libmdptvp PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${LIBVLCQT_INCLUDE_DIR}
)
