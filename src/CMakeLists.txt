qt5_wrap_ui(libmdptvp_ui_moc 
    mdptvp/mainwindow.ui 
    mdptvp/filelist/filelistwidget.ui
    mdptvp/media/playercontrolsbox.ui
)

set(libmdptvp_HEADERS 
    mdptvp/mainwindow.h 
    mdptvp/filelist/filelistmodel.h 
    mdptvp/filelist/filelistwidget.h
    mdptvp/media/mediaplayer.h
    mdptvp/media/playercontrolsbox.h
)

add_library(libmdptvp STATIC
    mdptvp/mainwindow.cpp
    mdptvp/filelist/filelistwidget.cpp
    mdptvp/filelist/filelistmodel.cpp
    mdptvp/media/playercontrolsbox.cpp
    mdptvp/media/mediaplayer.cpp
    ${libmdptvp_HEADERS}
    ${libmdptvp_ui_moc}
)    

target_link_libraries(libmdptvp Qt5::Widgets)
target_include_directories(libmdptvp PUBLIC .)
