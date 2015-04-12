# This allows includes to be done relative to the "project", i.e. "mdptvp/...".
include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(vlc)

qt5_wrap_ui(libmdptvp_ui_moc 
    mainwindow.ui 
    filelist/filelistwidget.ui
    media/playercontrolsbox.ui
)

set(libmdptvp_HEADERS 
    mainwindow.h 
    filelist/filelistmodel.h 
    filelist/filelistwidget.h
    media/mediaplayer.h
    media/playercontrolsbox.h
)

add_library(libmdptvp STATIC
    mainwindow.cpp
    filelist/filelistwidget.cpp
    filelist/filelistmodel.cpp
    media/playercontrolsbox.cpp
    media/mediaplayer.cpp
    ${libmdptvp_HEADERS}
    ${libmdptvp_ui_moc}
)    

target_link_libraries(libmdptvp Qt5::Widgets)

target_include_directories(libmdptvp PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)
